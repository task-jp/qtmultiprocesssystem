qt_internal_add_plugin(Music
    OUTPUT_NAME music
    PLUGIN_TYPE multiprocesssystem/application
    SOURCES
        music.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

qt_add_resources(plugin_resource_files music.qrc ../common/common.qrc)
qt_internal_extend_target(Music
    SOURCES
        ${plugin_resource_files}
)
