//***************************************************************************
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
//***************************************************************************

#include "settings.h"
#include <QCoreApplication>
#include <QDir>

namespace smos
{
    namespace smcore
    {
        //******************************************************************************
        SMSettings::SMSettings(QString settingsfile) : m_filename(settingsfile)
        {
            this->settingsInit();
        }
        //******************************************************************************
        SMSettings::~SMSettings(void)
        {
        }
        //******************************************************************************
        QString SMSettings::getMapKey(QString section, QString key)
        {
            QString tmpSection = section.replace("/", "").replace("\\", "").toUpper();
            QString tmpKey = key.replace("/", "").replace("\\", "").toLower();
            QString mapKey = tmpSection + "/" + tmpKey;
            return mapKey;
        }
        //******************************************************************************
        void SMSettings::settingsInit(void)
        {
            if (nullptr == this->m_settings)
            {
                this->m_settings = std::unique_ptr<QSettings>(new QSettings(this->m_filename, QSettings::IniFormat));
                this->m_filename = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + this->m_filename);
            }
        }
        //******************************************************************************
        QString SMSettings::getLogfileName(void)
        {
            QString logfileDefault = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + "smos.log");
            QString logfile = this->valueGet<QString>("Logging", "Logfilename", logfileDefault);
            if (logfile == logfileDefault)
            {
                this->setLogfileName(logfileDefault);
            }
            return logfile;
        }
        //******************************************************************************
        void SMSettings::setLogfileName(QString logfilename)
        {
            this->valueSet<QString>("Logging", "Logfilename", logfilename);
        }
    }
}
