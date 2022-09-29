qt_internal_add_plugin(TaskManagerPlugin
    OUTPUT_NAME taskmanager
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        taskmanager.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files taskmanager.qrc ../common/common.qrc)
qt_internal_extend_target(TaskManagerPlugin
    SOURCES
        ${plugin_resource_files}
)
