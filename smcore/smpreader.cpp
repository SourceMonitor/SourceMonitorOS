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

#include "smpreader.h"

#include <assert.h>
#include <iostream>
#include <map>
#include <string>

#include "checkpointsreader.h"
#include "classinfo.h"
#include "languagereader.h"
#include "version.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        SMPReader::~SMPReader()
        {
            if (m_stream.is_open())
                m_stream.close();
        }
        //******************************************************************************
        bool SMPReader::Open(std::filesystem::path path)
        {
            m_stream.exceptions(std::ifstream::failbit);
            m_stream.open(path, std::ios_base::in | std::ios_base::binary);
            return m_stream.is_open();
        }
        //******************************************************************************
        template <typename T>
        T ArchiveReader::Read()
        {
            T t;
            m_stream.read(reinterpret_cast<char *>(&t), sizeof(T));
            return t;
        }
        //******************************************************************************
        template <>
        std::vector<std::uint32_t> ArchiveReader::Read()
        {
            unsigned int size = ReadCount();
            std::vector<std::uint32_t> vec(size, 0);
            m_stream.read(reinterpret_cast<char *>(vec.data()), size * sizeof(std::uint32_t));
            return vec;
        }
        //******************************************************************************
        template <>
        std::time_t ArchiveReader::Read()
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
        }
        //******************************************************************************
        template <>
        Version ArchiveReader::Read()
        {
            std::int16_t major = Read<std::int16_t>();
            short minor = Read<short>();
            std::time_t time = Read<std::time_t>();
            // revision number is set to zero because the original implementation did not have a revision number
            Version version = {major, minor, 0, time};
            return version;
        }
        //******************************************************************************
        template <>
        std::string ArchiveReader::Read()
        {
            unsigned int length = ReadStringLength();
            std::string t(length, '\0');
            m_stream.read(t.data(), length);
            return t;
        }
        //******************************************************************************
        template <>
        std::vector<std::string> ArchiveReader::Read()
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
        //******************************************************************************
        template <>
        std::map<std::string, std::string> ArchiveReader::Read()
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
        //******************************************************************************
        template <>
        ClassInfo ArchiveReader::Read()
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
        //******************************************************************************
        bool SMPReader::Read(Project &project)
        {
            try
            {
                ArchiveReader archiveReader(m_stream);

                Version versionProject = archiveReader.Read<Version>();
                std::cout << "Version: " << versionProject.AsString() << std::endl;

                std::string name = archiveReader.Read<std::string>();
                std::cout << "m_sName: " << name << std::endl;
                project.setProjectName(name);

                std::int32_t includeSubdirectories = archiveReader.Read<std::int32_t>();
                std::cout << "m_fIncludeSubdirectories: " << includeSubdirectories << std::endl;

                std::cout << "read SMLanguage" << std::endl;
                SMLanguageReader languageReader(archiveReader);
                languageReader.Read();

                if (versionProject >= Version(1, 2))
                {
                    std::string m_sDirectory = archiveReader.Read<std::string>();
                    std::cout << "m_sDirectory: " << m_sDirectory << std::endl;
                }

                if (versionProject >= Version(2, 0))
                {
                    std::int32_t m_eOptionFlags = archiveReader.Read<std::int32_t>();
                    std::cout << "m_eOptionFlags: " << m_eOptionFlags << std::endl;
                }

                if (!(versionProject >= Version(2, 0)))
                {
                    languageReader.Read();
                }

                SMCheckpointsReader checkpointsReader(archiveReader);
                checkpointsReader.Read();

                m_stream.exceptions(std::ifstream::goodbit);
                char c;
                while (m_stream.get(c)) // checking if we missed any data, only for debug
                {
                    // assert(0);
                    std::cout << c;
                }
            }
            catch (const std::ios_base::failure &fail)
            {
                std::cout << fail.what() << std::endl;
                return false;
            }
            catch (...)
            {
                return false;
            }
            return true;
        }
        //******************************************************************************
        unsigned int ArchiveReader::ReadStringLength()
        {
            // the logic of this function is copied from the CArchive class
            unsigned char byteLength = Read<unsigned char>();
            if (byteLength < 0xff)
                return byteLength;

            unsigned short shortLength = Read<unsigned short>();
            if (shortLength == 0xfffe)
            {
                // UNICODE string prefix (length will follow)
                return (unsigned int)-1;
            }
            else if (shortLength == UINT16_MAX)
            {
                // read DWORD of length
                unsigned long longLength = Read<unsigned long>();
                return (unsigned int)longLength;
            }
            else
                return shortLength;
        }
        //******************************************************************************
        unsigned int ArchiveReader::ReadCount()
        {
            // reads the size of the container stored in the file
            std::uint16_t nCount = Read<std::uint16_t>();
            if (nCount != UINT16_MAX)
                return nCount;

            // stored size is 32 bits and we need to read it again
            std::uint32_t dwCount = Read<std::uint32_t>();
            return dwCount;
        }
    }
}
