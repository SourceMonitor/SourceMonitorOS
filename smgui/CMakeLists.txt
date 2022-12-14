# *******************************************************************************
# Copyright (C) 1999 Jim Wanner and the SourceMonitor team.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# *******************************************************************************

cmake_minimum_required(VERSION 3.5)

project(smgui LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "SourceMonitor UI")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(SMGUI_TS_FILES
    sggui_en_150.ts
)

set(SMGUI_UI_DEFINITIONS
    sggui.ui
    sgoptions.ui
)

set(SMGUI_INCLUDE
    sggui.h
    sgoptions.h
)

set(PROJECT_SOURCES
    main.cpp
    sggui.cpp
    sgoptions.cpp
    ${SMGUI_UI_DEFINITIONS}
    ${SMGUI_TS_FILES}
    ${SMGUI_INCLUDE}
    ${SMCORE_INCLUDE}
)

qt_add_executable(smgui
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_compile_options(smgui PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${SMCORE_TS_FILES})

target_link_libraries(smgui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets smcore)

set_target_properties(smgui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS smgui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(smgui)
