QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = music.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Music
load(qt_plugin)
