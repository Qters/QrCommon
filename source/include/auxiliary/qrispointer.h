#ifndef QRISPOINTER_H
#define QRISPOINTER_H

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

/*!
 *  Demo:
 *
 *  bool ispointer = QrIsPointer<Qt::HANDLE>::value;
 */

template <typename T>
struct QrIsPointer {
    static const bool value = false;
};

template <typename T>
struct QrIsPointer<T*> {
    static const bool value = true;
};

NS_QRCOMMON_END

#endif // QRISPOINTER_H

