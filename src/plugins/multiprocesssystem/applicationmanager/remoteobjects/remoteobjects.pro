TARGET = remoteobjects

QT = multiprocesssystem-private remoteobjects

HEADERS = \
    remoteobjectsapplicationmanager.h
SOURCES = main.cpp \
    remoteobjectsapplicationmanager.cpp

REPC_MERGED = \
    applicationmanager.rep

OTHER_FILES += remoteobjects.json

PLUGIN_TYPE = multiprocesssystem/applicationmanager
PLUGIN_CLASS_NAME = QRemoteObjectsApplicationManagerPlugin
load(qt_plugin)
