#include "custom/qrcustomlanguagedicter.h"

#include <QtCore/qfile.h>
#include <QtCore/qmap.h>

NS_QRCOMMON_BEGIN

class QrCustomLanguageDicterPrivate {
    QR_DECLARE_PUBLIC(QrCustomLanguageDicter)

public:
    QrCustomLanguageDicterPrivate(QrCustomLanguageDicter *q, const QString &filePath)
    : q_ptr(q),
      filePath(filePath) {}

public:
    void parserOne(const QString &line);

public:
    QString filePath;
    bool isLoad = false;
    QMap<QString, QString> dict;

    bool useDecipherFunc = false;
    std::function<QString(QByteArray)> decipherFunc;
};

void QrCustomLanguageDicterPrivate::parserOne(const QString &line)
{
    QChar f1('/');
    QChar f2('#');
    QChar f3('=');
    QChar f4('"');

    QString lineCopy = line.trimmed();

    if(lineCopy.isNull() || lineCopy.isEmpty() || lineCopy.at(0) == f1 || lineCopy.at(0) == f2) {
        return;
    }

    int equalIdx = lineCopy.indexOf(f3);
    if(equalIdx!=-1) {
        QString strKey = lineCopy.mid(0,equalIdx).trimmed();
        QString strValue = lineCopy.mid(equalIdx+1).trimmed();
        if(strKey.startsWith(f4)
                &&strKey.endsWith(f4)
                &&strValue.startsWith(f4)
                &&strValue.endsWith(f4)) {
            QString strMapKey = strKey.mid(1,strKey.size() - 2);
            QString strMapValue = strValue.mid(1,strValue.size() - 2);
            dict[strMapKey] = strMapValue;
        }
    }
}



NS_QRCOMMON_END

USING_NS_QRCOMMON;

QrCustomLanguageDicter::QrCustomLanguageDicter(const QString &filePath)
    : d_ptr(new QrCustomLanguageDicterPrivate(this, filePath))
{
}

QrCustomLanguageDicter::~QrCustomLanguageDicter()
{
    Q_D(QrCustomLanguageDicter);
    d->dict.clear();
}

void QrCustomLanguageDicter::setDecipherFunc(std::function<QString (QByteArray)> func)
{
    Q_D(QrCustomLanguageDicter);
    d->useDecipherFunc = true;
    d->decipherFunc = func;
}

QrCustomLanguageDicter* QrCustomLanguageDicter::reload()
{
    Q_D(QrCustomLanguageDicter);

    d->isLoad = false;
    d->dict.clear();

    load();

    return this;
}

QrCustomLanguageDicter* QrCustomLanguageDicter::load()
{
    Q_D(QrCustomLanguageDicter);

    QFile readFile(d->filePath);
    if(! readFile.open(QIODevice::ReadOnly)) {
        return this;
    }

    QString fileContent;
    auto rawContent = readFile.readAll();
    readFile.close();

    if(d->useDecipherFunc) {
        fileContent = d->decipherFunc(rawContent);
    } else {
        fileContent = rawContent;
    }

    Q_FOREACH(QString one, fileContent.split(";")) {
        d->parserOne(one);
    }

    return this;
}

QString QrCustomLanguageDicter::getValue(const QString &key, const QString& defaultValue)
{
    Q_D(QrCustomLanguageDicter);

    if(d->dict.find(key) != d->dict.end()) {
        QString value = d->dict[key];
        if(value.isEmpty() && ! defaultValue.isEmpty()) {
            return defaultValue;
        }
        return value;
    }
    return defaultValue;
}
