add_subdirectory(monolithic)
if(TARGET Qt::WaylandCompositor)
    add_subdirectory(wayland)
endif()
