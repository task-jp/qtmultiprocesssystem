# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(header LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem)

qt_add_plugin(HeaderPlugin
    OUTPUT_NAME header
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(HeaderPlugin PRIVATE
    header.cpp
)

qt_add_resources(HeaderPlugin "header"
    PREFIX "/multiprocesssystem/header"
    FILES
        header.qml
)

qt_add_resources(HeaderPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(HeaderPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS HeaderPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
