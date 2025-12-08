# Copyright (C) 2024 Signal Slot Inc.
# SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.16)
project(footer LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick MultiProcessSystem)

qt_add_plugin(FooterPlugin
    OUTPUT_NAME footer
    PLUGIN_TYPE multiprocesssystem/application
)

target_sources(FooterPlugin PRIVATE
    footer.cpp
)

qt_add_resources(FooterPlugin "footer"
    PREFIX "/multiprocesssystem/footer"
    FILES
        footer.qml
)

qt_add_resources(FooterPlugin "common"
    PREFIX "/multiprocesssystem/common"
    BASE "../common"
    FILES
        ../common/AbstractMain.qml
        ../common/Button.qml
)

target_link_libraries(FooterPlugin PRIVATE
    Qt::Core
    Qt::Quick
    Qt::MultiProcessSystem
)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multiprocesssystem/application")

install(TARGETS FooterPlugin
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
