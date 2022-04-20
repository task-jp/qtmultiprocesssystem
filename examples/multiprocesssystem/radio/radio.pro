QT = multiprocesssystem
SOURCES = radio.cpp
RESOURCES = radio.qrc ../common/common.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Radio
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
