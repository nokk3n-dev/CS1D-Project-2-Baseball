#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<adminpage.h>
#include<startpage.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Button_LogIn_clicked();

    void on_Button_Guest_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
