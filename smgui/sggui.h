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

#include <QMainWindow>
#include "options.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SGGUI;
}
QT_END_NAMESPACE

namespace smos
{
    namespace smgui
    {
        class SGGUI : public QMainWindow
        {
            Q_OBJECT

        public:
            /**
             * @brief Default constructor
             *
             * @param parent
             */
            SGGUI(QWidget *parent = nullptr);
            /**
             * @brief Default desctructor
             *
             */
            ~SGGUI(void);
            /**
             * @brief Initialize UI
             *
             * @return true On succes
             * @return false On failure
             */
            bool initUI(void);

        private slots:
            /**
             * @brief Called when menu entry 'File - Exit' is triggered
             *
             */
            void on_actionExit_triggered(void);

            /**
             * @brief Called when menu entry 'Help - View License' is triggered
             *
             */
            void on_actionView_License_triggered(void);

            /**
             * @brief Called when menu entry 'Help - About SourceMonitor' is triggered
             *
             */
            void on_actionAbout_SourceMonitor_triggered(void);

            /**
             * @brief Called when menu entry 'File - Options' is triggered
             *
             */
            void on_actionOptions_triggered(void);

        private:
            /**
             * @brief Instance of UI
             *
             */
            Ui::SGGUI *ui;
            /**
             * @brief Pointer to program options
             *
             */
            // std::shared_ptr<smos::smcore::SMOptions> smOptions = nullptr;
            smos::smcore::Options *options = nullptr;
        };
    }
}
