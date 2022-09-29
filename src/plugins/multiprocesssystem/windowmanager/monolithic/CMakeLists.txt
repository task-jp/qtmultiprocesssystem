qt_internal_add_plugin(QMonolithicWindowManagerPlugin
    OUTPUT_NAME monolithic
    PLUGIN_TYPE multiprocesssystem/windowmanager
    SOURCES
        main.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)

qt_add_resources(plugin_resource_files monolithic.qrc)
qt_internal_extend_target(QMonolithicWindowManagerPlugin
    SOURCES
        ${plugin_resource_files}
)
