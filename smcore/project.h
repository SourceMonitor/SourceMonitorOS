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

#include "smstring.h"
#include "error.h"

namespace smos
{
    namespace smcore
    {
        class Project
        {
        public:
            /**
             * @brief Construct a new Project object
             */
            Project(void);

            /**
             * @brief Destroy the Project object
             */
            ~Project(void);

            /**
             * @brief Load project data
             *
             * @param filename Name of project file
             *
             * @return smos::smcore::Error::ErrorCode
             */
            smos::smcore::Error::ErrorCode loadProject(smos::smcore::SMSring filename);

            /**
             * @brief Save project data
             *
             * @param filename Name of project file
             *
             * @return smos::smcore::Error::ErrorCode
             */
            smos::smcore::Error::ErrorCode saveProject(smos::smcore::SMSring filename);

            smos::smcore::SMSring getProjectName(void);
            void setProjectName(smos::smcore::SMSring projectName);

        private:
            /**
             * @brief Name of project
             */
            smos::smcore::SMSring m_ProjectName;
            /**
             * @brief Location of project source code
             */
            smos::smcore::SMSring m_sDirectory;
            /**
             * @brief Filename of project file
             */
            smos::smcore::SMSring m_sProjectFileName;
            /**
             * @brief Location of project file
             */
            smos::smcore::SMSring m_sProjectFileDirectory;
            /**
             * @brief Project setting: Include subdirectories yes/no
             */
            bool m_fIncludeSubdirectories;
            /**
             * @brief Some options - need more inspection for knowing kind of options and what they tweak
             */
            int m_eOptionFlags;
            /**
             * @brief Reference to language object
             */
            // SMLanguage *m_poLanguageExemplar; // exemplar is used to build all project language objects
            /**
             * @brief Version object
             */
            // SMVersion m_oVersion;             // version of SourceMonitor that created this project
            /**
             * @brief List of project checkpoints, ordered list?
             *
             */
            // CheckpointList m_oCheckpoints;    // list of checkponts in the project

            // transient (non-persisted) members
            // CStringArray m_saFilesXmlPathNames;   // Xml files that holds the paths to all project files
            // CStringArray m_saXmlFileXPathFilters; // XPath specifications that define locations of project files in xml file
            // CString m_sBaseDirectory;             // base directory for source files with relative references resolved
            // CString m_sRootDirectory;             // base directory as read from project file - may be relative
            // CString m_sXmlFileDirectory;          // directory where the current XML file is located
            // CStringArray m_saSubDirectories;      // list of (relative) sub-directories
            // SubdirectoryMode m_eSubdirectoryMode;
            // CStringArray m_saIncludeExtensionList;  // list of file extensions to search for
            // CStringArray m_saExcludeExtensionList;  // list of file extensions to exclude (subset of the include list)
            // CWordArray m_waExcludeExtensionLengths; // lengths of the extensions in the exclude list
            // CheckpointList m_oDeletedCheckpoints;   // list of deleted checkponts
            // bool m_fNewFileFormat;                  // true if project is saved in the new binary format instead of the MFC Serialize format
            // bool m_fProcessingXMLTest;              // controls display of XML extraction errors only when user is testing an XML specification
        };
    }
}
