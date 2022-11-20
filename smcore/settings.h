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

#pragma once

#include <QString>
#include <QSettings>
#include <QVariant>
#include <memory>
#include "smcore_global.h"

namespace smos
{
    namespace smcore
    {
        class SMCORE_EXPORT SMSettings
        {
        public:
            /**
             * @brief Default constructor
             *
             * @param settingsfile Name of settings file
             */
            SMSettings(QString settingsfile);
            /**
             * @brief Default destructor
             *
             */
            ~SMSettings(void);
            /**
             * @brief Get the absolute path to the logfile
             *
             * @return QString The absolute path to the logfile
             */
            QString getLogfileName(void);
            /**
             * @brief Set the absolute path to the logfile
             *
             * @param logfilename
             * @return QString
             */
            void setLogfileName(QString logfilename);

        protected:
            /**
             * @brief Instance of QSettings object
             *
             */
            std::unique_ptr<QSettings> m_settings;
            /**
             * @brief Name of used ini file
             *
             */
            QString m_filename;
            /**
             * @brief Internal method for initialization, used in constructor
             *
             */
            void settingsInit(void);
            /**
             * @brief Method to build the key for accessing QSettings
             *
             * @param section Section name
             * @param key Key name
             * @return QString The key
             */
            QString getMapKey(QString section, QString key);
            /**
             * @brief Templated method to get a value
             *
             * @tparam argumentType Datatype of value
             * @param section Section to set value
             * @param key Key to set value
             * @param defaultValue Default value
             */
            template <typename argumentType>
            argumentType valueGet(QString section, QString key, argumentType defaultValue)
            {
                QString mapKey = this->getMapKey(section, key);
                QVariant defaultValueArgument(defaultValue);
                QVariant valueRaw = this->m_settings->value(mapKey, defaultValueArgument);
                argumentType value = valueRaw.value<argumentType>();
                return value;
            }
            /**
             * @brief Templated method to set a value
             *
             * @tparam argumentType Datatype of value
             * @param section Section to set value
             * @param key Key to set value
             * @param value Value itself
             */
            template <typename argumentType>
            void valueSet(QString section, QString key, argumentType value)
            {
                QString mapKey = this->getMapKey(section, key);
                this->m_settings->setValue(mapKey, value);
            }
        };
    }
}
