QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = main.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Settings
load(qt_plugin)
