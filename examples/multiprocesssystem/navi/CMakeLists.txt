qt_internal_add_plugin(NaviPlugin
    OUTPUT_NAME navi
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        navi.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files navi.qrc ../common/common.qrc)
qt_internal_extend_target(NaviPlugin
    SOURCES
        ${plugin_resource_files}
)
