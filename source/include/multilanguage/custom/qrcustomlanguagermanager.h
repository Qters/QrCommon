#ifndef QRCUSTOMLANGUAGERMANAGER_H
#define QRCUSTOMLANGUAGERMANAGER_H

#include <QtCore/qlocale.h>

#include "qrglobal.h"

#include "qrcommon_global.h"
#include "singleton/qrsingleton.h"

#define QrLngTR(key,_comment) \
    ::Qters::QrCommon::QrCustomLanguagerManager::getInstance()->getValue(QString(key), QString(_comment)) \

#define QrLngReg(_this) \
    ::Qters::QrCommon::QrCustomLanguagerManager::getInstance()->regLanguageChangeListener(_this); \
    _this->onLanguageChange() \

#define QrLngUnReg(_this) \
    ::Qters::QrCommon::QrCustomLanguagerManager::getInstance()->unRegLanguageChangeListener(_this) \


NS_QRCOMMON_BEGIN

class QrCustomLanguageDicter;

class QRCOMMONSHARED_EXPORT ILanguageChangeListener{
public:
    virtual void onLanguageChange() = 0;
};

class QRCOMMONSHARED_EXPORT QrCustomLanguagerData {
public:
    QString filename;
    QLocale locale;
    QString displayName;
};

class QrCustomLanguagerManagerPrivate;
class QRCOMMONSHARED_EXPORT QrCustomLanguagerManager : public QrSingleton<QrCustomLanguagerManager>
{
    QR_DECLARE_PRIVATE(QrCustomLanguagerManager)
    QR_SINGLETON_DEFINE(QrCustomLanguagerManager)

private:
    QrCustomLanguagerManager();

public:
    ~QrCustomLanguagerManager();

public:
    /*!
     * \return language index of manager
     */
    int addLanguage(const QrCustomLanguagerData& data);
    bool switchLanguage(int index);
    void setRelativePathOfLanguageFiles(const QString& path);

    int size() const;
    QStringList displayNames() const;
    QrCustomLanguagerData languageDataOf(int index) const;
    QrCustomLanguagerData preLanguage() const;
    QrCustomLanguagerData curLanguage() const;

public:
    QString getValue(const QString &key, const QString& defaultValue);

    void regLanguageChangeListener(ILanguageChangeListener *listener);
    void unRegLanguageChangeListener(ILanguageChangeListener *listener);

private:
    bool loadLanguage(int index);
    void dispatchLanguageChangeEvent();
};

NS_QRCOMMON_END

#endif // QRCUSTOMLANGUAGERMANAGER_H
