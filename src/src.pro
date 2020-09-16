TEMPLATE = subdirs

SUBDIRS += multiprocesssystem

SUBDIRS += plugins
plugins.depends += multiprocesssystem
