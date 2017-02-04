#ifndef QRLANGUAGER_H
#define QRLANGUAGER_H

#include <QtCore/qobject.h>
#include <QtCore/qlocale.h>

#include "qrglobal.h"
#include "singleton/qrsingleton.h"

NS_QRCOMMON_BEGIN

class QRCOMMONSHARED_EXPORT QrLanguagData {
public:
    int index = 0;  //  zero is the default language
    QString display;
    QString qmFileName;
    QLocale::Language locale;
};

/*!
 *  qm's file should be put in `applicationPath/translations`
 */
class QrLanguagerPrivate;
class QRCOMMONSHARED_EXPORT QrLanguager : public QObject, public QrSingleton<QrLanguager>
{
    Q_OBJECT

    QR_DECLARE_PRIVATE(QrLanguager)
    QR_SINGLETON_DEFINE(QrLanguager)

private:
    QrLanguager();

public:
    void initLanguages(const QVector<QrLanguagData>& languageDatas);

    bool setLanguageByName(const QString& display);
    bool setLanaugeByIndex(int index);

    QrLanguagData curLanguage() const;

    QStringList getDisplayNames() const;
};

NS_QRCOMMON_END

#endif // QRLANGUAGER_H
