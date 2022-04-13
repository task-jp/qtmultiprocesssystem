TEMPLATE = subdirs

SUBDIRS += multiprocesssystem

SUBDIRS += plugins
plugins.depends += multiprocesssystem

qtHaveModule(qml) {
    SUBDIRS += imports
    imports.depends += multiprocesssystem
}
