#include "adminlogin.h"
#include "adminoptions.h"
#include "ui_adminlogin.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    ui->accessDenied->setHidden(true);
    ui->userDenied->setHidden(true);
    ui->passDenied->setHidden(true);
    ui->userPassDenied->setHidden(true);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_loginButton_clicked()
{
    QString username = ui->inputUsername->text();
    QString password = ui->inputPassword->text();
    if (username == "Admin" && password == "password") {
        this->close();
        AdminOptions LoginSuccess;
        LoginSuccess.setModal(true);
        LoginSuccess.exec();
    } else if (username != "Admin" && password == "password") {
        ui->accessDenied->setHidden(true);
        ui->userDenied->setHidden(true);
        ui->passDenied->setHidden(true);
        ui->userPassDenied->setHidden(true);
        ui->accessDenied->setHidden(false);
        ui->userDenied->setHidden(false);
    } else if (username == "Admin" && password != "password") {
        ui->accessDenied->setHidden(true);
        ui->userDenied->setHidden(true);
        ui->passDenied->setHidden(true);
        ui->userPassDenied->setHidden(true);
        ui->accessDenied->setHidden(false);
        ui->passDenied->setHidden(false);
    } else if (username != "Admin" && password != "password") {
        ui->accessDenied->setHidden(true);
        ui->userDenied->setHidden(true);
        ui->passDenied->setHidden(true);
        ui->userPassDenied->setHidden(true);
        ui->accessDenied->setHidden(false);
        ui->userPassDenied->setHidden(false);
    } else {
        ui->accessDenied->setHidden(true);
        ui->userDenied->setHidden(true);
        ui->passDenied->setHidden(true);
        ui->userPassDenied->setHidden(true);
        ui->accessDenied->setHidden(false);
    }
}

