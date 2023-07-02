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

#include "checkpointsreader.h"

#include <iostream>

#include "languagereader.h"
#include "version.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        void SMCheckpointsReader::Read()
        {
            unsigned int sizeCheckpoints = m_archiveReader.ReadCount();
            std::cout << "sizeCheckpoints: " << sizeCheckpoints << std::endl;
            for (unsigned int i = 0; i < sizeCheckpoints; i++)
            {
                Version versionCheckpoint = m_archiveReader.Read<Version>();
                std::cout << "Checkpoint version: " << versionCheckpoint.AsString() << std::endl;

                // ar >> m_sName >> m_oDate >> m_fUseModifiedComplexity >> m_poLanguage;
                std::string nameSMCheckpoint = m_archiveReader.Read<std::string>();
                std::cout << "nameSMCheckpoint: " << nameSMCheckpoint << std::endl;
                std::time_t t64_checkpointSMCheckpoint = m_archiveReader.Read<std::time_t>();
                std::cout << "Checkpoint time: " << t64_checkpointSMCheckpoint << std::endl;

                std::int32_t m_fUseModifiedComplexity = m_archiveReader.Read<std::int32_t>();
                std::cout << "m_fUseModifiedComplexity: " << m_fUseModifiedComplexity << std::endl;

                std::cout << "read SMLanguage" << std::endl;
                SMLanguageReader languageReader(m_archiveReader);
                languageReader.Read();

                if (versionCheckpoint >= Version(3, 1))
                {
                    std::string m_sBaseDirectory = m_archiveReader.Read<std::string>();
                    std::cout << "m_sBaseDirectory: " << m_sBaseDirectory << std::endl;
                }

                // if (!m_oVersion.IsOKVersion(2, 0))
                if (!(versionCheckpoint >= Version(2, 0)))
                {
                    // m_poLanguage->Serialize(ar); // include redundant copy for older versions only
                    languageReader.Read();
                }

                unsigned int m_iFileCount = m_archiveReader.ReadCount();
                std::cout << "m_iFileCount: " << m_iFileCount << std::endl;
                // m_oFiles.Serialize(ar);

                for (unsigned int f = 0; f < m_iFileCount; f++)
                {
                    // void SMFile::Serialize(CArchive &ar)
                    std::string m_sPathname = m_archiveReader.Read<std::string>();
                    std::cout << "m_sPathname: " << m_sPathname << std::endl;
                    std::cout << "read SMLanguage" << std::endl;
                    SMLanguageReader languageReaderFile(m_archiveReader);
                    languageReaderFile.Read();
                }
            }
        }
        //******************************************************************************
    }
}
