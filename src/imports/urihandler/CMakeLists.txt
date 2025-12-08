qt_internal_add_qml_module(qtmultiprocesssystem_urihandler
    URI "QtMultiProcessSystem.UriHandler"
    VERSION "${PROJECT_VERSION}"
    PAST_MAJOR_VERSIONS 1
    DESIGNER_SUPPORTED
    CLASS_NAME UriHandlerPlugin
    PLUGIN_TARGET qtmultiprocesssystem_urihandler
    NO_GENERATE_PLUGIN_SOURCE
    NO_PLUGIN_OPTIONAL
    SOURCES
        urihandler_plugin.cpp
    LIBRARIES
        Qt::Qml
        Qt::MultiProcessSystem
)
