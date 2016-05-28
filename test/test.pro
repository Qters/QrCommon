CONFIG   += console
CONFIG   -= app_bundle

QT += testlib

QR_TEST_PRO = $$PWD/../../QrTest/source
QR_COMMON_PRO = $$PWD/../source

include($$PWD/../config.pri)

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_debug_qrtest/ -lQrTestd \
        -L$$QR_COMMON_PRO/../../build_debug_qrcommon/ -lQrCommond \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_release_qrtest/ -lQrTest \
        -L$$QR_COMMON_PRO/../../build_release_qrcommon/ -lQrCommon \
}

INCLUDEPATH += \
    $$PWD/include \
    $$QR_TEST_PRO\include \
    $$QR_COMMON_PRO\include \
    $$QR_COMMON_PRO\inl \

HEADERS += \
    include/tst_converter.h \
    include/tst_ispointer.h \
    include/tst_singleton.h

SOURCES += \
    src/main.cpp \
    src/tst_converter.cpp \
    src/tst_ispointer.cpp \
    src/tst_singleton.cpp

