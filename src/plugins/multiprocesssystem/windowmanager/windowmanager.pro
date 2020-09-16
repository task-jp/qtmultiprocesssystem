TEMPLATE = subdirs
SUBDIRS = monolithic
qtHaveModule(waylandcompositor): SUBDIRS += wayland
