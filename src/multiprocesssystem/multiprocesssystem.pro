TARGET = QtMultiProcessSystem

HEADERS += \
    multiprocesssystem_global.h \
    qmpsabstractipcinterface.h \
    qmpsabstractmanagerfactory.h \
    qmpsapplication.h \
    qmpsapplicationfactory.h \
    qmpsapplicationmanager.h \
    qmpsapplicationmanagerfactory.h \
    qmpsapplicationmanagerplugin.h \
    qmpsapplicationplugin.h \
    qmpsipcinterface.h \
    qmpsurihandler.h \
    qmpswatchdog.h \
    qmpswatchdogmanager.h \
    qmpswatchdogmanagerfactory.h \
    qmpswatchdogmanagerplugin.h \
    qmpswindowmanager.h \
    qmpswindowmanagerfactory.h \
    qmpswindowmanagerplugin.h

SOURCES += \
    qmpsabstractipcinterface.cpp \
    qmpsapplication.cpp \
    qmpsapplicationfactory.cpp \
    qmpsapplicationmanager.cpp \
    qmpsapplicationmanagerfactory.cpp \
    qmpsapplicationmanagerplugin.cpp \
    qmpsapplicationplugin.cpp \
    qmpsurihandler.cpp \
    qmpswatchdog.cpp \
    qmpswatchdogmanager.cpp \
    qmpswatchdogmanagerfactory.cpp \
    qmpswatchdogmanagerplugin.cpp \
    qmpswindowmanager.cpp \
    qmpswindowmanagerfactory.cpp \
    qmpswindowmanagerplugin.cpp

QT = core-private quick

qtHaveModule(dbus) {
    QT += dbus
    HEADERS += qmpsabstractdbusinterface.h
    SOURCES += qmpsabstractdbusinterface.cpp
}

CONFIG += qmltypes
QML_IMPORT_NAME = QtMultiProcessSystem
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

CONFIG += git_build
MODULE_PLUGIN_TYPES = \
    multiprocesssystem/applicationmanager \
    multiprocesssystem/windowmanager \
    multiprocesssystem/watchdogmanager \
    multiprocesssystem/application
load(qt_module)
