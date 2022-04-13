TARGET = qtmultiprocesssystem_xdgshell
TARGETPATH = QtMultiProcessSystem/XdgShell
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = qml multiprocesssystem

SOURCES += \
        xdgshell_plugin.cpp \
        xdgshellwatchdog.cpp

HEADERS += \
        xdgshell_plugin.h \
        xdgshellwatchdog.h

CONFIG += qmltypes install_qmltypes
load(qml_plugin)
