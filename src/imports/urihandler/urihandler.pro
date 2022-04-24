TARGET = qtmultiprocesssystem_urihandler
TARGETPATH = QtMultiProcessSystem/UriHandler
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT = quick multiprocesssystem

SOURCES = urihandler_plugin.cpp

CONFIG += qmltypes install_qmltypes
load(qml_plugin)
