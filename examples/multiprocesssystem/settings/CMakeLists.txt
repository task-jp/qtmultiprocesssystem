qt_internal_add_plugin(Settings
    OUTPUT_NAME settings
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        settings.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files settings.qrc ../common/common.qrc)
qt_internal_extend_target(Settings
    SOURCES
        ${plugin_resource_files}
)
