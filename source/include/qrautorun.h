#ifndef QRAUTORUN_H
#define QRAUTORUN_H


#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QrAutoRunPrivate;

class QRCOMMONSHARED_EXPORT QrAutoRun
{
    QR_DECLARE_PRIVATE(QrAutoRun)

public:
    QrAutoRun(const QString& appName);

public:
    bool isAutoRun() const;
    void autoRun(bool isAuto);
    void resetAppPath(const QString& path);
};

NS_QRCOMMON_END

#endif // QRAUTORUN_H
