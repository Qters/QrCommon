#ifndef QRRUNGUARD_H
#define QRRUNGUARD_H

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QrRunGuardPrivate;

class QRCOMMONSHARED_EXPORT QrRunGuard
{
    Q_DISABLE_COPY(QrRunGuard)
    QR_DECLARE_PRIVATE(QrRunGuard)

public:
    QrRunGuard( const QString& key );
    ~QrRunGuard();

public:
    bool isAnotherRunning();
    bool tryToRun();
    void release();
};

NS_QRCOMMON_END

#endif // QRRUNGUARD_H
