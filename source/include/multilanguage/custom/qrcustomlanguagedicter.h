#ifndef QRCUSTOMLANGUAGEDICTER_H
#define QRCUSTOMLANGUAGEDICTER_H

#include <string>
#include <map>

#include <QtCore/qstring.h>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QRCOMMONSHARED_EXPORT QrCustomLanguageDicter
{
public:
    QrCustomLanguageDicter(const std::string &filePath);
    ~QrCustomLanguageDicter();

public:
    QrCustomLanguageDicter* load();
    QrCustomLanguageDicter* reload();
    QString getValue(const QString &key, const QString& defaultValue);

private:
    void parserLine(const QString &line);

private:
    std::string filePath;
    bool isLoad = false;
    std::map<QString, QString> dict;
};

NS_QRCOMMON_END

#endif // QRCUSTOMLANGUAGEDICTER_H
