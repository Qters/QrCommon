#ifndef QRISPOINTER_H
#define QRISPOINTER_H

namespace Qters {

namespace QrCommon {

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

}   //  namespace QrCommon

}   //  namespace Qters


#endif // QRISPOINTER_H

