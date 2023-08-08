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

#include "archivereader.h"

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        unsigned int ArchiveReader::ReadCount()
        {
            // reads the size of the container stored in the file
            std::uint16_t nCount = Read<std::uint16_t>();
            if (nCount != UINT16_MAX)
                return nCount;

            // stored size is 32 bits and we need to read it again
            std::uint32_t dwCount = Read<std::uint32_t>();
            return dwCount;
        }
        //******************************************************************************
        unsigned int ArchiveReader::ReadStringLength()
        {
            // the logic of this function is copied from the CArchive class
            unsigned char byteLength = Read<unsigned char>();
            if (byteLength < 0xff)
                return byteLength;

            unsigned short shortLength = Read<unsigned short>();
            if (shortLength == 0xfffe)
            {
                // UNICODE string prefix (length will follow)
                return (unsigned int)-1;
            }
            else if (shortLength == UINT16_MAX)
            {
                // read DWORD of length
                unsigned long longLength = Read<unsigned long>();
                return (unsigned int)longLength;
            }
            else
                return shortLength;
        }
        //******************************************************************************
    }
}
