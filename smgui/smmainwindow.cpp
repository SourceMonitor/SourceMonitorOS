#include "smmainwindow.h"
#include "./ui_smmainwindow.h"

SMMainWindow::SMMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SMMainWindow)
{
    ui->setupUi(this);
}

SMMainWindow::~SMMainWindow()
{
    delete ui;
}

void SMMainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

