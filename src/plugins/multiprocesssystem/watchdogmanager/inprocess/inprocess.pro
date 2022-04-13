TARGET = inprocess

QT = multiprocesssystem-private

HEADERS = \
    inprocesswatchdogmanager.h

SOURCES = main.cpp \
    inprocesswatchdogmanager.cpp

OTHER_FILES += inprocess.json

PLUGIN_TYPE = multiprocesssystem/watchdogmanager
PLUGIN_CLASS_NAME = QInProcessWatchDogManagerPlugin
load(qt_plugin)
