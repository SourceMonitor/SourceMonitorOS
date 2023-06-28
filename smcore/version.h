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

#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>

#include "smstring.h"

namespace smos
{
    namespace smcore
    {
        class Version
        {
        public:
            /**
             * @brief Default constructor
             */
            Version(void);

            /**
             * @brief Default destructor
             */
            ~Version(void);

            /**
             * @brief Constructor
             */
            Version(short major, short minor, short revision = 0, std::time_t time = 0);

            /**
             * @brief Copy constructor
             *
             * @param versionObject Version to copy data from
             */
            Version(const Version &versionObject);

            /**
             * @brief Get version information as string
             *
             * @return smos::smcore::SMString
             */
            smos::smcore::SMString AsString(void) const;

            /**
             * @brief Non equal operator
             *
             * @param versionObject Version to compare with
             * @return bool True on non equal, otherwise false
             */
            bool operator!=(const Version &versionObject) const;

            /**
             * @brief Assignment operator
             *
             * @param versionObject
             * @return Version& reference to current object
             */
            Version &operator=(const Version &versionObject);

            /**
             * @brief Equal operator
             *
             * @param versionObject Version to compare with
             * @return bool True on equal, otherwise false
             */
            bool operator==(const Version &versionObject) const;

            /**
             * @brief Object comparison greater than
             *
             * @param otherVersion Version to compare with
             * @return bool True on equal, otherwise false
             */
            bool operator>=(const Version &otherVersion) const;

            /**
             * @brief Set the Version object
             *
             * @param major Major version information
             * @param minor Minor version information
             * @param revision Revision version informationi
             */
            void SetVersion(const uint16_t major, const uint16_t minor, const uint16_t revision);

            /**
             * @brief Enable writing to stream
             *
             * @param os Outputstream to write to
             * @param obj Version object to write to stream
             *
             * @return std::ostream&
             */
            friend std::ostream &operator<<(std::ostream &os, const Version &obj);

            /**
             * @brief Enable reading from stream
             *
             * @param is Inputstream to read from
             * @param obj Version object to read from stream
             *
             * @return std::istream&
             */
            friend std::istream &operator>>(std::istream &is, Version &obj);

        private:
            /**
             * @brief Major version number
             */
            uint16_t m_major;
            /**
             * @brief Minor version number
             */
            uint16_t m_minor;
            /**
             * @brief Revision version number
             */
            uint16_t m_revision;
            /**
             * @brief Timestamp
             */
            std::time_t m_time;
        };
    }
}
