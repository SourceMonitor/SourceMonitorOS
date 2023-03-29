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

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        Project::Project(void)
        {
        }
        //******************************************************************************
        Project::~Project(void)
        {
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
        smos::smcore::SMString Project::getProjectName(void) const
        {
            return m_ProjectName;
        }
        //******************************************************************************
        void Project::setProjectName(smos::smcore::SMString projectName)
        {
            m_ProjectName = projectName;
        }
        //******************************************************************************
        std::ostream &operator<<(std::ostream &os, const Project &obj)
        {
            os << obj.m_ProjectName << std::endl;
            return os;
        }
        //******************************************************************************
        std::istream &operator>>(std::istream &is, Project &obj)
        {
            is >> obj.m_ProjectName;
            return is;
        }
        //******************************************************************************
    }
}
