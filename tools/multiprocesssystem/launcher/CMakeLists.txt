qt_internal_add_app(qmpslauncher
    SOURCES
        launcher.cpp
    LIBRARIES
        Qt::MultiProcessSystem
)

set_target_properties(qmpslauncher PROPERTIES
    WIN32_EXECUTABLE TRUE
)
