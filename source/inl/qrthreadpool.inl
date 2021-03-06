﻿//#ifndef QRTHREADPOOL_INL
//#define QRTHREADPOOL_INL

//#include "qrcommon_global.h"

//USING_NS_QRCOMMON;

//// the constructor just launches some amount of workers
//inline QrThreadPool::QrThreadPool(size_t threads)
//    :   stop(false)
//{
//    callbacklimit = threads * 2;
//    for(size_t i = 0;i<threads;++i)
//        workers.emplace_back(
//            [this]
//            {
//                for(;;)
//                {
//                    std::function<void()> task;

//                    {
//                        std::unique_lock<std::mutex> lock(this->queue_mutex);
//                        this->condition.wait(lock,
//                            [this]{ return this->stop || !this->tasks.empty(); });
//                        if(this->stop && this->tasks.empty()){
//                            return;
//                        }
//                        task = std::move(this->tasks.front());
//                        this->tasks.pop();
//                    }

//                    task();
//                }
//            }
//        );
//}

//// add new work item to the pool
//template<class F, class... Args>
//auto QrThreadPool::enqueue(F&& f, Args&&... args)
//    -> std::future<typename std::result_of<F(Args...)>::type>
//{
//    using return_type = typename std::result_of<F(Args...)>::type;

//    auto task = std::make_shared< std::packaged_task<return_type()> >(
//            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
//        );

//    std::future<return_type> res = task->get_future();
//    {
//        std::unique_lock<std::mutex> lock(queue_mutex);

//        // don't allow enqueueing after stopping the pool
//        if(stop){
//            throw std::runtime_error("enqueue on stopped threadpool");
//        }

//        tasks.emplace([task](){ (*task)(); });
//    }
//    condition.notify_one();
//    return res;
//}

//inline void QrThreadPool::enqueue_asyc(std::function<void * ()> task, std::function<void (void *)> callback)
//{
//    {
//        std::unique_lock<std::mutex> lock(queue_mutex);

//        // don't allow enqueueing after stopping the pool
//        if(stop){
//            throw std::runtime_error("enqueue on stopped threadpool");
//        }

//        callbacks[taskid] = callback;
//        int cur_taskid = taskid;
//        tasks.emplace([this, task, cur_taskid](){
//            auto data = task();
//            notify_callback(cur_taskid, (void *)(data));
//        });

//        {
//            std::unique_lock<std::mutex> lock(taskid_mutex);
//            if(++taskid > callbacklimit) {
//                taskid = 0;
//            }
//        }
//    }
//    condition.notify_one();
//}

//inline void QrThreadPool::notify_callback(long taskid, void *data)
//{
//    {
//        std::unique_lock<std::mutex> lock(taskid_mutex);
//        if(callbacks.end() == callbacks.find(taskid)) {
//            return;
//        }
//    }

//    callbacks[taskid](data);
//}

//// the destructor joins all threads
//inline QrThreadPool::~QrThreadPool()
//{
//    {
//        std::unique_lock<std::mutex> lock(queue_mutex);
//        stop = true;
//    }
//    condition.notify_all();
//    for(std::thread &worker: workers){
//        worker.join();
//    }
//}

//#endif  //  QRTHREADPOOL_INL
