#ifndef SMMAINWINDOW_H
#define SMMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SMMainWindow;
}
QT_END_NAMESPACE

class SMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SMMainWindow(QWidget *parent = nullptr);
    ~SMMainWindow();

private slots:
    void on_actionExit_triggered();

private:
    Ui::SMMainWindow *ui;
};
#endif // SMMAINWINDOW_H
