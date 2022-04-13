TARGET = remoteobjects

QT = multiprocesssystem-private remoteobjects

HEADERS = \
    remoteobjectswatchdogmanager.h
SOURCES = main.cpp \
    remoteobjectswatchdogmanager.cpp

REPC_MERGED = \
    watchdogmanager.rep

OTHER_FILES += remoteobjects.json

PLUGIN_TYPE = multiprocesssystem/watchdogmanager
PLUGIN_CLASS_NAME = QRemoteObjectsWatchDogManagerPlugin
load(qt_plugin)
