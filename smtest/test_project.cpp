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
#include "optionflags.h"
#include "smstring.h"

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        void TestProject::cleanupTestCase(void)
        {
            smos::smcore::SMString filename = smos::smcore::SMString("testfile.dat");
            std::filesystem::remove(filename);
        }
        //******************************************************************************
        void TestProject::initTestCase(void)
        {
            smos::smcore::SMString filename = smos::smcore::SMString("testfile.dat");
            std::filesystem::remove(filename);
        }
        //******************************************************************************
        void TestProject::TestIncludeSubdirectories(void)
        {
            smos::smcore::Project objProject;
            smos::smcore::SubdirectoryMode flag = smos::smcore::SubdirectoryMode::NoSubs;
            QCOMPARE(flag, objProject.getIncludeSubdirectories());
            flag = smos::smcore::SubdirectoryMode::SelectedSubs;
            objProject.setIncludeSubdirectories(flag);
            QCOMPARE(flag, objProject.getIncludeSubdirectories());
            flag = smos::smcore::SubdirectoryMode::AllSubs;
            objProject.setIncludeSubdirectories(flag);
            QCOMPARE(flag, objProject.getIncludeSubdirectories());
        }
        //******************************************************************************
        void TestProject::TestOptions(void)
        {
            bool flag;
            smos::smcore::Project objProject;

            int optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::None, optionCurrent);

            flag = true;
            objProject.UseModifiedComplexity(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::ModifiedComplexity, optionCurrent);
            QCOMPARE(flag, objProject.UseModifiedComplexity());
            flag = false;
            objProject.UseModifiedComplexity(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::None, optionCurrent);
            QCOMPARE(flag, objProject.UseModifiedComplexity());

            flag = true;
            objProject.UseIgnoreBlankLines(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::IgnoreBlankLines, optionCurrent);
            QCOMPARE(flag, objProject.UseIgnoreBlankLines());
            flag = false;
            objProject.UseIgnoreBlankLines(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::None, optionCurrent);
            QCOMPARE(flag, objProject.UseIgnoreBlankLines());

            flag = true;
            objProject.SetFileListFromXmlFile(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::FilesFromXmlFile, optionCurrent);
            QCOMPARE(flag, objProject.IsFileListFromXmlFile());
            flag = false;
            objProject.SetFileListFromXmlFile(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::None, optionCurrent);
            QCOMPARE(flag, objProject.IsFileListFromXmlFile());

            flag = true;
            objProject.IgnoreHeaderFooter(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::IgnoreCommentsOnly, optionCurrent);
            QCOMPARE(flag, objProject.IgnoreHeaderFooter());
            flag = false;
            objProject.IgnoreHeaderFooter(flag);
            optionCurrent = objProject.GetOptionFlags();
            QCOMPARE((int)smos::smcore::OptionFlags::None, optionCurrent);
            QCOMPARE(flag, objProject.IgnoreHeaderFooter());
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
        void TestProject::TestProjectName(void)
        {
            smos::smcore::SMString projectNameSet = smos::smcore::SMString("ProjectName");
            smos::smcore::Project objProject;
            objProject.setProjectName(projectNameSet);
            smos::smcore::SMString projectNameGet = objProject.getProjectName();
            QCOMPARE(projectNameSet, projectNameGet);
        }
        //******************************************************************************
        void TestProject::TestSourcePath(void)
        {
            smos::smcore::SMString sourcePathSet = smos::smcore::SMString("C:\\develop\\source");
            smos::smcore::Project objProject;
            objProject.setSourcePath(sourcePathSet);
            smos::smcore::SMString sourcePathGet = objProject.getSourcePath();
            QCOMPARE(sourcePathSet, sourcePathGet);
        }
        //******************************************************************************
    }
}
