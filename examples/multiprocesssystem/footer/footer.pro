QT = multiprocesssystem
SOURCES = footer.cpp
RESOURCES = footer.qrc
OTHER_FILES += footer.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = Footer
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
