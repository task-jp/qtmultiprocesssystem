TARGET = qprocess

QT = multiprocesssystem

HEADERS = \
    qprocessapplicationmanager.h
SOURCES = main.cpp \
    qprocessapplicationmanager.cpp

OTHER_FILES += qprocess.json

PLUGIN_TYPE = multiprocesssystem/applicationmanager
PLUGIN_CLASS_NAME = QProcessApplicationManagerPlugin
load(qt_plugin)
