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

#include "sgoptions.h"

#include <QFileDialog>

#include "ui_sgoptions.h"

namespace smos
{
    namespace smgui
    {
        //******************************************************************************
        SGOptions::SGOptions(QWidget *parent, smos::smcore::Options *options) : QDialog(parent), ui(new Ui::SGOptions), m_options(options)
        {
            ui->setupUi(this);
            this->dialogInit();
        }
        //******************************************************************************
        SGOptions::~SGOptions(void)
        {
            delete ui;
        }
        //******************************************************************************
        void SGOptions::dialogInit(void)
        {
            QString editorOld = QString::fromUtf8(this->m_options->codeEditorGet().c_str());
            ui->lineEditEditor->setText(editorOld);
        }
        //******************************************************************************
        void SGOptions::on_btnEditor_clicked(void)
        {
            QString fileName = QFileDialog::getOpenFileName(this, "Select editor", "", "Executable Files (*.exe);;All files (*.*)");
        }
    }
}
