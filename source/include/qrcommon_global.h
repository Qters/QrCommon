#ifndef QRCOMMON_GLOBAL_H
#define QRCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRCOMMON_LIBRARY)
#  define QRCOMMONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRCOMMONSHARED_EXPORT Q_DECL_IMPORT
#endif

//  qrcommon namespace
#define NS_QRCOMMON_BEGIN \
    namespace Qters { \
    namespace QrCommon {
#define NS_QRCOMMON_END \
    } \
    }
#define USING_NS_QRCOMMON    using namespace Qters::QrCommon
#define NS_QRCOMMON  ::Qters::QrCommon

#endif // QRCOMMON_GLOBAL_H
