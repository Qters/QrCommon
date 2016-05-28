#include "singleton/qrsingletoncontainer.h"

#include <QtCore/QMutexLocker>
#include <QtCore/qdebug.h>

using namespace Qters::QrCommon;

QHash<QString, QrIfSingleton*> QrSingletonContainer::mapSingletonContainer;
QMutex QrSingletonContainer::mutexSingletonContainer;

QR_SINGLETON_IMPLEMENT(QrSingletonContainer)

QrSingletonContainer::QrSingletonContainer()
    :QrSingleton<QrSingletonContainer>("qrsingtoncontainer")
{
    //  the registered function will call after main finish
    int iResult = std::atexit(& QrSingletonContainer::removeAllSingleton);
    Q_ASSERT( 0 == iResult );
    Q_UNUSED(iResult);
}

bool QrSingletonContainer::addSingleton(const QString &key, QrIfSingleton *singleton)
{
    QMutexLocker locker( QCoreApplication::instance () ? (&mutexSingletonContainer) : nullptr);
    bool exist = mapSingletonContainer.contains (key);
    Q_ASSERT(! exist && ! key.isEmpty ());

    if ( nullptr == singleton || exist || key.isEmpty ()) {
        return false;
    }

    mapSingletonContainer.insert (key, singleton);
    return true;
}

bool QrSingletonContainer::removeSingleton(const QString &key)
{
    QMutexLocker locker( QCoreApplication::instance () ? (&mutexSingletonContainer) : nullptr);
    //Q_ALIGNOF(mapSingletonContainer.contains (key));

    return mapSingletonContainer.remove (key) > 0;
}

void QrSingletonContainer::removeAllSingleton()
{
    QMutexLocker locker( QCoreApplication::instance () ? (&mutexSingletonContainer) : nullptr);
    Q_FOREACH (QrIfSingleton *singleton, mapSingletonContainer) {
        if (nullptr != singleton && singleton != QrSingletonContainer::getInstance ()) {
            singleton->deleteInstance ();
        }
    }

    QrSingletonContainer::deleteSingleton ();
    mapSingletonContainer.clear ();
}
