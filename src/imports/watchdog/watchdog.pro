TARGET = qtmultiprocesssystem_watchdog
TARGETPATH = QtMultiProcessSystem/WatchDog
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = quick multiprocesssystem

SOURCES += \
        mainthreadwatchdog.cpp \
        renderthreadwatchdog.cpp \
        systemdwatchdog.cpp \
        watchdog_plugin.cpp

HEADERS += \
        mainthreadwatchdog.h \
        renderthreadwatchdog.h \
        systemdwatchdog.h \
        watchdog_plugin.h

qtHaveModule(waylandcompositor) {
    QT += waylandcompositor
    SOURCES += xdgshellwatchdog.cpp
    HEADERS += xdgshellwatchdog.h
}

config_systemd_watchdog {
    CONFIG += link_pkgconfig
    PKGCONFIG += libsystemd
    DEFINES += QT_FEATURE_systemd_watchdog=1
} else {
    DEFINES += QT_FEATURE_systemd_watchdog=-1
}


CONFIG += qmltypes install_qmltypes
load(qml_plugin)
