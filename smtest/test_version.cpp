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

#include "test_version.h"

#include <QDebug>
#include "version.h"
#include <chrono>
#include <thread>

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        void TestVersion::initTestCase(void)
        {
        }
        //******************************************************************************
        void TestVersion::TestVersionCopyConstructor(void)
        {
            smos::smcore::Version verObjectSrc;
            smos::smcore::Version verObjectDst(verObjectSrc);
            QCOMPARE(verObjectSrc, verObjectDst);
        }
        //******************************************************************************
        void TestVersion::TestVersionAssignmentOperator(void)
        {
            smos::smcore::Version verObjectSrc;
            smos::smcore::Version verObjectDst(verObjectSrc);
            QCOMPARE(true, (verObjectSrc == verObjectDst));

            verObjectSrc.SetVersion(1, 2, 3);
            QCOMPARE(false, (verObjectSrc == verObjectDst));

            verObjectDst = verObjectSrc;
            QCOMPARE(true, (verObjectSrc == verObjectDst));
        }
        //******************************************************************************
        void TestVersion::TestVersionEqualOperator(void)
        {
            smos::smcore::Version verObjectSrc;
            smos::smcore::Version verObjectDst(verObjectSrc);
            QCOMPARE(true, (verObjectSrc == verObjectDst));

            verObjectSrc.SetVersion(1, 2, 3);
            QCOMPARE(false, (verObjectSrc == verObjectDst));

            verObjectDst.SetVersion(1, 2, 3);
            QCOMPARE(true, (verObjectSrc == verObjectDst));
        }
        //******************************************************************************
        void TestVersion::TestVersionNonEqualOperator(void)
        {
            smos::smcore::Version verObjectSrc;
            smos::smcore::Version verObjectDst(verObjectSrc);
            QCOMPARE(false, (verObjectSrc != verObjectDst));

            verObjectSrc.SetVersion(1, 2, 3);
            QCOMPARE(true, (verObjectSrc != verObjectDst));

            verObjectDst.SetVersion(1, 2, 3);
            QCOMPARE(false, (verObjectSrc != verObjectDst));
        }
        //******************************************************************************
        void TestVersion::TestVersionString(void)
        {
            smos::smcore::Version verObjectSrc;
            smos::smcore::Version verObjectDst(verObjectSrc);
            smos::smcore::SMString versionSrc = verObjectSrc.AsString();
            smos::smcore::SMString versionDst = verObjectDst.AsString();
            QCOMPARE(true, (verObjectSrc == verObjectDst));

            verObjectSrc.SetVersion(1, 2, 3);
            versionSrc = verObjectSrc.AsString();
            QCOMPARE(false, (verObjectSrc == verObjectDst));

            verObjectDst.SetVersion(1, 2, 3);
            versionDst = verObjectDst.AsString();
            QCOMPARE(true, (verObjectSrc == verObjectDst));
        }
        //******************************************************************************
        void TestVersion::cleanupTestCase(void)
        {
        }
    }
}
