QT = multiprocesssystem
SOURCES = main.cpp
RESOURCES = menu.qrc
OTHER_FILES += main.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Menu
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
