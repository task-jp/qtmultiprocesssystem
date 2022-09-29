qt_internal_add_plugin(Radio
    OUTPUT_NAME radio
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        radio.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files radio.qrc ../common/common.qrc)
qt_internal_extend_target(Radio
    SOURCES
        ${plugin_resource_files}
)
