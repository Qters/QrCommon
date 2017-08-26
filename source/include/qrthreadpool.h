#ifndef QRTHREADPOOL_H
#define QRTHREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

/*!
 * \brief The QrThreadPool class
 *
 * from https://github.com/progschj/ThreadPool/
 *
 * #include <iostream>
 * #include <vector>
 * #include <chrono>
 *
 * #include "qrthreadpool.h"
 *
 * int main()
 * {
 *     QrThreadPool pool(4);
 *     std::vector< std::future<int> > results;
 *
 *     for(int i = 0; i < 8; ++i) {
 *         results.emplace_back(
 *             pool.enqueue([i] {
 *                 std::cout << "hello " << i << std::endl;
 *                 std::this_thread::sleep_for(std::chrono::seconds(1));
 *                 std::cout << "world " << i << std::endl;
 *                 return i*i;
 *             })
 *         );
 *     }
 *
 *     for(auto && result: results)
 *         std::cout << result.get() << ' ';
 *     std::cout << std::endl;
 *
 *     return 0;
 * }
 *
 */
class QrThreadPool {
public:
    QrThreadPool(size_t);
    ~QrThreadPool();

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

NS_QRCOMMON_END

#include "qrthreadpool.inl"

#endif // QRTHREADPOOL_H
