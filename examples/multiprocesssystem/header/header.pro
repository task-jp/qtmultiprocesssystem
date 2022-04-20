QT = multiprocesssystem
SOURCES = header.cpp
RESOURCES = header.qrc ../common/common.qrc
OTHER_FILES += header.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Header
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
