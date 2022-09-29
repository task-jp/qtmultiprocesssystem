qt_internal_add_plugin(QWaylandWindowManagerPlugin
    OUTPUT_NAME wayland
    PLUGIN_TYPE multiprocesssystem/windowmanager
    SOURCES
        main.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)

qt_add_resources(plugin_resource_files wayland.qrc)
qt_internal_extend_target(QWaylandWindowManagerPlugin
    SOURCES
        ${plugin_resource_files}
)
