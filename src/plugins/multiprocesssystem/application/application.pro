TEMPLATE = subdirs
SUBDIRS = header footer menu settings weather
qtHaveModule(location): SUBDIRS += navi
qtHaveModule(multimedia): SUBDIRS += music radio
