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

#include "test_about.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        QString TestAbout::buildAboutString(void)
        {
            return "SourceMonitor Tracks Source Code Quality and Quantity\nVersion <InsertVersionInfoHere> [InsertBuildInformationHere]\n\nSourceMonitor Team\nhttp://www.github.com/SourceMonitor\n© SourceMonitor Team";
        }
        //******************************************************************************
        void TestAbout::initTestCase(void)
        {
        }
        //******************************************************************************
        void TestAbout::TestGetAbout(void)
        {
            // Build about string
            QString aboutData = this->buildAboutString();
            // Get about string from application
            QString aboutApplication = smos::smcore::SMAbout::getAbout();
            // They must be equal
            QCOMPARE(aboutData, aboutApplication);
        }
        //******************************************************************************
        void TestAbout::cleanupTestCase(void)
        {
        }
    }
}
