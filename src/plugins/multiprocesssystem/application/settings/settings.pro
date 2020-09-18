QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = settings.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Settings
load(qt_plugin)
