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

#pragma once

#include "checkpoint.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        Checkpoint::Checkpoint(void) : m_version(), m_name("")
        {
        }
        //******************************************************************************
        Checkpoint::~Checkpoint(void)
        {
        }
        //******************************************************************************
        smos::smcore::Version Checkpoint::versionGet(void)
        {
            return this->m_version;
        }
        //******************************************************************************
        void Checkpoint::versionSet(const smos::smcore::Version &version)
        {
            this->m_version = version;
        }
        //******************************************************************************
        smos::smcore::SMString Checkpoint::checkpointNameGet(void)
        {
            return this->m_name;
        }
        //******************************************************************************
        void Checkpoint::checkpointNameSet(const smos::smcore::SMString &checkpointName)
        {
            this->m_name = checkpointName;
        }
        //******************************************************************************
    }
}
