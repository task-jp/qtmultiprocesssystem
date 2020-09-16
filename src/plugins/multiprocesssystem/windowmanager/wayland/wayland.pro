TARGET = wayland

QT = multiprocesssystem

SOURCES = main.cpp
RESOURCES = wayland.qrc

OTHER_FILES += wayland.json

PLUGIN_TYPE = multiprocesssystem/windowmanager
PLUGIN_CLASS_NAME = QWaylandWindowManagerPlugin
load(qt_plugin)
