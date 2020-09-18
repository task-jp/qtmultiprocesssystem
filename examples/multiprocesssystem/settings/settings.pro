QT = multiprocesssystem
SOURCES = settings.cpp
RESOURCES = settings.qrc
OTHER_FILES += settings.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Settings
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
