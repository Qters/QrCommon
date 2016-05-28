#ifndef TST_ISPOINTER_H
#define TST_ISPOINTER_H

#include "qrtestsuitefactory.h"

class TESTSUITE(tst_ispointer) tst_ispointer : public QObject
{
    Q_OBJECT
private slots:
    void ispointer();
};

#endif // TST_ISPOINTER_H
