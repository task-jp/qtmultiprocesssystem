TARGET = systemd

QT = multiprocesssystem dbus

HEADERS = \
    systemdapplicationmanager.h
SOURCES = \
    main.cpp \
    systemdapplicationmanager.cpp

OTHER_FILES += \
    systemd.json

PLUGIN_TYPE = multiprocesssystem/applicationmanager
PLUGIN_CLASS_NAME = SystemdApplicationManagerManagerPlugin
load(qt_plugin)
