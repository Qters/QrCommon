#ifndef QRFILER_H
#define QRFILER_H

#include <QtCore/qstring.h>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QRCOMMONSHARED_EXPORT QrFiler
{
public:
    static bool fileExists(const QString& path);
    static bool getFileFolder(const QString &filePath, QString *fileFolder, bool autoCreate = true);
};

NS_QRCOMMON_END

#endif // QRFILER_H
