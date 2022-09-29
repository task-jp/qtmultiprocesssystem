qt_internal_add_plugin(FooterPlugin
    OUTPUT_NAME footer
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        footer.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files footer.qrc ../common/common.qrc)
qt_internal_extend_target(FooterPlugin
    SOURCES
        ${plugin_resource_files}
)
