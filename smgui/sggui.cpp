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

#include "sggui.h"

#include <QDir>
#include <QMessageBox>

#include "about.h"
#include "factory.h"
#include "license.h"
#include "options.h"
#include "sgoptions.h"
#include "ui_sggui.h"

namespace smos
{
    namespace smgui
    {
        //******************************************************************************
        SGGUI::SGGUI(QWidget *parent)
            : QMainWindow(parent), ui(new Ui::SGGUI)
        {
            ui->setupUi(this);
        }
        //******************************************************************************
        SGGUI::~SGGUI(void)
        {
            delete ui;
        }
        //******************************************************************************
        bool SGGUI::initUI(void)
        {
            QString optionfileName = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "smos.ini");
            // std::shared_ptr<SMOptions> smOptions = smos::smcore::SMFactory::getOptions(optionfileName);
            this->options = smos::smcore::Factory::getOptions(optionfileName);
            return true;
        }
        //******************************************************************************
        void SGGUI::on_actionExit_triggered(void)
        {
            QCoreApplication::quit();
        }
        //******************************************************************************
        void SGGUI::on_actionView_License_triggered(void)
        {
            QMessageBox::about(this, "SourceMonitorOS License", smos::smcore::License::getLicense());
        }
        //******************************************************************************
        void SGGUI::on_actionAbout_SourceMonitor_triggered(void)
        {
            QMessageBox::about(this, "About SourceMonitorOS", smos::smcore::About::getAbout());
        }
        //******************************************************************************
        void SGGUI::on_actionOptions_triggered(void)
        {
            smos::smgui::SGOptions optionsDialog(this, this->options);

            optionsDialog.setModal(true);
            optionsDialog.exec();
        }
    }
}
