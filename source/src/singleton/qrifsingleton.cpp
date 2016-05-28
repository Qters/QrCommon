#include "singleton/qrifsingleton.h"

#include <QtCore/qcoreapplication.h>

#include "singleton/qrsingletoncontainer.h"

using namespace Qters::QrCommon;

QrIfSingleton::QrIfSingleton(const QString &_key)
    :key(_key)
{
    QrSingletonContainer::addSingleton (key, this);
}

QrIfSingleton::~QrIfSingleton(){
    QrSingletonContainer::removeSingleton (key);
}

void QrIfSingleton::init()
{
    static bool done = false;
    if ( !done && QCoreApplication::instance() ) {
        done = true;
        QrSingletonContainer::singletonize ();
    }
}
