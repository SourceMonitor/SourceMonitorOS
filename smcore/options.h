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

// Think about this:
// http://katecpp.github.io/qsettings/

#pragma once

#include "smstring.h"
#include <memory>

namespace smos
{
    namespace smcore
    {
        class Options
        {
        public:
            /**
             * @brief Default constructor
             *
             * @param optionsfile Name of options file
             */
            Options(smos::smcore::SMSring optionsfile);

            /**
             * @brief Default destructor
             *
             */
            ~Options(void);

            /**
             * @brief Get the editor call with filename templated
             *
             * @return smos::smcore::SMSring
             */
            smos::smcore::SMSring codeEditorGet(void);

            /**
             * @brief Get the editor call with filename templated
             *
             * @param codeeditor smos::smcore::SMSring
             */
            void codeEditorSet(smos::smcore::SMSring codeeditor);

            /**
             * @brief Get the absolute path to the logfile
             *
             * @return smos::smcore::SMSring The absolute path to the logfile
             */
            smos::smcore::SMSring logfileNameGet(void);

            /**
             * @brief Set the name (and path) of the logfile
             *
             * @param logfileName Name (and path) of the logfile to use
             */
            void logfileNameSet(smos::smcore::SMSring logfileName);

        protected:
            /**
             * @brief Absolute path to editor for code files
             */
            smos::smcore::SMSring m_general_CodeEditor = "${filename}";

            /**
             * @brief Name of used ini file
             */
            smos::smcore::SMSring m_logfileName;

            /**
             * @brief Name of options file
             */
            smos::smcore::SMSring m_optionsFile;
        };
    }
}
