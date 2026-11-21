qt_internal_add_plugin(QWaylandWindowManagerPlugin
    OUTPUT_NAME wayland
    PLUGIN_TYPE multiprocesssystem/windowmanager
    SOURCES
        main.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)

# Qt 6 keeps XdgShell and WlShell in QML modules of their own; in Qt 5 they
# come with QtWayland.Compositor.  server.qml stays as Qt 5 (qmake) builds it,
# and the copy that goes into this plugin gets the two imports.
set(qml_dir "${CMAKE_CURRENT_BINARY_DIR}/qml")
file(READ server.qml server_qml)
string(REPLACE "import QtWayland.Compositor 1.15\n"
    "import QtWayland.Compositor 1.15\nimport QtWayland.Compositor.XdgShell\nimport QtWayland.Compositor.WlShell\n"
    server_qml "${server_qml}")
file(CONFIGURE OUTPUT "${qml_dir}/server.qml" CONTENT "${server_qml}" @ONLY)
configure_file(client.qml "${qml_dir}/client.qml" COPYONLY)
configure_file(wayland.qrc "${qml_dir}/wayland.qrc" COPYONLY)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS server.qml)

qt_add_resources(plugin_resource_files "${qml_dir}/wayland.qrc")
qt_internal_extend_target(QWaylandWindowManagerPlugin
    SOURCES
        ${plugin_resource_files}
)
