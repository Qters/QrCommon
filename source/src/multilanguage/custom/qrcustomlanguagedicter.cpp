#include "custom/qrcustomlanguagedicter.h"

#include <fstream>

USING_NS_QRCOMMON;

QrCustomLanguageDicter::QrCustomLanguageDicter(const std::string &filePath)
    : filePath(filePath.c_str())
{
}

QrCustomLanguageDicter::~QrCustomLanguageDicter()
{
    dict.clear();
}

QrCustomLanguageDicter* QrCustomLanguageDicter::reload()
{
    isLoad = false;
    dict.clear();
    load();

    return this;
}

QrCustomLanguageDicter* QrCustomLanguageDicter::load()
{
    std::wifstream fin(filePath.c_str());

    wchar_t wcharArr[1024] ={0};
    while(fin.is_open() && !fin.eof()) {
        fin.getline(wcharArr,1024);
        parserLine(QString::fromUtf8(QString::fromWCharArray(wcharArr).toLatin1()));
    }
    fin.close();

    return this;
}

QString QrCustomLanguageDicter::getValue(const QString &key, const QString& defaultValue)
{
    if(dict.find(key) != dict.end()) {
        QString value = dict[key];
        if(value.isEmpty() && ! defaultValue.isEmpty()) {
            return defaultValue;
        }
        return value;
    }
    return defaultValue;
}

void QrCustomLanguageDicter::parserLine(const QString &line)
{
    QChar f1('/');
    QChar f2('#');
    QChar f3('=');
    QChar f4('"');
    QString f5("\";");

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
                &&strValue.endsWith(f5)) {
            QString strMapKey = strKey.mid(1,strKey.size() - 2);
            QString strMapValue = strValue.mid(1,strValue.size() - 3);
            dict[strMapKey] = strMapValue;
        }
    }
}

