#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlogin.h"
#include "planningtourpage.h"
#include "viewingpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting up the background
    ui->testLabel->setWindowFlags(Qt::FramelessWindowHint);
    ui->testLabel->setMask((new QPixmap("/Users/carter/Documents/GitHub/CS1D-Project-2-Baseball/Resources/pitcher.gif"))->mask());
    QMovie *movie = new QMovie("/Users/carter/Documents/GitHub/CS1D-Project-2-Baseball/Resources/pitcher.gif");
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
    ViewingPage go;
    go.setModal(true);
    go.exec();
}

