#include "qrthreadpool.h"

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>
#include <map>

NS_QRCOMMON_BEGIN

class QrThreadPoolPrivate{
    QR_DECLARE_PUBLIC(QrThreadPool)

public:
    QrThreadPoolPrivate(QrThreadPool* q);

public:
    void notify_callback(long callback_taskid, void *data);

public:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;
    //  task's callback
    long taskid = 0;
    long callbacklimit = 1;
    std::map<long, std::function<void (void *)> > callbacks;

    // synchronization
    std::mutex queue_mutex;
    std::mutex taskid_mutex;
    std::condition_variable condition;
    bool stop;
};

QrThreadPoolPrivate::QrThreadPoolPrivate(QrThreadPool *q)
    : stop(false),
      q_ptr(q)
{}

void QrThreadPoolPrivate::notify_callback(long callback_taskid, void *data)
{
    {
        std::unique_lock<std::mutex> lock(taskid_mutex);
        if(callbacks.end() == callbacks.find(callback_taskid)) {
            return;
        }
    }

    callbacks[callback_taskid](data);
}

NS_QRCOMMON_END

////////////////////////////////////////////////////

USING_NS_QRCOMMON;

// the constructor just launches some amount of workers
QrThreadPool::QrThreadPool(size_t threads)
    : d_ptr(new QrThreadPoolPrivate(this))
{
    Q_D(QrThreadPool);
    d->callbacklimit = threads * 2;
    auto conditonWaitPred = [this]{
        Q_D(QrThreadPool);
        return d->stop || !d->tasks.empty();
    };
    for(size_t i = 0;i<threads;++i) {
        d->workers.emplace_back([this, conditonWaitPred] {
            Q_D(QrThreadPool);
            for(;;) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(d->queue_mutex);
                    d->condition.wait(lock, conditonWaitPred);
                    if(d->stop && d->tasks.empty()){
                        return;
                    }
                    task = std::move(d->tasks.front());
                    d->tasks.pop();
                }

                task();
            }
        }
        );
    }
}

// the destructor joins all threads
QrThreadPool::~QrThreadPool()
{
    Q_D(QrThreadPool);

    {
        std::unique_lock<std::mutex> lock(d->queue_mutex);
        d->stop = true;
    }

    d->condition.notify_all();
    for(std::thread &worker: d->workers) {
        worker.join();
    }
}

void Qters::QrCommon::QrThreadPool::enqueue_asy(std::function<void ()> task)
{
    enqueue_asyc([task](){ task(); return (void *)(1);}, [](void * data){Q_UNUSED(data)});
}

void QrThreadPool::enqueue_asyc(std::function<void * ()> task, std::function<void (void *)> callback)
{
    Q_D(QrThreadPool);
    {
        std::unique_lock<std::mutex> lock(d->queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(d->stop){
            throw std::runtime_error("enqueue on stopped threadpool");
        }

        d->callbacks[d->taskid] = callback;
        int cur_taskid = d->taskid;
        d->tasks.emplace([this, task, cur_taskid](){
            auto data = task();
            Q_D(QrThreadPool);
            d->notify_callback(cur_taskid, (void *)(data));
        });

        {
            std::unique_lock<std::mutex> lock(d->taskid_mutex);
            if(++d->taskid > d->callbacklimit) {
                d->taskid = 0;
            }
        }
    }
    d->condition.notify_one();
}
