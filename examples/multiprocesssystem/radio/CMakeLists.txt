# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(radio LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem Multimedia)

qt_add_plugin(RadioPlugin
    OUTPUT_NAME radio
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(RadioPlugin PRIVATE
    radio.cpp
)

qt_add_resources(RadioPlugin "radio"
    PREFIX "/multiprocesssystem/radio"
    FILES
        radio.qml
)

qt_add_resources(RadioPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(RadioPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
    Qt::Multimedia
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS RadioPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
