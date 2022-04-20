QT = multiprocesssystem
SOURCES = music.cpp
RESOURCES = music.qrc ../common/common.qrc
OTHER_FILES += music.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Music
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
