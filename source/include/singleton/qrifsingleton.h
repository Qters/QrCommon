#ifndef QRIFSINGLETON_H
#define QRIFSINGLETON_H

#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QrSingletonContainer;

/*!
 * \brief Common interface for all singleton
 */

class QRCOMMONSHARED_EXPORT QrIfSingleton
{
    friend class QrSingletonContainer;

    Q_DISABLE_COPY(QrIfSingleton)

protected:
    QrIfSingleton(const QString& _key);
    virtual ~QrIfSingleton();

protected:
    static void init();
    virtual void deleteInstance() = 0;

private:
    QString key;    //  singleton key
};

NS_QRCOMMON_END

#endif // QRIFSINGLETON_H

