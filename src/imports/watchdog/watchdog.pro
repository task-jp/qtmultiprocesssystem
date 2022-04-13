TARGET = qtmultiprocesssystem_watchdog
TARGETPATH = QtMultiProcessSystem/WatchDog
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = quick multiprocesssystem

SOURCES += \
        mainthreadwatchdog.cpp \
        renderthreadwatchdog.cpp \
        watchdog_plugin.cpp

HEADERS += \
        mainthreadwatchdog.h \
        renderthreadwatchdog.h \
        watchdog_plugin.h

qtHaveModule(waylandcompositor) {
    QT += waylandcompositor
    SOURCES += xdgshellwatchdog.cpp
    HEADERS += xdgshellwatchdog.h
}

CONFIG += qmltypes install_qmltypes
load(qml_plugin)
