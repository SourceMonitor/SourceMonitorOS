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

#include "version.h"

#include <sstream>

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        Version::Version(void)
        {
        }
        //******************************************************************************
        Version::~Version(void)
        {
        }
        //******************************************************************************
        Version::Version(short major, short minor, short revision, std::time_t time)
            : m_major(major), m_minor(minor), m_revision(revision), m_time(time)
        {
        }
        //******************************************************************************
        Version::Version(const Version &versionObject)
        {
            this->m_major = versionObject.m_major;
            this->m_minor = versionObject.m_minor;
            this->m_revision = versionObject.m_revision;
        }
        //******************************************************************************
        Version &Version::operator=(const Version &versionObject)
        {
            if (&versionObject != this)
            {
                this->m_major = versionObject.m_major;
                this->m_minor = versionObject.m_minor;
                this->m_revision = versionObject.m_revision;
            }
            return *this;
        }
        //******************************************************************************
        bool Version::operator==(const Version &versionObject) const
        {
            if (&versionObject == this)
            {
                return true;
            }
            bool result = (this->m_major == versionObject.m_major) && (this->m_minor == versionObject.m_minor)
                && (this->m_revision == versionObject.m_revision);
            return result;
        }
        //******************************************************************************
        bool Version::operator!=(const Version &versionObject) const
        {
            bool result = !(*this == versionObject);
            return result;
        }
        //******************************************************************************
        bool Version::operator>=(const Version &otherVersion) const
        {
            return (m_major > otherVersion.m_major) || (m_major == otherVersion.m_major && m_minor > otherVersion.m_minor)
                || (m_major == otherVersion.m_major && m_minor == otherVersion.m_minor && m_revision > otherVersion.m_revision)
                || (m_major == otherVersion.m_major && m_minor == otherVersion.m_minor && m_revision == otherVersion.m_revision);
        }
        //******************************************************************************
        smos::smcore::SMString Version::AsString(void) const
        {
            std::stringstream os;
            os << this->m_major << "." << this->m_minor << "." << this->m_revision;

            smos::smcore::SMString result = os.str();
            return result;
        }
        //******************************************************************************
        void Version::SetVersion(const uint16_t major, const uint16_t minor, const uint16_t revision)
        {
            this->m_major = major;
            this->m_minor = minor;
            this->m_revision = revision;
        }
        //******************************************************************************
        std::ostream &operator<<(std::ostream &os, const Version &obj)
        {
            os << obj.m_major;
            os << obj.m_minor;
            os << obj.m_revision;
            return os;
        }
        //******************************************************************************
        std::istream &operator>>(std::istream &is, Version &obj)
        {
            is >> obj.m_major;
            is >> obj.m_minor;
            is >> obj.m_revision;
            return is;
        }
        //******************************************************************************
    }
}
