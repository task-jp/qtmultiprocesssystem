QT = multiprocesssystem
SOURCES = system.cpp
RESOURCES = system.qrc
OTHER_FILES += settings.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = System
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
