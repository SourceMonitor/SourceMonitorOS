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

#include "project.h"

#include <filesystem>

#include "version.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        Project::Project(void) : m_ClassVersion(0), m_includeSubdirectories(SubdirectoryMode::NoSubs)
        {
        }
        //******************************************************************************
        Project::~Project(void)
        {
        }
        //******************************************************************************
        SubdirectoryMode Project::getIncludeSubdirectories(void)
        {
            return m_includeSubdirectories;
        }
        //******************************************************************************
        int Project::GetOptionFlags(void) const
        {
            return m_OptionFlags;
        }
        //******************************************************************************
        smos::smcore::SMString Project::getProjectName(void) const
        {
            return m_ProjectName;
        }
        //******************************************************************************
        smos::smcore::SMString Project::getSourcePath(void) const
        {
            return m_sDirectory;
        }
        //******************************************************************************
        void Project::IgnoreHeaderFooter(int ignore)
        {
            m_OptionFlags = (m_OptionFlags & ~(int)smos::smcore::OptionFlags::IgnoreAllComments) | ignore;
            // TODO: Enable this with language file
            // if (m_poLanguageExemplar != NULL)
            // {
            //     m_poLanguageExemplar->SetOptionFlags(m_OptionFlags);
            // }
        }
        //******************************************************************************
        int Project::IgnoreHeaderFooter(void) const
        {
            return m_OptionFlags & (int)smos::smcore::OptionFlags::IgnoreAllComments;
        }
        //******************************************************************************
        bool Project::IsFileListFromXmlFile(void) const
        {
            return ((m_OptionFlags & (int)smos::smcore::OptionFlags::FilesFromXmlFile) != 0);
        }
        //******************************************************************************
        smos::smcore::Error::ErrorCode Project::loadProject(const smos::smcore::SMString &filename, Project &project)
        {
            if (!std::filesystem::exists(filename))
            {
                return smos::smcore::Error::ERR_PROJECT_DOES_NOT_EXIST;
            }
            std::ifstream in(filename, std::ios::binary);
            in >> project;
            in.close();

            return smos::smcore::Error::ERR_NONE;
        }
        //******************************************************************************
        std::ostream &operator<<(std::ostream &os, const Project &obj)
        {
            os << obj.m_ClassVersion << obj.m_ProjectName;
            return os;
        }
        //******************************************************************************
        std::istream &operator>>(std::istream &is, Project &obj)
        {
            is >> obj.m_ClassVersion >> obj.m_ProjectName;

            return is;
        }
        //******************************************************************************
        smos::smcore::Error::ErrorCode Project::saveProject(const smos::smcore::SMString &filename, Project &project, bool force)
        {
            if (std::filesystem::exists(filename) && !force)
            {
                return smos::smcore::Error::ERR_PROJECT_ALREADY_EXIST;
            }
            std::ofstream out(filename, std::ios::binary);
            out << project;
            out.close();
            return smos::smcore::Error::ERR_NONE;
        }
        //******************************************************************************
        void Project::SetFileListFromXmlFile(bool isFileListFromXmlFile)
        {
            if (isFileListFromXmlFile)
            {
                m_OptionFlags |= (int)smos::smcore::OptionFlags::FilesFromXmlFile;
            }
            else
            {
                m_OptionFlags &= ~(int)smos::smcore::OptionFlags::FilesFromXmlFile;
            }
            // TODO: Enable this with language file
            // if (m_poLanguageExemplar != NULL)
            // {
            //     m_poLanguageExemplar->SetOptionFlags(m_OptionFlags);
            // }
        }
        //******************************************************************************
        void Project::setIncludeSubdirectories(smos::smcore::SubdirectoryMode usage)
        {
            m_includeSubdirectories = usage;
        }
        //******************************************************************************
        void Project::SetOptionFlags(int options)
        {
            m_OptionFlags = options;
        }
        //******************************************************************************
        void Project::setProjectName(smos::smcore::SMString projectName)
        {
            m_ProjectName = projectName;
        }
        //******************************************************************************
        void Project::setSourcePath(smos::smcore::SMString directory)
        {
            m_sDirectory = directory;
        }
        //******************************************************************************
        void Project::UseIgnoreBlankLines(bool ignoreBlankLines)
        {
            if (ignoreBlankLines)
            {
                m_OptionFlags |= (int)smos::smcore::OptionFlags::IgnoreBlankLines;
            }
            else
            {
                m_OptionFlags &= ~(int)smos::smcore::OptionFlags::IgnoreBlankLines;
            }
            // TODO: Enable this with language file
            // if (m_poLanguageExemplar != NULL)
            // {
            //     m_poLanguageExemplar->SetOptionFlags(m_OptionFlags);
            // }
        }
        //******************************************************************************
        bool Project::UseIgnoreBlankLines(void) const
        {
            return ((m_OptionFlags & (int)smos::smcore::OptionFlags::IgnoreBlankLines) != 0);
        }
        //******************************************************************************
        void Project::UseModifiedComplexity(bool useModifiedComplexity)
        {
            if (useModifiedComplexity)
            {
                m_OptionFlags |= (int)smos::smcore::OptionFlags::ModifiedComplexity;
            }
            else
            {
                m_OptionFlags &= ~(int)smos::smcore::OptionFlags::ModifiedComplexity;
            }
            // TODO: Enable this with language file
            // if (m_poLanguageExemplar != NULL)
            // {
            //     m_poLanguageExemplar->SetOptionFlags(m_OptionFlags);
            // }
        }
        //******************************************************************************
        bool Project::UseModifiedComplexity(void) const
        {
            return ((m_OptionFlags & (int)smos::smcore::OptionFlags::ModifiedComplexity) != 0);
        }
        //******************************************************************************
    }
}
