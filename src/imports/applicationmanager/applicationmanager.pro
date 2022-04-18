TARGET = qtmultiprocesssystem_applicationmanager
TARGETPATH = QtMultiProcessSystem/ApplicationManager
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = quick multiprocesssystem

HEADERS += \
    applicationmanagermodel.h

SOURCES += \
        applicationmanager_plugin.cpp \
        applicationmanagermodel.cpp

CONFIG += qmltypes install_qmltypes
load(qml_plugin)
