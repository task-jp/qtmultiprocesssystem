qt_internal_add_plugin(QInProcessApplicationManagerPlugin
    OUTPUT_NAME inprocess
    PLUGIN_TYPE multiprocesssystem/applicationmanager
    SOURCES
        main.cpp
        inprocessapplicationmanager.h inprocessapplicationmanager.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)
