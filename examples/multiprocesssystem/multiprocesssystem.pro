TEMPLATE = subdirs
SUBDIRS = system footer header menu settings taskmanager weather
qtHaveModule(location): SUBDIRS += navi
qtHaveModule(multimedia): SUBDIRS += music radio
