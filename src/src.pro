TEMPLATE = subdirs

SUBDIRS += multiprocesssystem

SUBDIRS += plugins
plugins.depends += multiprocesssystem

SUBDIRS += imports
imports.depends += multiprocesssystem
