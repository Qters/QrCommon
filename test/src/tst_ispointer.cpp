#include "tst_ispointer.h"

#include <QtTest>

#include "auxiliary/qrispointer.h"

USING_NS_QRCOMMON;

void tst_ispointer::ispointer()
{
    QCOMPARE(QrIsPointer<Qt::HANDLE>::value, true);
}
