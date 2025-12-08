# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(taskmanager LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem)

qt_add_plugin(TaskmanagerPlugin
    OUTPUT_NAME taskmanager
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(TaskmanagerPlugin PRIVATE
    taskmanager.cpp
)

qt_add_resources(TaskmanagerPlugin "taskmanager"
    PREFIX "/multiprocesssystem/taskmanager"
    FILES
        taskmanager.qml
)

qt_add_resources(TaskmanagerPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(TaskmanagerPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS TaskmanagerPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
