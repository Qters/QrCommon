#ifndef QRSINGLETON_INL
#define QRSINGLETON_INL

#include <QtCore/qmutex.h>

#include "qrcommon_global.h"

USING_NS_QRCOMMON;

template <typename T> T * QrSingleton<T>::singleton = nullptr;
template <typename T> QMutex QrSingleton<T>::mutexSingleton;

template <typename T>
QrSingleton<T>::QrSingleton(const QString &sKey) : QrIfSingleton(sKey) {
    ;
}

template <typename T>
bool QrSingleton<T>::isSingletonNull() {
    return (singleton == nullptr);
}

template <typename T>
void QrSingleton<T>::deleteInstance() {
    QrSingleton<T>::deleteSingleton();
}

template <typename T>
T * QrSingleton<T>::singletonize()
{
   if (nullptr != singleton) {
      return singleton;
   }

   QrIfSingleton::init();
   QMutexLocker locker(QCoreApplication::instance() ? (& mutexSingleton) : nullptr);
   if (nullptr == singleton) {
       singleton = new T();
   }

   return singleton;
}

template <typename T>
void QrSingleton<T>::deleteSingleton()
{
   QMutexLocker locker(QCoreApplication::instance() ? (&mutexSingleton) : nullptr);
   if (nullptr == singleton) {
       return;
   }

   delete singleton;
   singleton = nullptr;
}


#endif  //  QRSINGLETON_INL
