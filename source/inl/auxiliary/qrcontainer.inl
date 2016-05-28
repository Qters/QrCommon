#ifndef QRCONTAINER_INL
#define QRCONTAINER_INL

#include <QtCore/qvector.h>
#include <QtCore/qalgorithms.h>

#include <algorithm>

using namespace Qters::QrCommon;

template <typename T>
QVector<T> QrContainerOperate<T>::intersection(const QVector<QVector<T> > &datas)
{
    QVector<QVector<T> > copy;
    if (datas.isEmpty ()) {
        return QVector<T>();
    }

    Q_FOREACH(QVector<T> data, datas) {
        if (data.isEmpty ()) {
            continue;
        }
        qSort(data);
        copy.push_back (data);
    }

    if (copy.isEmpty ()) {
        return QVector<T>();
    }

    if (copy.count () < 2) {
        return copy.at (0);
    }

    QVector<T> result;
    for (int idx = 0; idx < copy.count ()-1; ++idx) {
        QVector<T> first = copy.at (idx);
        QVector<T> second = copy.at (idx+1);
        std::set_intersection(first.begin (), first.end (),
                              second.begin (), second.end (),
                              std::back_inserter(result));
    }

    return result;
}


void QrContianerConverter::vectorToList(const QVector<T> &from, QList<T> *to) {
    to->clear ();
    Q_FOREACH(T val, from) {
        to->push_back (val);
    }
}

void QrContianerConverter::listToVector(const QList<T> &from, QVector<T> *to) {
    to->clear ();
    Q_FOREACH(T val, from) {
        to->push_back (val);
    }
}

void QrContianerConverter::stringListToVector(const QStringList &from, QVector<T> *to) {
    to->clear ();
    Q_FOREACH(QString val, from) {
        to->push_back (val);
    }
}

void QrContianerConverter::vectorToStringList(const QVector<T> &from, QStringList *to) {
    to->clear ();
    Q_FOREACH(T val, from) {
        QVariant temp(val);
        to->push_back (temp.toString ());
    }
}

#endif  //  QRCONTAINER_INL
