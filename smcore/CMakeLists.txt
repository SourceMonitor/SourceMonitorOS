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

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SMCORE_INCLUDE
    about.h
    archivereader.h
    checkpoint.h
    classinfo.h
    error.h
    factory.h
    language.h
    languages.h
    languagebase.h
    license.h
    optionflags.h
    options.h
    printvector.h
    project.h
    smcheckpointsreader.h
    smlanguagereader.h
    smpreader.h
    smstring.h
    subdirectorymode.h
    version.h
)

set(SMCORE_BODY
    about.cpp
    archivereader.cpp
    checkpoint.cpp
    error.cpp
    factory.cpp
    language.cpp
    languages.cpp
    languagebase.cpp
    license.cpp
    options.cpp
    project.cpp
    smcheckpointsreader.cpp
    smlanguagereader.cpp
    smpreader.cpp
    smstring.cpp
    version.cpp
)

add_library(smcore STATIC
    ${SMCORE_INCLUDE}
    ${SMCORE_BODY}
)

target_compile_options(smcore PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(smcore)

target_compile_definitions(smcore PRIVATE SMCORE_LIBRARY)

if(MSVC OR MINGW)
    target_compile_definitions(smcore PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
