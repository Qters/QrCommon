#ifndef QRAUTORUN_H
#define QRAUTORUN_H


#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QrAutoRunPrivate;

/*!
 * \brief The QrAutoRun class
 * set application auto run or not when os start up
 */
class QRCOMMONSHARED_EXPORT QrAutoRun
{
    QR_DECLARE_PRIVATE(QrAutoRun)

public:
    QrAutoRun(const QString& appName);

public:
    bool isAutoRun() const;
    /*!
     * \brief autoRun
     * \param isAuto    auto run or not
     * \return
     */
    bool autoRun(bool isAuto);
    /*!
     * \brief resetRunApp
     * default value is qApp->applicationFilePath()
     * \param appPath
     */
    void resetRunApp(const QString& appPath);
};

NS_QRCOMMON_END

#endif // QRAUTORUN_H
