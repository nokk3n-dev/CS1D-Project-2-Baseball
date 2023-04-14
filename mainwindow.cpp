#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminoptions.h"

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


void MainWindow::on_adminButton_clicked()
{
    AdminOptions go;
    go.setModal(true);
    go.exec();
}

