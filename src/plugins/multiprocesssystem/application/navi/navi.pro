QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = navi.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Navi
load(qt_plugin)
