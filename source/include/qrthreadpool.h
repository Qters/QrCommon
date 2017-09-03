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
 *     for(int i = 0; i < 8; ++i) {
 *         pool.enqueue_asyc([i](){
 *             qDebug() << "hello " << i;
 *             std::this_thread::sleep_for(std::chrono::seconds(1));
 *             qDebug() << "world " << i;
 *
 *             QVariant result;
 *             result.setValue(i*i);
 *             return result;
 *         }, [i](QVariant data){
 *             int result = data.value<int>();
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
    void enqueue_asyc(std::function<QVariant ()> task, std::function<void (QVariant)> callback);
};

NS_QRCOMMON_END

#endif // QRTHREADPOOL_H
