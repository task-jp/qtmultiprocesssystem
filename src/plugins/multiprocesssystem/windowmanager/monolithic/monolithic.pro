TARGET = monolithic

QT = multiprocesssystem

SOURCES = main.cpp
RESOURCES = monolithic.qrc

OTHER_FILES += monolithic.json

PLUGIN_TYPE = multiprocesssystem/windowmanager
PLUGIN_CLASS_NAME = QMonolithicWindowManagerPlugin
load(qt_plugin)
