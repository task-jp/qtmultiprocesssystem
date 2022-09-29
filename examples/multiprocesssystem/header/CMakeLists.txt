qt_internal_add_plugin(HeaderPlugin
    OUTPUT_NAME header
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        header.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files header.qrc ../common/common.qrc)
qt_internal_extend_target(HeaderPlugin
    SOURCES
        ${plugin_resource_files}
)
