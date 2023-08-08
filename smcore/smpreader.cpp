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

#include "archivereader.h"
#include "classinfo.h"
#include "smcheckpointsreader.h"
#include "smlanguagereader.h"
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
                project.setIncludeSubdirectories(static_cast<smos::smcore::SubdirectoryMode>(includeSubdirectories));

                std::cout << "read SMLanguage" << std::endl;
                SMLanguageReader languageReader(archiveReader);
                languageReader.Read();

                if (versionProject >= Version(1, 2))
                {
                    std::string m_sDirectory = archiveReader.Read<std::string>();
                    std::cout << "m_sDirectory: " << m_sDirectory << std::endl;
                    project.setSourcePath(m_sDirectory);
                }

                if (versionProject >= Version(2, 0))
                {
                    std::int32_t m_eOptionFlags = archiveReader.Read<std::int32_t>();
                    std::cout << "m_eOptionFlags: " << m_eOptionFlags << std::endl;
                    project.SetOptionFlags(m_eOptionFlags);
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
    }
}
