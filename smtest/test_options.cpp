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

#include "test_options.h"
#include "options.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        void TestOptions::initTestCase(void)
        {
            QString optionsfileName = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "smos.ini");
            if (QFile::exists(optionsfileName))
            {
                QFile configfile(optionsfileName);
                configfile.remove();
            }
        }
        //******************************************************************************
        void TestOptions::TestCodeEditorGetSet(void)
        {
            QString optionsfileName = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "smos.ini");
            QString codeEditorExpected = "${filename}";

            smos::smcore::Options options(optionsfileName.toStdString());

            QString value = QString::fromUtf8(options.codeEditorGet().c_str());
            QCOMPARE(codeEditorExpected, value);

            codeEditorExpected = "something else";
            options.codeEditorSet(codeEditorExpected.toStdString());
            value = QString::fromUtf8(options.codeEditorGet().c_str());
            QCOMPARE(codeEditorExpected, value);
        }
        //******************************************************************************
        void TestOptions::TestLogfileNameGetSet(void)
        {
            QString optionsfileName = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "smos.ini");
            QString logfileNameExpected = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "smos.log");

            smos::smcore::Options options(optionsfileName.toStdString());
            options.logfileNameSet(logfileNameExpected.toStdString());

            QString logfileName = QString::fromUtf8(options.logfileNameGet().c_str());
            QCOMPARE(logfileNameExpected, logfileName);
        }
        //******************************************************************************
        void TestOptions::cleanupTestCase(void)
        {
        }
    }
}
