TARGET = qtmultiprocesssystem_watchdog
TARGETPATH = QtMultiProcessSystem/WatchDog
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = qml multiprocesssystem

SOURCES += \
        mainthreadwatchdog.cpp \
        watchdog_plugin.cpp

HEADERS += \
        mainthreadwatchdog.h \
        watchdog_plugin.h

qtHaveModule(waylandcompositor) {
    QT += waylandcompositor
    SOURCES += xdgshellwatchdog.cpp
    HEADERS += xdgshellwatchdog.h
}

CONFIG += qmltypes install_qmltypes
load(qml_plugin)
