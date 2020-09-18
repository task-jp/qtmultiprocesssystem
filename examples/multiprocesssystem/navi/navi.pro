QT = multiprocesssystem location positioning
SOURCES = navi.cpp
RESOURCES = navi.qrc
OTHER_FILES += navi.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Navi
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
