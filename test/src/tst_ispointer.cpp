#include "tst_ispointer.h"

#include <QtTest>

#include "auxiliary/qrispointer.h"

using namespace Qters::QrCommon;

void tst_ispointer::ispointer()
{
    QCOMPARE(QrIsPointer<Qt::HANDLE>::value, true);
}
