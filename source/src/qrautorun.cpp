#include "qrautorun.h"

#include <QtCore/qdebug.h>
#include <QtCore/qdir.h>
#include <QtWidgets/qapplication.h>

#ifdef Q_OS_WIN32
#include <QtCore/qsettings.h>
#elif Q_OS_MAC
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#endif

NS_QRCOMMON_BEGIN

class QrAutoRunPrivate{
public:
    QString appName;
    QString appPath;

#ifdef Q_OS_WIN32
    const QString regKey = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
#endif

public:
#ifdef Q_OS_MAC
    void writePlist();
    QString plistPath();
#endif
};

#ifdef Q_OS_MAC
bool QrAutoRunPrivate::writePlist()
{
    QFile file(plistPath());
    if(! file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDbug() << "auto run, fail to write plist.";
        return false;
    }

    QTextStream txtOutput(&file);
    txtOutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    txtOutput << "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" << endl;
    txtOutput << "<plist version=\"1.0\">" << endl;
    txtOutput << "<dict>" << endl;
    txtOutput << "	<key>Label</key>" << endl;
    txtOutput << QString("	<string>%1</string>").arg(appName) << endl;
    txtOutput << "	<key>ProgramArguments</key>" << endl;
    txtOutput << "	<array>" << endl;
    txtOutput << QString("		<string>%1</string>").arg(appPath) << endl;
    txtOutput << "	</array>" << endl;
    txtOutput << "	<key>ProcessType</key>" << endl;
    txtOutput << "	<string>Interactive</string>" << endl;
    txtOutput << "	<key>RunAtLoad</key>" << endl;
    txtOutput << "	<true/>" << endl;
    txtOutput << "	<key>KeepAlive</key>" << endl;
    txtOutput << "	<false/>" << endl;
    txtOutput << "</dict>" << endl;
    txtOutput << "</plist>" << endl;
    file.close();

    return true;
}

QString QrAutoRunPrivate::plistPath()
{
    return QString("%1/Library/LaunchAgents/%2.plist")
            .arg(QDir::homePath())
            .arg(appName);
}
#endif

NS_QRCOMMON_END

////////////////////////////////////////////////////

USING_NS_QRCOMMON;

QrAutoRun::QrAutoRun(const QString& appName)
    : d_ptr(new QrAutoRunPrivate())
{
    Q_D(QrAutoRun);
    d->appName = appName;
    d->appPath = qApp->applicationFilePath();
}

bool QrAutoRun::isAutoRun() const
{
    Q_D(const QrAutoRun);

#ifdef Q_OS_WIN32
    QSettings reg(d->regKey, QSettings::NativeFormat);
    return reg.contains(d->appName);
#elif Q_OS_MAC
    return QFile::exists(d->plistPath());
#endif

    return false;
}

void QrAutoRun::autoRun(bool isAuto)
{
    Q_D(QrAutoRun);
#ifdef Q_OS_WIN32
    QSettings registry(d->regKey, QSettings::NativeFormat);
    if(isAuto) {
        registry.setValue(d->appName, QDir::toNativeSeparators(d->appPath));
    } else {
        registry.remove(d->appName);
    }
    registry.sync();
#elif Q_OS_MAC
    if(isAuto) {
        d->writePlist();
    } else {
        QFile::remove(d->plistPath());
    }
#endif
}

void QrAutoRun::resetAppPath(const QString &path)
{
    Q_D(QrAutoRun);
    d->appPath = path;
}
