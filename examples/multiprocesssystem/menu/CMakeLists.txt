qt_internal_add_plugin(MenuPlugin
    OUTPUT_NAME menu
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        menu.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files menu.qrc ../common/common.qrc)
qt_internal_extend_target(MenuPlugin
    SOURCES
        ${plugin_resource_files}
)
