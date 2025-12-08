# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(music LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem Multimedia)

qt_add_plugin(MusicPlugin
    OUTPUT_NAME music
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(MusicPlugin PRIVATE
    music.cpp
)

qt_add_resources(MusicPlugin "music"
    PREFIX "/multiprocesssystem/music"
    FILES
        music.qml
)

qt_add_resources(MusicPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(MusicPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
    Qt::Multimedia
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS MusicPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
