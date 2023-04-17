#include "adminoptions.h"
#include "ui_adminoptions.h"

AdminOptions::AdminOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOptions)
{
    ui->setupUi(this);
    ui->stadiumDisplayWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showStadiums(ui);
}

AdminOptions::~AdminOptions()
{
    delete ui;
}


void AdminOptions::showStadiums(Ui::AdminOptions* ui)
{
    QMessageBox msgBox;
    QString teamName;
    QString stadiumName;
    int     seatCapacity;
    QString location;
    QString playingSurface;
    QString league;
    int     dateOpened;
    QString distanceToCenter;
    QString ballparkTypology;
    QString roofType;
    int id;
    int row = 0;
    int column = 0;


    QTableWidgetItem *item = new QTableWidgetItem;

    ui->stadiumDisplayWidget->setColumnCount(10);
    ui->stadiumDisplayWidget->setRowCount(35);


    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
    ui->stadiumDisplayWidget->setHorizontalHeaderLabels(labels);


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
                            distanceToCenter = query1.value(7).toString();
                            ballparkTypology = query1.value(8).toString();
                            roofType = query1.value(9).toString();

                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(teamName));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(stadiumName));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::number(seatCapacity)));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(location));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(playingSurface));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(league));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::number(dateOpened)));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem((distanceToCenter)));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(ballparkTypology));
                            ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(roofType));

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
