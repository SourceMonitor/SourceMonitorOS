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

#include "options.h"
#include <QDir>

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        Options::Options(QString optionsfile)
        {
            this->m_settings = std::unique_ptr<QSettings>(new QSettings(optionsfile, QSettings::IniFormat));
            this->optionsLoad();
        }
        //******************************************************************************
        Options::~Options(void)
        {
        }
        //******************************************************************************
        void Options::optionsLoad(void)
        {
            this->m_general_CodeEditor = this->valueGet<QString>("program", "codeeditor", "${filename}");
            this->m_logfileName = this->valueGet<QString>("program", "logfile", "smos.log");
        }
        //******************************************************************************
        void Options::optionsSave(void)
        {
            this->valueSet<QString>("program", "codeeditor", this->m_general_CodeEditor);
            this->valueSet<QString>("program", "logfile", this->m_logfileName);
            this->m_settings->sync();
        }
        //******************************************************************************
        QString Options::getMapKey(QString section, QString key)
        {
            QString tmpSection = section.replace("/", "").replace("\\", "").toUpper();
            QString tmpKey = key.replace("/", "").replace("\\", "").toLower();
            QString mapKey = tmpSection + "/" + tmpKey;
            return mapKey;
        }
        //******************************************************************************
        QString Options::codeEditorGet(void)
        {
            return this->m_general_CodeEditor;
        }
        //******************************************************************************
        void Options::codeEditorSet(QString codeeditor)
        {
            this->m_general_CodeEditor = codeeditor;
        }
        //******************************************************************************
        QString Options::logfileNameGet(void)
        {
            return this->m_logfileName;
        }
        //******************************************************************************
        void Options::logfileNameSet(QString logfileName)
        {
            this->m_logfileName = logfileName;
        }
    }
}
