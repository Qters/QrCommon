
CONFIG += c++11

CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)

    DESTDIR = $$PWD/../Qters_debug/qrcommon
}
CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../Qters_release/qrcommon
}
