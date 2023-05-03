#include "mainwindow.h"
#include "adminlogin.h"
#include "ui_mainwindow.h"
#include "adminoptions.h"
#include "planningtourpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->testLabel->setWindowFlags(Qt::FramelessWindowHint);
    ui->testLabel->setMask((new QPixmap("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\pitcher.gif"))->mask());

    QMovie *movie = new QMovie("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\pitcher.gif");
    ui->testLabel->setMovie(movie);
    movie->start();
    ui->testLabel->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_adminButton_clicked()
{
    AdminLogin adminWindow;
    adminWindow.setModal(true);
    adminWindow.exec();
}


void MainWindow::on_planTour_clicked()
{
    planningTourPage go;
    go.setModal(true);
    go.exec();
}


void MainWindow::on_viewTeams_clicked()
{
    AdminOptions go;
    go.setModal(true);
    go.exec();
}

