#ifndef QRTHREADPOOL_H
#define QRTHREADPOOL_H

#include <functional>

#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

/*!
 * \brief The QrThreadPool class
 *
 * from https://github.com/progschj/ThreadPool/
 *
 * #include <iostream>
 * #include <vector>
 * #include <thread>
 * #include <chrono>
 *
 * #include "qrthreadpool.h"
 *
 * USING_NS_QRCOMMON;
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
 *
 * int main()
 * {
 *     QrThreadPool pool(4);
 *     for(int i = 0; i < 8; ++i) {
 *         pool.enqueue_asyc([i](){
 *             qDebug() << "hello " << i;
 *             std::this_thread::sleep_for(std::chrono::seconds(1));
 *             qDebug() << "world " << i;
 *             return (void *)(i*i);
 *         }, [i](void * data){
 *             int result = int(data);
 *             qDebug() << "hello world " << i << " finish, result is: " << result;
 *         });
 *     }
 *
 *     return 0;
 * }
 *
 */
class QrThreadPoolPrivate;
class QRCOMMONSHARED_EXPORT QrThreadPool {
    QR_DECLARE_PRIVATE(QrThreadPool)

public:
    QrThreadPool(size_t);
    ~QrThreadPool();

public:
    //  asyc enqueue, result pass as void *
    void enqueue_asy(std::function<void ()> task);
    void enqueue_asyc(std::function<void * ()> task, std::function<void (void *)> callback);
};

NS_QRCOMMON_END

#endif // QRTHREADPOOL_H
