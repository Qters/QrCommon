#ifndef QRCONVERT_INL
#define QRCONVERT_INL

#include "qrcommon_global.h"

USING_NS_QRCOMMON;

template <typename T>
T *QrVariantPoniter<T>::asPoniter(QVariant v)
{
    return  (T *) v.value<void *>();
}

template <typename T>
QVariant QrVariantPoniter<T>::asQVariant(T *ptr)
{
    return qVariantFromValue((void *) ptr);
}

#endif //   QRCONVERT_INL
