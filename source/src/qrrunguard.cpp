#include "qrrunguard.h"

#include <QCryptographicHash>

NS_QRCOMMON_BEGIN

class QrRunGuardPrivate{
public:
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;

public:
    QrRunGuardPrivate(const QString& key);
    QString generateKeyHash( const QString& key, const QString& salt );
};

QrRunGuardPrivate::QrRunGuardPrivate(const QString &key)
    : key( key )
    , memLockKey( generateKeyHash( key, "_memLockKey" ) )
    , sharedmemKey( generateKeyHash( key, "_sharedmemKey" ) )
    , sharedMem( sharedmemKey )
    , memLock( memLockKey, 1 )
{
    memLock.acquire();
    {
        QSharedMemory fix( sharedmemKey );    // Fix for *nix: http://habrahabr.ru/post/173281/
        fix.attach();
    }
    memLock.release();
}

QString QrRunGuardPrivate::generateKeyHash(const QString &key, const QString &salt)
{
    QByteArray data;

    data.append( key.toUtf8() );
    data.append( salt.toUtf8() );
    data = QCryptographicHash::hash( data, QCryptographicHash::Sha1 ).toHex();

    return data;
}

NS_QRCOMMON_END

////////////////////////////////////////////////////

USING_NS_QRCOMMON;

QrRunGuard::QrRunGuard( const QString& key )
    : d_ptr(new QrRunGuardPrivate(key))
{
}

QrRunGuard::~QrRunGuard()
{
    release();
}

bool QrRunGuard::isAnotherRunning()
{
    Q_D(QrRunGuard);
    if ( d->sharedMem.isAttached() ){
        return false;
    }

    d->memLock.acquire();
    const bool isRunning = d->sharedMem.attach();
    if ( isRunning )
        d->sharedMem.detach();
    d->memLock.release();

    return isRunning;
}

bool QrRunGuard::tryToRun()
{
    if ( isAnotherRunning() ){   // Extra check
        return false;
    }

    Q_D(QrRunGuard);
    d->memLock.acquire();
    const bool result = d->sharedMem.create( sizeof( quint64 ) );
    d->memLock.release();
    if ( ! result ) {
        release();
        return false;
    }

    return true;
}

void QrRunGuard::release()
{
    Q_D(QrRunGuard);
    d->memLock.acquire();
    if ( d->sharedMem.isAttached() ){
        d->sharedMem.detach();
    }
    d->memLock.release();
}
