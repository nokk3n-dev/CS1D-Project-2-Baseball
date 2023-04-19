#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_LogIn_clicked()
{
    QString username = ui->Input_Username->text();
    QString password = ui->Input_Password->text();
    AdminPage loginSuccessPage;
    if(username == "Admin"&&password=="ABCD"){
        this->close();
        loginSuccessPage.setModal(true);
        loginSuccessPage.exec();
    } else {
        this->ui->ErrorMessage->setText("Incorrect Username/Password. Please Try Again.");
    }
}


void MainWindow::on_Button_Guest_clicked()
{
    StartPage guestLoginPage;
    this->close();
    guestLoginPage.setModal(true);
    guestLoginPage.exec();
}

