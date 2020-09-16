TARGET = QtMultiProcessSystem

SOURCES += \
    multiprocesssystem.cpp \
    qmpsapplication.cpp \
    qmpsapplicationfactory.cpp \
    qmpsapplicationmanager.cpp \
    qmpsapplicationmanagerfactory.cpp \
    qmpsapplicationmanagerplugin.cpp \
    qmpsapplicationplugin.cpp \
    qmpswindowmanager.cpp \
    qmpswindowmanagerfactory.cpp \
    qmpswindowmanagerplugin.cpp

HEADERS += \
    multiprocesssystem_global.h \
    multiprocesssystem.h \
    qmpsabstractmanagerfactory.h \
    qmpsapplication.h \
    qmpsapplicationfactory.h \
    qmpsapplicationmanager.h \
    qmpsapplicationmanagerfactory.h \
    qmpsapplicationmanagerplugin.h \
    qmpsapplicationplugin.h \
    qmpswindowmanager.h \
    qmpswindowmanagerfactory.h \
    qmpswindowmanagerplugin.h

QT = core-private quick
CONFIG += git_build
MODULE_PLUGIN_TYPES = multiprocesssystem/applicationmanager multiprocesssystem/windowmanager multiprocesssystem/application
load(qt_module)
