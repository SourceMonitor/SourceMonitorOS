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

project(smcli LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "SourceMonitor CLI")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

set(SMCLI_TS_FILES
    smcli_en_150.ts
)

add_executable(smcli
    main.cpp
    ${SMCLI_TS_FILES}
    ${SMCORE_INCLUDE}
)

# Copy required files
configure_file(./../LICENSE LICENSE COPYONLY)
configure_file(./../smtest/testfiles/osm.smp osm.smp COPYONLY)

target_compile_options(smcli PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(smcli Qt${QT_VERSION_MAJOR}::Core smcore)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${SMCLI_TS_FILES})
endif()

install(TARGETS smcli LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(smcli)
