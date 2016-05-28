#ifndef QRSINGLETON_H
#define QRSINGLETON_H

#include <QtCore/qmutex.h>
#include <QtCore/qcoreapplication.h>

#include "singleton/qrifsingleton.h"



namespace Qters {

namespace QrCommon {

/*!
 *
 * how to use:
 * 1. inherit QrSingleton<YOUR_CLASS>.
 * 2. define two macro in class, SINGLETON_DEFINE in header and SINGLETON_IMPLEMENT in cpp.
 *
 * example:
 * in classname.h:
 * #include "singleton/singleton.h"
 * class ClassName : public QrCommon::QrSingleton<ClassName>
 * {
 *  QR_SINGLETON_DEFINE(ClassName)
 *  private:
 *      ClassName();
 * };
 *
 * in classname.cpp:
 * QR_SINGLETON_IMPLEMENT(ClassName)
 *
 * constructor:
 * ClassName::ClassName()
 *     : QrCommon::QrSingleton<ClassName>("classname")
 * {}
 *
 * use:
 * ClassName::getInstance()->xxxfunction()
 */


/*!
  *
 * \brief Macro to make class be singleton
  */
#define QR_SINGLETON_DEFINE(CLASS_NAME) \
    public: \
        friend class QrCommon::QrSingleton<CLASS_NAME>; \
    public: \
        static CLASS_NAME* getInstance(); \

#define QR_SINGLETON_IMPLEMENT(CLASS_NAME) \
    CLASS_NAME *CLASS_NAME::getInstance() \
    { \
        return CLASS_NAME::singletonize (); \
    } \


/*!
 * \brief Concrete class to define a thread-safe singleton
 */
template <typename T>
class QrSingleton : public QrIfSingleton
{
protected:
    QrSingleton(const QString & sKey);
    virtual ~QrSingleton() = default;

private:
//    struct creator
//    {
//        creator(){
//            QrSingleton<T>::singletonize ();
//        }
//    };
//    static creator creator_;

protected:
    static T * singletonize();
    static void deleteSingleton();

protected:
    static bool isSingletonNull();
    virtual void deleteInstance();

private:
    static T *     singleton;
    static QMutex  mutexSingleton;
};

//template <typename T>
//typename QrSingleton<T>::creator QrSingleton<T>::creator_;

#include "singleton/qrsingleton.inl"


}   //  namespace QrCommon

}   //  namespace Qters

#endif // QRSINGLETON_H

