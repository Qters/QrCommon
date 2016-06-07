#include "auxiliary/qrfiler.h"

#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtWidgets/qapplication.h>

USING_NS_QRCOMMON;

bool QrFiler::fileExists(const QString& path)
{
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return checkFile.exists() && checkFile.isFile();
}

bool QrFiler::getFileFolder(const QString& filePath, QString *fileFolder, bool autoCreate /*= true*/)
{
    int folderIdx = -1;
    if (-1 == (folderIdx = filePath.lastIndexOf('/')) ) {
        return false;
    }

    *fileFolder = filePath.left(folderIdx + 1);
    if ("./" == *fileFolder) {
        *fileFolder = QApplication::applicationFilePath();
    }

    if (autoCreate) {
        if (! QDir(*fileFolder).exists()) {
            QDir().mkdir(*fileFolder);
        }
    }

    return true;
}
