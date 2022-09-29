qt_internal_add_plugin(System
    OUTPUT_NAME system
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        system.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files system.qrc)
qt_internal_extend_target(System
    SOURCES
        ${plugin_resource_files}
)
