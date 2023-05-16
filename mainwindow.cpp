#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "planningtourpage.h"
#include "viewingpage.h"
#include "adminlogin.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting up the background
    ui->testLabel->setWindowFlags(Qt::FramelessWindowHint);
    ui->testLabel->setMask((new QPixmap("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\pitcher.gif"))->mask());
    QMovie *movie = new QMovie("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\pitcher.gif");
    ui->testLabel->setMovie(movie);
    movie->start();
    ui->testLabel->show();

    /*
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }*/
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

