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

project(smcore LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "SourceMonitor Core Functionality")

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(Qt6Core_DIR "C:/Qt/6.4.0/msvc2013_64/lib/cmake/Qt5Core")
#set(Qt5_DIR "C:/Qt/5.6/msvc2013_64/lib/cmake/Qt5")
#set(QT_QMAKE_EXECUTABLE "C:/Qt/5.6/msvc2013_64/bin/qmake.exe")

set(CMAKE_PREFIX)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt6Widgets)

set(SMCORE_TS_FILES
    smcore_en_150.ts
)

set(SMCORE_INCLUDE
    license.h
    smcore_global.h
    settings.h
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${SMCORE_TS_FILES})

add_library(smcore SHARED
    license.cpp
    settings.cpp
    ${SMCORE_TS_FILES}
    ${SMCORE_INCLUDE}
)

target_compile_options(smcore PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(smcore PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(smcore PRIVATE SMCORE_LIBRARY)
