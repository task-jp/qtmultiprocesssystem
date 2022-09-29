qt_internal_add_qml_module(MultiProcessSystem
    URI "QtMultiProcessSystem"
    VERSION "${PROJECT_VERSION}"
    PLUGIN_TYPES
        multiprocesssystem/applicationmanager
        multiprocesssystem/windowmanager
        multiprocesssystem/watchdogmanager
        multiprocesssystem/application
    SOURCES
        multiprocesssystem_global.h
        qmpsabstractipcinterface.h qmpsabstractipcinterface.cpp
        qmpsabstractmanagerfactory.h
        qmpsapplication.h qmpsapplication.cpp
        qmpsapplicationfactory.h qmpsapplicationfactory.cpp
        qmpsapplicationmanager.h qmpsapplicationmanager.cpp
        qmpsapplicationmanagerfactory.h qmpsapplicationmanagerfactory.cpp
        qmpsapplicationmanagerplugin.h qmpsapplicationmanagerplugin.cpp
        qmpsapplicationplugin.h qmpsapplicationplugin.cpp
        qmpsipcinterface.h
        qmpsurihandler.h qmpsurihandler.cpp
        qmpswatchdog.h qmpswatchdog.cpp
        qmpswatchdogmanager.h qmpswatchdogmanager.cpp
        qmpswatchdogmanagerfactory.h qmpswatchdogmanagerfactory.cpp
        qmpswatchdogmanagerplugin.h qmpswatchdogmanagerplugin.cpp
        qmpswindowmanager.h qmpswindowmanager.cpp
        qmpswindowmanagerfactory.h qmpswindowmanagerfactory.cpp
        qmpswindowmanagerplugin.h qmpswindowmanagerplugin.cpp
    LIBRARIES
       Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Core Qt::Quick
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
    GENERATE_CPP_EXPORTS
)

qt_internal_extend_target(MultiProcessSystem CONDITION TARGET Qt::DBus
    SOURCES
        qmpsabstractdbusinterface.h qmpsabstractdbusinterface.cpp
    PUBLIC_LIBRARIES
        Qt::DBus
)
