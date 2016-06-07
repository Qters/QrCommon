#ifndef QRCONVERT_H
#define QRCONVERT_H

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qlist.h>
#include <QtCore/qtextstream.h>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

/*!
 *  \brief  convert qt handle to qstring
 *
 *  QString curThreadId = QrStringCvter<Qt::HANDLE, QrIsPointer<Qt::HANDLE>::value>::toString (curThreadIdHandle);
 */
template <typename T, bool isPointer>
struct QrStringCvter{
    static QString toString(T t) {
        return QString::number (static_cast<qlonglong>(t));
    }
};

template <typename T>
struct QrStringCvter<T, true>{
    static QString toString(T t) {
        const void * ptr = static_cast<const void *>(t);
        QString value;
        QTextStream stream(& value);
        stream << ptr;
        return value;
    }
};

/*!
 *  converter of QVariant and Object pointer
 *
 * example:
 *
 * MyClass *p;
 * QVariant v = QrVariantPoniter<MyClass>::asQVariant(p);
 *
 * MyClass *p1 = QrVariantPoniter<MyClass>::asPtr(v);
 */
template <class T>
class QrVariantPoniter
{
public:
    static T* asPoniter(QVariant v);
    static QVariant asQVariant(T* ptr);
};

NS_QRCOMMON_END

#include "auxiliary/qrconverter.inl"

#endif // QRCONVERT_H
