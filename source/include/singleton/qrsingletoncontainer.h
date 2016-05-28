#ifndef QRSINGLETONCONTAINER_H
#define QRSINGLETONCONTAINER_H


#include <QtCore/qhash.h>

#include "qrcommon_global.h"
#include "singleton/qrsingleton.h"

namespace Qters {

namespace QrCommon {

/*!
 * \brief singleton object's container, contain all singleton object defined in project,
 * it is responsible for release all singleton object.
 */
class QRCOMMONSHARED_EXPORT QrSingletonContainer : public QrSingleton<QrSingletonContainer>
{
    friend class QrIfSingleton;

    QR_SINGLETON_DEFINE(QrSingletonContainer)

private:
    QrSingletonContainer();
    virtual ~QrSingletonContainer() = default;

private:
    static bool addSingleton(const QString& key, QrIfSingleton *singleton);
    static bool removeSingleton(const QString& key);
    static void removeAllSingleton();

private:
    static QMutex mutexSingletonContainer;
    static QHash<QString, QrIfSingleton *> mapSingletonContainer;
};

}   //  namespace QrCommon

}   //  namespace Qters

#endif // QRSINGLETONCONTAINER_H
