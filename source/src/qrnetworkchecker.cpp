#include "qrnetworkchecker.h"

#include <QtCore/qdebug.h>
#include <QtCore/qthread.h>
#include <QtCore/qfuture.h>
#include <QtConcurrent/QtConcurrent>
#include <QtNetwork/qnetworkinterface.h>

#include "qrutf8.h"

NS_QRCOMMON_BEGIN

class QrNetworkCheckerPrivate {
    QR_DECLARE_PUBLIC(QrNetworkChecker)

public:
    QrNetworkChecker::State currentState = QrNetworkChecker::Stopped;
    QrNetworkChecker::State previousState = QrNetworkChecker::Stopped;

    int ifaceIndex = 0;
    QTimer checkTimer;
    const int checkTime = 1000*3;

public:
    QrNetworkCheckerPrivate(QrNetworkChecker *q);
    QrNetworkChecker::State getState();
    void init();
};

void QrNetworkCheckerPrivate::init()
{
    Q_Q(QrNetworkChecker);

    q->connect(&checkTimer, &QTimer::timeout, [this](){
        Q_Q(QrNetworkChecker);
        currentState = getState();
        if(previousState != currentState) {
            previousState = currentState;
            qDebug() << "network state change : " << currentState;
            emit q->sig_change(currentState);
        }
    });

    checkTimer.start(checkTime);
    Q_FOREACH(auto iface, QNetworkInterface::allInterfaces()) {
        qDebug() << "init iface: " << iface;
        if(! iface.flags().testFlag(QNetworkInterface::IsUp)
                || iface.hardwareAddress().isEmpty()
                || iface.humanReadableName().toLower().contains("vmware")) {
            continue;
        }
        ifaceIndex = iface.index();
        break;
    }

    currentState = getState();
    previousState = currentState;
}

QrNetworkCheckerPrivate::QrNetworkCheckerPrivate(QrNetworkChecker *q)
    : q_ptr(q) {}

QrNetworkChecker::State QrNetworkCheckerPrivate::getState()
{
    QrNetworkChecker::State state = currentState;

    QNetworkInterface iface (QNetworkInterface::interfaceFromIndex(ifaceIndex));
    if(iface.isValid()) {
        if ( iface.flags().testFlag(QNetworkInterface::IsRunning)) {
            state = QrNetworkChecker::Running;
        } else {
            state = QrNetworkChecker::Stopped;
        }
    } else {
        qDebug() << "iface is unvalid : " << iface;
        state = QrNetworkChecker::Stopped;
    }

    return state;
}

NS_QRCOMMON_END

////////////////////////////////////////

USING_NS_QRCOMMON;

QrNetworkChecker *QrNetworkChecker::instance()
{
    static QrNetworkChecker networkChecker;
    return &networkChecker;
}

QrNetworkChecker::QrNetworkChecker()
    : d_ptr(new QrNetworkCheckerPrivate(this))
{
    Q_D(QrNetworkChecker);
    d->init();
}

QrNetworkChecker::State QrNetworkChecker::currentState() const
{
    Q_D(const QrNetworkChecker);
    return d->currentState;
}
