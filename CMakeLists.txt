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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SourceMonitorOS LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "SourceMonitor OpenSource")

# Add Qt to path.
set(CMAKE_PREFIX_PATH "D:/dev/Qt/6.5.1/msvc2019_64")
message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")

# Look for Qt as first priority.
find_package(Qt6 REQUIRED COMPONENTS Core LinguistTools)

# *******************************************************************************
# Settings for smcore
# *******************************************************************************
add_subdirectory(smcore)

# *******************************************************************************
# Settings for smcli
# *******************************************************************************
add_subdirectory(smcli)
target_include_directories(smcli PRIVATE smcore)

# *******************************************************************************
# Settings for smgui
# *******************************************************************************
add_subdirectory(smgui)
target_include_directories(smgui PRIVATE smcore)

# *******************************************************************************
# Settings for smtest
# *******************************************************************************
add_subdirectory(smtest)
target_include_directories(smtest PRIVATE smcore)
