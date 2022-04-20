QT = multiprocesssystem
SOURCES = weather.cpp
RESOURCES = weather.qrc ../common/common.qrc
OTHER_FILES += weather.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Weather
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
