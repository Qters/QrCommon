#ifndef NETWORKCHECKER_H
#define NETWORKCHECKER_H

#include <qtimer.h>

#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

/*!
 * realtime check network state(5s)
 */

class QrNetworkCheckerPrivate;
class QRCOMMONSHARED_EXPORT QrNetworkChecker : public QObject
{
    Q_OBJECT

    QR_DECLARE_PRIVATE(QrNetworkChecker)

public:
    static QrNetworkChecker* instance();

private:
    QrNetworkChecker();
    void init();

public:
    enum State{
        Stopped = 0,
        Running = 1,
    };
    State currentState() const;

Q_SIGNALS:
    /*!
     * \brief sig_change    0 for stopped, 1 for running
     */
    void sig_change(int);
};

NS_QRCOMMON_END

#endif // NETWORKCHECKER_H
