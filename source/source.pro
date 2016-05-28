QT       -= gui

TARGET = QrCommon
TEMPLATE = lib

DEFINES += QRCOMMON_LIBRARY

include($$PWD/../config.pri)
include($$PWD/../output.pri)

INCLUDEPATH += \
    $$PWD/include \
    $$PWD/inl \

SOURCES += \
    inl/singleton/qrsingleton.inl \
    src/singleton/qrifsingleton.cpp \
    src/singleton/qrsingletoncontainer.cpp \
    src/auxiliary/qrfiler.cpp \
    inl/auxiliary/qrcontainer.inl \
    inl/auxiliary/qrconverter.inl

HEADERS += \
    include/qrcommon_global.h \
    include/qrglobal.h \
    include/qrutf8.h \
    include/singleton/qrifsingleton.h \
    include/singleton/qrsingleton.h \
    include/singleton/qrsingletoncontainer.h \
    include/auxiliary/qrfiler.h \
    include/auxiliary/qrispointer.h \
    include/auxiliary/qrconverter.h \
    include/auxiliary/qrcontainer.h
