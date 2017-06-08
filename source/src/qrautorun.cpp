#include "qrautorun.h"

#include <QtWidgets/qapplication.h>
#include <QtCore/qsettings.h>
#include <QtCore/qdir.h>

NS_QRCOMMON_BEGIN

class QrAutoRunPrivate{
public:
    QString appName;

#ifdef Q_OS_WIN32
    const QString regKey = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
#endif
};

NS_QRCOMMON_END

////////////////////////////////////////////////////

USING_NS_QRCOMMON;

QrAutoRun::QrAutoRun(const QString& appName)
    : d_ptr(new QrAutoRunPrivate())
{
    Q_D(QrAutoRun);
    d->appName = appName;
}

bool QrAutoRun::isAutoRun() const
{
    Q_D(const QrAutoRun);
#ifdef Q_OS_WIN32
    QSettings reg(d->regKey, QSettings::NativeFormat);
    return reg.contains(d->appName);
#elif Q_OS_MAC

#endif
    return false;
}

void QrAutoRun::autoRun(bool _auto)
{
    Q_D(QrAutoRun);
#ifdef Q_OS_WIN32
        QSettings reg(d->regKey, QSettings::NativeFormat);
        if(_auto) {
            reg.setValue(d->appName, QDir::toNativeSeparators(qApp->applicationFilePath()));
        } else {
            reg.remove(d->appName);
        }
#elif Q_OS_MAC

#endif
}
