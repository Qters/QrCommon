#include "custom/qrcustomlanguagermanager.h"

#include <istream>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <list>

#include <QtWidgets/qapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qdebug.h>
#include <QtCore/qmutex.h>

#include "qrutf8.h"

#include "custom/qrcustomlanguagedicter.h"


NS_QRCOMMON_BEGIN

class QrCustomLanguagerManagerPrivate {
    QR_DECLARE_PUBLIC(QrCustomLanguagerManager)

public:
    QrCustomLanguagerManagerPrivate(QrCustomLanguagerManager *q) : q_ptr(q) {}

public:
    int preLanguageIndex = -1;
    int curLanguageIndex = -1;
    QString relativePath;
    QVector<QrCustomLanguagerData> languageDatas;

public:
    std::list<ILanguageChangeListener*> listeners;
    std::map<int, QrCustomLanguageDicter*> languageDicts;
    std::map<int, QString> dictResources;
    QrCustomLanguageDicter *currentLanguageDicter = nullptr;

    QMutex curDicterMutex;
    QMutex listenerMutex;
};

NS_QRCOMMON_END


USING_NS_QRCOMMON;

QR_SINGLETON_IMPLEMENT(QrCustomLanguagerManager)

QrCustomLanguagerManager::QrCustomLanguagerManager()
    : QrCommon::QrSingleton<QrCustomLanguagerManager>("QrCustomLanguagerManager"),
      d_ptr(new QrCustomLanguagerManagerPrivate(this))
{
}

QrCustomLanguagerManager::~QrCustomLanguagerManager()
{
    Q_D(QrCustomLanguagerManager);

    d->dictResources.clear();
    d->listeners.clear();

    std::map<int, QrCustomLanguageDicter*>::iterator it;
    while(d->languageDicts.begin() != d->languageDicts.end())
    {
        it = d->languageDicts.begin();
        QrCustomLanguageDicter *dicter = it->second;
        delete dicter;
        d->languageDicts.erase(it);
    }
}

void QrCustomLanguagerManager::setRelativePathOfLanguageFiles(const QString &path)
{
    Q_D(QrCustomLanguagerManager);
    d->relativePath = path;
}

int QrCustomLanguagerManager::addLanguage(const QrCustomLanguagerData& data)
{
    Q_D(QrCustomLanguagerManager);
    d->languageDatas.push_back(data);

    int index = d->languageDatas.size() - 1;
    d->dictResources[index] = d->relativePath + QDir::separator() + data.filename;

    loadLanguage(index);

    return index;
}

QStringList QrCustomLanguagerManager::displayNames() const
{
    Q_D(const QrCustomLanguagerManager);
    QStringList names;
    Q_FOREACH(QrCustomLanguagerData data, d->languageDatas) {
        names.push_back(data.displayName);
    }
    return names;
}

int QrCustomLanguagerManager::size() const
{
    Q_D(const QrCustomLanguagerManager);
    return d->languageDatas.size();
}

QrCustomLanguagerData QrCustomLanguagerManager::languageDataOf(int index) const
{
    Q_D(const QrCustomLanguagerManager);
    if(index > (d->languageDatas.size()-1)) {
        return QrCustomLanguagerData();
    }
    return d->languageDatas.at(index);
}

QrCustomLanguagerData QrCustomLanguagerManager::preLanguage() const
{
    Q_D(const QrCustomLanguagerManager);
    if(d->languageDatas.isEmpty()) {
        return QrCustomLanguagerData();
    }
    return d->languageDatas[d->preLanguageIndex];
}

QrCustomLanguagerData Qters::QrCommon::QrCustomLanguagerManager::curLanguage() const
{
    Q_D(const QrCustomLanguagerManager);

    if(d->languageDatas.isEmpty()) {
        return QrCustomLanguagerData();
    }

    return d->languageDatas[d->curLanguageIndex];
}

bool QrCustomLanguagerManager::loadLanguage(int index)
{
    Q_D(QrCustomLanguagerManager);

    if(d->languageDicts.find(index) == d->languageDicts.end()
            && d->dictResources.find(index) != d->dictResources.end()) {
        QrCustomLanguageDicter *dicter = new QrCustomLanguageDicter(d->dictResources[index]);
        dicter->load();
        d->languageDicts[index] = dicter;
        return true;
    }
    return false;
}

bool QrCustomLanguagerManager::switchLanguage(int index)
{
    Q_D(QrCustomLanguagerManager);

    if(index > (d->languageDatas.size()-1)) {
        return false;
    }

    d->preLanguageIndex = d->curLanguageIndex;
    d->curLanguageIndex = index;

    if(d->languageDicts.find(index) != d->languageDicts.end()) {
        {
            QMutexLocker lock(&(d->curDicterMutex));
            d->currentLanguageDicter = d->languageDicts[index];
        }

        dispatchLanguageChangeEvent();
        return true;
    } else {
        if(loadLanguage(index)) {
            {
                QMutexLocker lock(&(d->curDicterMutex));
                d->currentLanguageDicter = d->languageDicts[index];
            }
            dispatchLanguageChangeEvent();
            return true;
        }
    }

    return false;
}

QString QrCustomLanguagerManager::getValue(const QString &key, const QString& defaultValue)
{
    Q_D(QrCustomLanguagerManager);

    QMutexLocker lock(&(d->curDicterMutex));
    if(d->currentLanguageDicter != nullptr) {
       return d->currentLanguageDicter->getValue(key, defaultValue);
    }

    return defaultValue;
}

void QrCustomLanguagerManager::regLanguageChangeListener(ILanguageChangeListener *listener)
{
    Q_D(QrCustomLanguagerManager);

    QMutexLocker lock(&(d->listenerMutex));
    d->listeners.push_back(listener);
}

void QrCustomLanguagerManager::unRegLanguageChangeListener(ILanguageChangeListener *listener)
{
    Q_D(QrCustomLanguagerManager);

    QMutexLocker lock(&(d->listenerMutex));
    d->listeners.remove(listener);
}

void QrCustomLanguagerManager::dispatchLanguageChangeEvent()
{
    Q_D(QrCustomLanguagerManager);

    QMutexLocker lock(&(d->listenerMutex));

    std::list<ILanguageChangeListener*>::iterator it;
    for(it = d->listeners.begin(); it != d->listeners.end(); it++){
        ILanguageChangeListener* listener = (*it);
        listener->onLanguageChange();
    }
}
