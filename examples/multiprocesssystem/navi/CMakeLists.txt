# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(navi LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem Location)

qt_add_plugin(NaviPlugin
    OUTPUT_NAME navi
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(NaviPlugin PRIVATE
    navi.cpp
)

qt_add_resources(NaviPlugin "navi"
    PREFIX "/multiprocesssystem/navi"
    FILES
        navi.qml
)

qt_add_resources(NaviPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(NaviPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
    Qt::Location
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS NaviPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
