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

#include "languagereader.h"

#include <iostream>
#include <map>

#include "classinfo.h"
#include "printvector.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        void SMLanguageReader::Read()
        {
            ClassInfo classInfo = m_archiveReader.Read<ClassInfo>();
            std::cout << "class name: " << classInfo.m_name << std::endl;
            if (classInfo.m_name.empty())
                return;

            if (classInfo.m_name == "SMCpp" || classInfo.m_name == "SMCs" || classInfo.m_name == "SMJava" || classInfo.m_name == "SMVBNET")
            {
                std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
                std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

                std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
                std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
                printVector(m_iCounts);

                std::map<std::string, std::string> m_oClassList = m_archiveReader.Read<std::map<std::string, std::string>>();
                std::cout << "m_oClassList: size = " << m_oClassList.size() << " elements: " << std::endl;
            }
            else if (classInfo.m_name == "SMC")
            {
                std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
                std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

                std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
                std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
                printVector(m_iCounts);

                // m_oFunctionList.Serialize(ar);
                std::map<std::string, std::string> m_oFunctionList = m_archiveReader.Read<std::map<std::string, std::string>>();
                std::cout << "m_oFunctionList: size = " << m_oFunctionList.size() << " elements: " << std::endl;
            }
            else if (classInfo.m_name == "SMDelphi")
            {
                std::string m_sSubroutineName = m_archiveReader.Read<std::string>();
                std::cout << "m_sSubroutineName: " << m_sSubroutineName << std::endl;

                std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
                std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

                std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
                std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
                printVector(m_iCounts);

                std::map<std::string, std::string> m_oClassList = m_archiveReader.Read<std::map<std::string, std::string>>();
                std::cout << "m_oClassList: size = " << m_oClassList.size() << " elements: " << std::endl;
            }
            else if (classInfo.m_name == "SMHTML")
            {
                std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
                std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

                std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
                std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
                printVector(m_iCounts);
            }
            else if (classInfo.m_name == "SMVisualBasic")
            {
                std::string m_sSubroutineName = m_archiveReader.Read<std::string>();
                std::cout << "m_sSubroutineName: " << m_sSubroutineName << std::endl;

                std::int32_t m_iSubroutineStatements = m_archiveReader.Read<std::int32_t>();
                std::cout << "m_iSubroutineStatements: " << m_iSubroutineStatements << std::endl;

                std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
                std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

                std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
                std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
                printVector(m_iCounts);
            }
        }
        //******************************************************************************
    }
}
