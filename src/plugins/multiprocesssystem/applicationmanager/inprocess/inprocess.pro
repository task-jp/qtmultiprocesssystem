TARGET = inprocess

QT = multiprocesssystem-private

HEADERS = \
    inprocessapplicationmanager.h

SOURCES = main.cpp \
    inprocessapplicationmanager.cpp

OTHER_FILES += inprocess.json

PLUGIN_TYPE = multiprocesssystem/applicationmanager
PLUGIN_CLASS_NAME = QInProcessApplicationManagerPlugin
load(qt_plugin)
