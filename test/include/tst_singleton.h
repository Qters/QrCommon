#ifndef TESTSINGLETON_H
#define TESTSINGLETON_H

#include "qrtestsuitefactory.h"

#define TEST_SINGLETON_DEFINE(CLASS_NAME) \
    void test##CLASS_NAME()

#define TEST_SINGLETON_IMPLEMENT(CLASS_NAME) \
    void tst_Singleton::test##CLASS_NAME() \
    { \
        CLASS_NAME *signleton = CLASS_NAME::getInstance (); \
        for (int var = 0; var < 10; ++var) { \
            QVERIFY( signleton == CLASS_NAME::getInstance ()); \
        } \
    } \


class TESTSUITE(tst_Singleton) : public QObject
{
    Q_OBJECT
private slots:
    TEST_SINGLETON_DEFINE(QrSingletonContainer);
};

#endif // TESTSINGLETON_H
