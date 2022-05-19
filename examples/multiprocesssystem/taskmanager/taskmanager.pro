QT = multiprocesssystem
SOURCES = taskmanager.cpp
RESOURCES = taskmanager.qrc ../common/common.qrc
OTHER_FILES += taskmanager.json

PLUGIN_TYPE = multiprocesssystem/application
PLUGIN_CLASS_NAME = TaskManager
load(qt_plugin)
CONFIG += install_ok  # Do not cargo-cult this!
