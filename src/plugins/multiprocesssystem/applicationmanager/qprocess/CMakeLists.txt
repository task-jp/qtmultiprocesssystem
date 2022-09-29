qt_internal_add_plugin(QProcessApplicationManagerPlugin
    OUTPUT_NAME qprocess
    PLUGIN_TYPE multiprocesssystem/applicationmanager
    SOURCES
        main.cpp
        qprocessapplicationmanager.h qprocessapplicationmanager.cpp
    LIBRARIES
        Qt::MultiProcessSystemPrivate
)
