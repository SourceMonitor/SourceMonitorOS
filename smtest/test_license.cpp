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

#include "test_license.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "license.h"

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        QString TestLicense::readLicenseFromFile(void)
        {
            QString licenseText = "";
            QString filename = "LICENSE";
            QFile licenseFile(filename);
            if (!licenseFile.open(QFile::ReadOnly | QFile::Text))
            {
                // Cannot open or read file containing license text, abort
                return licenseText;
            }
            // Read license from file
            QTextStream licenseFileStream(&licenseFile);
            licenseText = licenseFileStream.readAll();
            licenseFile.close();
            return licenseText;
        }
        //******************************************************************************
        void TestLicense::initTestCase(void)
        {
        }
        //******************************************************************************
        void TestLicense::TestGetLicense(void)
        {
            // Read license from given license file (part of project)
            QString licenseFile = this->readLicenseFromFile();
            // Get license text from application
            QString licenseApplication = smos::smcore::License::getLicense();
            // They must be equal
            QCOMPARE(licenseFile, licenseApplication);
        }
        //******************************************************************************
        void TestLicense::cleanupTestCase(void)
        {
        }
    }
}
