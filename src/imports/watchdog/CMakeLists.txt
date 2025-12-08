qt_internal_add_qml_module(qtmultiprocesssystem_watchdog
    URI "QtMultiProcessSystem.WatchDog"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 1
    CLASS_NAME WatchDogPlugin
    PLUGIN_TARGET qtmultiprocesssystem_watchdog
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    SOURCES
        mainthreadwatchdog.h mainthreadwatchdog.cpp
        renderthreadwatchdog.h renderthreadwatchdog.cpp
        systemdwatchdog.h systemdwatchdog.cpp
        watchdog_plugin.cpp
    DEFINES
        QT_FEATURE_systemd_watchdog=-1
    LIBRARIES
        Qt::Qml
        Qt::MultiProcessSystem
)

qt_internal_extend_target(qtmultiprocesssystem_watchdog CONDITION TARGET Qt::WaylandCompositor
    SOURCES
        xdgshellwatchdog.h xdgshellwatchdog.cpp
    PUBLIC_LIBRARIES
        Qt::WaylandCompositor
)

#config_systemd_watchdog {
#    CONFIG += link_pkgconfig
#    PKGCONFIG += libsystemd
#    DEFINES += QT_FEATURE_systemd_watchdog=1
#} else {
#    DEFINES += QT_FEATURE_systemd_watchdog=-1
#}
