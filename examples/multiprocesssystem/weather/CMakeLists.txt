# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(weather LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem)

qt_add_plugin(WeatherPlugin
    OUTPUT_NAME weather
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(WeatherPlugin PRIVATE
    weather.cpp
)

qt_add_resources(WeatherPlugin "weather"
    PREFIX "/multiprocesssystem/weather"
    FILES
        weather.qml
)

qt_add_resources(WeatherPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(WeatherPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS WeatherPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
