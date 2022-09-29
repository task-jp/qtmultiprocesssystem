qt_internal_add_plugin(QInProcessWatchDogManagerPlugin
    OUTPUT_NAME inprocess
    PLUGIN_TYPE multiprocesssystem/watchdogmanager
    SOURCES
        main.cpp
        inprocesswatchdogmanager.h inprocesswatchdogmanager.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)
