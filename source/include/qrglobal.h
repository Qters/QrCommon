#ifndef QRGLOBAL
#define QRGLOBAL

#include <QtCore/qglobal.h>
#include <QtCore/qsharedpointer.h>

/*!
 *  Q_DECLARE_PRIVATE and d_ptr
 *
*/
#define QR_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    QSharedPointer<Class##Private> d_ptr;

/*!
 *  Q_DECLARE_PUBLIC and q_ptr
 *
*/
#define QR_DECLARE_PUBLIC(Class) \
    private: \
    Q_DECLARE_PUBLIC(Class) \
    Class* q_ptr;

#endif // QRGLOBAL

