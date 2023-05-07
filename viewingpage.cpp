#include "viewingpage.h"
#include "ui_viewingpage.h"

ViewingPage::ViewingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewingPage)
{
    ui->setupUi(this);
    ui->teamView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showStadiums(ui);
}

ViewingPage::~ViewingPage()
{
    delete ui;
}

void ViewingPage::on_sortBox_currentTextChanged(const QString &sortOption)
{
    if (sortOption == "Typology")
    {
//        showStadiums(ui);
    }
}

void ViewingPage::showStadiums(Ui::ViewingPage* ui)
{
    QMessageBox msgBox;
    QString teamName;
    QString stadiumName;
    int     seatCapacity;
    QString location;
    QString playingSurface;
    QString league;
    int     dateOpened;
    int distanceToCenter;
    QString ballparkTypology;
    QString roofType;
    int row = 0;
    int column = 0;

    ui->teamView->setColumnCount(10);
    ui->teamView->setRowCount(35);


    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
    ui->teamView->setHorizontalHeaderLabels(labels);


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information");

                        while(query1.next())
                        {
                            teamName = query1.value(0).toString();
                            stadiumName = query1.value(1).toString();
                            seatCapacity = query1.value(2).toInt();
                            location = query1.value(3).toString();
                            playingSurface = query1.value(4).toString();
                            league = query1.value(5).toString();
                            dateOpened = query1.value(6).toInt();
                            distanceToCenter = query1.value(7).toInt();
                            ballparkTypology = query1.value(8).toString();
                            roofType = query1.value(9).toString();

                            // Create Team Object
                            Team t(teamName.toStdString(), stadiumName.toStdString(), seatCapacity, location.toStdString(), playingSurface.toStdString(), league.toStdString(), dateOpened, distanceToCenter, ballparkTypology.toStdString(), roofType.toStdString());

                            ui->teamView->setItem(row,column++,new QTableWidgetItem(teamName));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(stadiumName));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(seatCapacity)));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(location));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(playingSurface));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(league));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(dateOpened)));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(distanceToCenter)));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(ballparkTypology));
                            ui->teamView->setItem(row,column++,new QTableWidgetItem(roofType));

                            column = 0;
                            row++;
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }
}

