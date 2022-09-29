qt_internal_add_plugin(Header
    OUTPUT_NAME header
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        header.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files header.qrc ../common/common.qrc)
qt_internal_extend_target(Header
    SOURCES
        ${plugin_resource_files}
)
