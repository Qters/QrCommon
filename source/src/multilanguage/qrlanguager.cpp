#include "qrlanguager.h"

#include <algorithm>

#include <QtCore/qsettings.h>
#include <QTranslator>
#include <qapplication.h>
#include <QtCore/qdebug.h>

#include "qrutf8.h"

NS_QRCOMMON_BEGIN

class QrLanguagerPrivate
{
    QR_DECLARE_PUBLIC(QrLanguager)

public:
    int curLanaugeIndex = -1;
    QVector<QrLanguagData> languageDatas;

    QTranslator translator;

public:
    QrLanguagerPrivate(QrLanguager *q) : q_ptr(q) {}
    bool loadLanguage(const QString &qmFileName);
};

bool QrLanguagerPrivate::loadLanguage(const QString& qmFileName)
{
    qApp->removeTranslator(&translator);

    auto absFileName = QApplication::applicationDirPath() + "/translations/" + qmFileName;
    if(translator.load(absFileName)){
        return qApp->installTranslator(&translator);
    } else {
        qDebug() << "load language fail, " << absFileName;
    }

    return false;
}

NS_QRCOMMON_END


///////////////////////////////////////////////////////

USING_NS_QRCOMMON;

QR_SINGLETON_IMPLEMENT(QrLanguager)

QrLanguager::QrLanguager()
    : QrSingleton<QrLanguager>("qrlanguager"),
      d_ptr(new QrLanguagerPrivate(this))
{
}

void QrLanguager::initLanguages(const QVector<QrLanguagData> &languageDatas)
{
    Q_D(QrLanguager);
    d->languageDatas = languageDatas;
    if(d->languageDatas.isEmpty()) {
        d->curLanaugeIndex = -1;
    } else {
        d->curLanaugeIndex = 0;
    }
}

bool QrLanguager::setLanguageByName(const QString& display)
{
    Q_D(QrLanguager);
    auto find = std::find_if(d->languageDatas.begin(), d->languageDatas.end(),
             [display](QrLanguagData languageData){
        return languageData.display == display;
    });
    if(d->languageDatas.end() == find) {
        qDebug() << "fail to set language, could'nt find by " << display;
        return false;
    }

    return d->loadLanguage(find->qmFileName);
}

bool QrLanguager::setLanaugeByIndex(int index)
{
    Q_D(QrLanguager);
    auto find = std::find_if(d->languageDatas.begin(), d->languageDatas.end(),
             [index](QrLanguagData languageData){
        return languageData.index == index;
    });
    if(d->languageDatas.end() == find) {
        qDebug() << "fail to set language, could'nt find by " << index;
        return false;
    }

    return d->loadLanguage(find->qmFileName);
}

QrLanguagData QrLanguager::curLanguage() const
{
    Q_D(const QrLanguager);
    if(d->curLanaugeIndex >= d->languageDatas.count()) {
        qDebug() << "language index is unvalid.";
        return QrLanguagData();
    }

    return d->languageDatas.at(d->curLanaugeIndex);
}

QStringList QrLanguager::getDisplayNames() const
{
    QStringList names;
    Q_D(const QrLanguager);
    std::for_each(d->languageDatas.begin(),
              d->languageDatas.end(),
              [&names](QrLanguagData languageData){
        names.push_back(languageData.display);
    });
    return names;
}
