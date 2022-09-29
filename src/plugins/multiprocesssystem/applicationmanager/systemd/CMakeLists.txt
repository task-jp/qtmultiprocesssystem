qt_internal_add_plugin(SystemdApplicationManagerManagerPlugin
    OUTPUT_NAME systemd
    PLUGIN_TYPE multiprocesssystem/applicationmanager
    SOURCES
        main.cpp
        systemdapplicationmanager.h systemdapplicationmanager.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate Qt::DBus
)
