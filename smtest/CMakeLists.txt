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

project(smtest LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "SourceMonitor tests")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# *******************************************************************************
enable_testing(true)

set(SMTEST_INCLUDE
    test_about.h
    test_license.h
    test_options.h
    test_project.h
    test_version.h
)

set(PROJECT_SOURCES
    main.cpp
    test_about.cpp
    test_license.cpp
    test_options.cpp
    test_project.cpp
    test_version.cpp
    ${SMTEST_INCLUDE}
    ${SMCORE_INCLUDE}
)

add_executable(
    smtest
    ${PROJECT_SOURCES}
)

# Copy license file required in test_license
configure_file(./../LICENSE LICENSE COPYONLY)

target_compile_options(smtest PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(
    NAME smtest
    COMMAND
    TestLicense
)

target_link_libraries(smtest PRIVATE Qt::Test smcore)
