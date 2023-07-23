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

#include "test_checkpoint.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "checkpoint.h"

namespace smos
{
    namespace smtest
    {
        //******************************************************************************
        void TestCheckpoint::initTestCase(void)
        {
        }
        //******************************************************************************
        void TestCheckpoint::TestConstructor(void)
        {
            smos::smcore::Checkpoint checkpoint = smos::smcore::Checkpoint();
            smos::smcore::Version version = smos::smcore::Version();

            QCOMPARE(checkpoint.versionGet(), version);

            QString nameObject = QString::fromUtf8(checkpoint.checkpointNameGet().c_str());
            smos::smcore::SMString nameExpectedRaw = "";
            QString nameExpected = QString::fromUtf8(nameExpectedRaw.c_str());

            QCOMPARE(nameObject, nameExpected);
        }
        //******************************************************************************
        void TestCheckpoint::TestVersion(void)
        {
            smos::smcore::Checkpoint checkpoint = smos::smcore::Checkpoint();
            smos::smcore::Version version = smos::smcore::Version();

            QCOMPARE(checkpoint.versionGet(), version);

            smos::smcore::Version versionNew = smos::smcore::Version(2, 2, 2);
            checkpoint.versionSet(versionNew);
            QCOMPARE(checkpoint.versionGet(), versionNew);
        }
        //******************************************************************************
        void TestCheckpoint::TestName(void)
        {
            smos::smcore::Checkpoint checkpoint = smos::smcore::Checkpoint();
            QString nameObject = QString::fromUtf8(checkpoint.checkpointNameGet().c_str());
            smos::smcore::SMString nameExpectedRaw = "";
            QString nameExpected = QString::fromUtf8(nameExpectedRaw.c_str());

            nameExpectedRaw = "Hello world!";
            checkpoint.checkpointNameSet(nameExpectedRaw);
            nameObject = QString::fromUtf8(checkpoint.checkpointNameGet().c_str());
            nameExpected = QString::fromUtf8(nameExpectedRaw.c_str());
            QCOMPARE(nameObject, nameExpected);
        }
        //******************************************************************************
        void TestCheckpoint::cleanupTestCase(void)
        {
        }
    }
}
