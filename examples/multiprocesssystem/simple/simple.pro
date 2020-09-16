TEMPLATE = app
QT = multiprocesssystem

SOURCES = main.cpp

RESOURCES += \
    simple.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multiprocesssystem/simple
INSTALLS += target
