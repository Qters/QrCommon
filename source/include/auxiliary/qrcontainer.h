#ifndef QRCONTAINER_H
#define QRCONTAINER_H


#include <QtCore/qvector.h>

namespace Qters {

namespace QrCommon {

template <typename T>
class QrContainerOperate {
public:
    QVector<T> intersection(const QVector<QVector<T> >& datas);
};

template <class T>
class QrContianerConverter {
public:
    static void vectorToList(const QVector<T>& from, QList<T> *to);
    static void listToVector(const QList<T>& from, QVector<T> *to);

    static void stringListToVector(const QStringList& from, QVector<T> *to);
    static void vectorToStringList(const QVector<T>& from, QStringList *to);
};

}   //  namespace QrCommon

}   //  namespace Qters

#include "auxiliary/qrcontainer.inl"

#endif // QRCONTAINER_H
