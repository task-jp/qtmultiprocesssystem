qt_get_tool_target_name(target_name qmpslauncher)
qt_internal_add_tool(${target_name}
    SOURCES
        launcher.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)
qt_internal_return_unless_building_tools()
