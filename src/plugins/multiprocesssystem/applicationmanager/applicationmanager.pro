TEMPLATE = subdirs
SUBDIRS = inprocess qprocess
qtHaveModule(dbus): SUBDIRS += systemd
