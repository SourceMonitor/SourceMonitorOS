//******************************************************************************
// Copyright (C) 1999 Jim Wanner and the SourceMonitor team.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//******************************************************************************

#pragma once

#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "classinfo.h"
#include "version.h"

namespace smos
{
    namespace smcore
    {
        class ArchiveReader
        {
        public:
            //------------------------------------------------------------------------------
            ArchiveReader(std::ifstream &p_stream) : m_stream(p_stream){};
            //------------------------------------------------------------------------------
            unsigned int ReadCount();
            //------------------------------------------------------------------------------
            template <typename T>
            T Read()
            {
                T t;
                m_stream.read(reinterpret_cast<char *>(&t), sizeof(T));
                return t;
            };
            //------------------------------------------------------------------------------
            template <>
            std::vector<std::uint32_t> Read()
            {
                unsigned int size = ReadCount();
                std::vector<std::uint32_t> vec(size, 0);
                m_stream.read(reinterpret_cast<char *>(vec.data()), size * sizeof(std::uint32_t));
                return vec;
            };
            //------------------------------------------------------------------------------
            template <>
            std::time_t Read()
            {
                // first we read only 32 bits time value
                __time32_t time_32;
                m_stream.read(reinterpret_cast<char *>(&time_32), sizeof(__time32_t));
                const std::int32_t cTime64Mark = INT_MIN + 10; // this constant determines whether the value is 64 bits
                // check if stored time is 64 bit value
                if (static_cast<std::int32_t>(time_32) == cTime64Mark)
                {
                    // if this is 64 bit, then we must read this value again - prevoiuse value is only a flag
                    __time64_t time_64;
                    m_stream.read(reinterpret_cast<char *>(&time_64), sizeof(__time64_t));
                    return std::time_t(time_64);
                }
                else
                {
                    // this is 32 bits value
                    return std::time_t(time_32);
                }
            };
            //------------------------------------------------------------------------------
            template <>
            Version Read()
            {
                std::int16_t major = Read<std::int16_t>();
                short minor = Read<short>();
                std::time_t time = Read<std::time_t>();
                // revision number is set to zero because the original implementation did not have a revision number
                Version version = {major, minor, 0, time};
                return version;
            };
            //------------------------------------------------------------------------------
            template <>
            std::string Read()
            {
                unsigned int length = ReadStringLength();
                std::string t(length, '\0');
                m_stream.read(t.data(), length);
                return t;
            };
            //------------------------------------------------------------------------------
            template <>
            std::vector<std::string> Read()
            {
                unsigned int size = ReadCount();
                std::vector<std::string> vecValues;
                for (unsigned int i = 0; i < size; ++i)
                {
                    std::string sValue = Read<std::string>();
                    vecValues.push_back(sValue);
                }
                return vecValues;
            }
            //------------------------------------------------------------------------------
            template <>
            std::map<std::string, std::string> Read()
            {
                unsigned int size = ReadCount();
                std::map<std::string, std::string> mapValues;
                // while (size--)
                for (unsigned int i = 0; i < size; ++i)
                {
                    std::string sKey = Read<std::string>();
                    std::string sValue = Read<std::string>();
                    mapValues.insert(std::make_pair(sKey, sValue));
                }
                return mapValues;
            }
            //------------------------------------------------------------------------------
            template <>
            ClassInfo Read()
            {
                // the logic of this function is copied from the CArchive class
                std::uint16_t wTag = Read<std::uint16_t>();
                const std::uint16_t wNewClassTag = (std::uint16_t)UINT16_MAX;
                if (wTag == wNewClassTag)
                {
                    std::uint16_t wTemp = Read<std::uint16_t>();
                    (void)wTemp;

                    std::uint16_t nLen = Read<std::uint16_t>();
                    (void)nLen;

                    std::string name(nLen, '\0');
                    m_stream.read(name.data(), nLen);

                    m_classes[m_classesIndex] = name;
                    m_classesIndex++;
                    ClassInfo classInfo = {name};
                    return classInfo;
                }
                else
                {
                    const std::uint16_t wClassTag = (std::uint16_t)0x8000;
                    std::uint32_t obTag = ((wTag & wClassTag) << 16) | (wTag & ~wClassTag);
                    const std::uint32_t dwBigClassTag = (std::uint32_t)0x80000000;
                    std::uint32_t nClassIndex = (obTag & ~dwBigClassTag);
                    ClassInfo classInfo = {m_classes[nClassIndex]};
                    return classInfo;
                }
            }
            //------------------------------------------------------------------------------

        private:
            std::unordered_map<unsigned int, std::string> m_classes;
            unsigned int m_classesIndex = 1;
            std::ifstream &m_stream;

            unsigned int ReadStringLength();
        };
    }
}
