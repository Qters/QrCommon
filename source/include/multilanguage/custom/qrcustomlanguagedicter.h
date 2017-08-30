#ifndef QRCUSTOMLANGUAGEDICTER_H
#define QRCUSTOMLANGUAGEDICTER_H

#include <string>
#include <map>
#include <functional>

#include <QtCore/qstring.h>

#include "qrglobal.h"
#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QrCustomLanguageDicterPrivate;
class QRCOMMONSHARED_EXPORT QrCustomLanguageDicter
{
    QR_DECLARE_PRIVATE(QrCustomLanguageDicter)

public:
    QrCustomLanguageDicter(const QString &filePath);
    ~QrCustomLanguageDicter();

public:
    void setDecipherFunc(std::function<QString(QString)> func);
    QrCustomLanguageDicter* load();
    QrCustomLanguageDicter* reload();
    QString getValue(const QString &key, const QString& defaultValue);
};

NS_QRCOMMON_END

#endif // QRCUSTOMLANGUAGEDICTER_H
