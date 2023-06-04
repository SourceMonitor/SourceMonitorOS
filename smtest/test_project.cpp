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

#include "test_project.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <filesystem>
#include "project.h"
#include "smstring.h"

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        void TestProject::initTestCase(void)
        {
            smos::smcore::SMString filename = smos::smcore::SMString("testfile.dat");
            std::filesystem::remove(filename);
        }
        //******************************************************************************
        void TestProject::TestProjectName(void)
        {
            // Build about string
            smos::smcore::SMString projectNameSet = smos::smcore::SMString("ProjectName");
            smos::smcore::Project objProject;
            objProject.setProjectName(projectNameSet);
            smos::smcore::SMString projectNameGet = objProject.getProjectName();
            QCOMPARE(projectNameSet, projectNameGet);
        }
        //******************************************************************************
        void TestProject::TestPersistence(void)
        {
            smos::smcore::SMString filename = smos::smcore::SMString("testfile.dat");
            smos::smcore::SMString projectNameSet = smos::smcore::SMString("ProjectName");
            smos::smcore::Project objProjectSave;
            objProjectSave.setProjectName(projectNameSet);
            QCOMPARE(false, std::filesystem::exists(filename));
            smos::smcore::Error::ErrorCode result = smos::smcore::Project::saveProject(filename, objProjectSave);
            QCOMPARE(smos::smcore::Error::ErrorCode::ERR_NONE, result);
            QCOMPARE(true, std::filesystem::exists(filename));
            smos::smcore::Project objProjectLoad;
            result = smos::smcore::Project::loadProject(filename, objProjectLoad);
            QCOMPARE(smos::smcore::Error::ErrorCode::ERR_NONE, result);
            QCOMPARE(objProjectLoad.getProjectName(), objProjectSave.getProjectName());
        }
        //******************************************************************************
        void TestProject::cleanupTestCase(void)
        {
            smos::smcore::SMString filename = smos::smcore::SMString("testfile.dat");
            std::filesystem::remove(filename);
        }
        //******************************************************************************
        void TestProject::TestIncludeSubdirectories(void)
        {
            smos::smcore::Project objProject;
            bool flag = false;
            QCOMPARE(flag, objProject.getIncludeSubdirectories());
            flag = true;
            objProject.setIncludeSubdirectories(flag);
            QCOMPARE(flag, objProject.getIncludeSubdirectories());
        }
    }
}
