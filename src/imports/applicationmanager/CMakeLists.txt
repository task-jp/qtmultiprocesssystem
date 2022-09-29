qt_internal_add_qml_module(qtmultiprocesssystem_applicationmanager
    URI "QtMultiProcessSystem.ApplicationManager"
    VERSION "${PROJECT_VERSION}"
    CLASS_NAME ApplicationManagerPlugin
    PLUGIN_TARGET qtmultiprocesssystem_applicationmanager
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    SOURCES
        applicationmanagermodel.h applicationmanagermodel.cpp
        applicationmanager_plugin.cpp
    LIBRARIES
        Qt::Qml
        Qt::MultiProcessSystem
)
