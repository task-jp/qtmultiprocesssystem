QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = header.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Header
load(qt_plugin)
