qt_internal_add_plugin(WeatherPlugin
    OUTPUT_NAME weather
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        weather.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files weather.qrc ../common/common.qrc)
qt_internal_extend_target(WeatherPlugin
    SOURCES
        ${plugin_resource_files}
)
