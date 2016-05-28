#ifndef QRFILER_H
#define QRFILER_H

#include <QtCore/qstring.h>

#include "qrcommon_global.h"

namespace Qters {

namespace QrCommon {

class QRCOMMONSHARED_EXPORT QrFiler
{
public:
    static bool fileExists(const QString& path);
    static bool getFileFolder(const QString &filePath, QString *fileFolder, bool autoCreate = true);
};

}   //  namespace QrCommon

}   //  namespace Qters


#endif // QRFILER_H
