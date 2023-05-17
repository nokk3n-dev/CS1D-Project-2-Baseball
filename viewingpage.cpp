#include "viewingpage.h"
#include "ui_viewingpage.h"
#include "dbhandler.h"
#include <QWidget>

ViewingPage::ViewingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewingPage)
{
    ui->setupUi(this);
    ui->teamView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set up background
    QPixmap bkgnd("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\viewingPage.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // Hide seating capacity
    ui->seatingCapcity_label->hide();
    ui->seatNum_label->hide();
    seatingCapcity = 0;

    // Set up text color
//    ui->baseballTeamsLabel->setText("<font color='white'>Baseball Teams</font>");
//    ui->sortByLabel->setText("<font color='white'>Sort By</font>");

    // Get data from database
    QMessageBox msgBox;

    // Linked List to hold teams
    TeamList<Team> initialList;

    // Ensure the table is clear
    ui->teamView->clear();

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY TEAM_NAME");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "")
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                initialList.insert(t);
                                ui->viewTeam_box->addItem(QString::fromStdString(teamName));
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, initialList);
}

ViewingPage::~ViewingPage()
{
    delete ui;
}

void ViewingPage::on_sortBox_currentTextChanged(const QString &sortOption)
{
    if (sortOption == "Team Name")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByTeam();
    } else if (sortOption == "Stadium Name")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByStadiumName();
    } else if (sortOption == "American League")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByLeague("American");
    } else if (sortOption == "National League")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByLeague("National");
    } else if (sortOption == "Typology")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByTypology();
    } else if (sortOption == "Date Opened")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        sortByDate();
    } else if (sortOption == "Seating Capacity")
    {

        sortBySeat();
    } else if (sortOption == "Greatest Distance to Centre Field")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        showGreatestDTC();
    } else if (sortOption == "Smallest Distance to Centre Field")
    {
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        showSmallestDTC();
    } else if (sortOption == "Open Roof")
    {    
        // Hide seating capacity
        ui->seatingCapcity_label->hide();
        ui->seatNum_label->hide();
        showOpenRoof();
    }
}

void ViewingPage::sortByTeam()
{
    // Get data from database
    QMessageBox msgBox;

    // Linked List to hold teams
    TeamList<Team> initialList;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY TEAM_NAME");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "")
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                initialList.insert(t);
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, initialList);
}

void ViewingPage::sortByStadiumName()
{
    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> sortedStadium;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY STADIUM_NAME");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "")
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                sortedStadium.insert(t);
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, sortedStadium);
}

void ViewingPage::sortBySeat()
{
    seatingCapcity = 0;
    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> sortedSeat;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY SEAT_CAPACITY");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "")
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                sortedSeat.insert(t);
                                seatingCapcity += seatCapacity;
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, sortedSeat);

    // Set labels
    ui->seatingCapcity_label->setText("Seating Capacity");
    ui->seatNum_label->setText(QString::number(seatingCapcity));

    // Show seating capacity
    ui->seatingCapcity_label->show();
    ui->seatNum_label->show();
}

void ViewingPage::sortByLeague(string whatLeague)
{

        // Get data from database
        QMessageBox msgBox;

        TeamList<Team> sortedLeague;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
            if(dbHandler.open())
            {
                QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                                 "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY TEAM_NAME");

                            while(query1.next())
                            {
                                string teamName = query1.value(0).toString().toStdString();
                                string stadiumName = query1.value(1).toString().toStdString();
                                int seatCapacity = query1.value(2).toInt();
                                string location = query1.value(3).toString().toStdString();
                                string playingSurface = query1.value(4).toString().toStdString();
                                string league = query1.value(5).toString().toStdString();
                                int dateOpened = query1.value(6).toInt();
                                int distanceToCenter = query1.value(7).toInt();
                                string ballparkTypology = query1.value(8).toString().toStdString();
                                string roofType = query1.value(9).toString().toStdString();

                                // Only add if league == the specific league in question
                                if (league == whatLeague)
                                {
                                    // Create Team Object
                                    Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                    sortedLeague.insert(t);
                                }
                            }

            }
            else
            {
                msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
                msgBox.exec();
                dbHandler.close();
            }

            showStadiums(ui, sortedLeague);
}

void ViewingPage::sortByTypology()
{
        // Get data from database
        QMessageBox msgBox;

        TeamList<Team> sortedTypology;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
            if(dbHandler.open())
            {
                QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                                 "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY BALLPARK_TYPOLOGY");

                            while(query1.next())
                            {
                                string teamName = query1.value(0).toString().toStdString();
                                string stadiumName = query1.value(1).toString().toStdString();
                                int seatCapacity = query1.value(2).toInt();
                                string location = query1.value(3).toString().toStdString();
                                string playingSurface = query1.value(4).toString().toStdString();
                                string league = query1.value(5).toString().toStdString();
                                int dateOpened = query1.value(6).toInt();
                                int distanceToCenter = query1.value(7).toInt();
                                string ballparkTypology = query1.value(8).toString().toStdString();
                                string roofType = query1.value(9).toString().toStdString();

                                if (teamName != "")
                                {
                                    // Create Team Object
                                    Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                    sortedTypology.insert(t);
                                }
                            }

            }
            else
            {
                msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
                msgBox.exec();
                dbHandler.close();
            }

        showStadiums(ui, sortedTypology);
}

void ViewingPage::showOpenRoof()
{
    int numOpenRoofs = 0;

    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> sortedSeat;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY TEAM_NAME");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "" && roofType == "Open")
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                sortedSeat.insert(t);
                                numOpenRoofs++;
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, sortedSeat);
    ui->seatingCapcity_label->setText("Number of Open Roofs: ");
    ui->seatNum_label->setText(QString::number(numOpenRoofs));
    ui->seatingCapcity_label->show();
    ui->seatNum_label->show();
}

void ViewingPage::sortByDate()
{
    // Get data from database
        QMessageBox msgBox;

        TeamList<Team> sortedDate;

        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
            if(dbHandler.open())
            {
                QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                                 "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY DATE_OPENED");

                            while(query1.next())
                            {
                                string teamName = query1.value(0).toString().toStdString();
                                string stadiumName = query1.value(1).toString().toStdString();
                                int seatCapacity = query1.value(2).toInt();
                                string location = query1.value(3).toString().toStdString();
                                string playingSurface = query1.value(4).toString().toStdString();
                                string league = query1.value(5).toString().toStdString();
                                int dateOpened = query1.value(6).toInt();
                                int distanceToCenter = query1.value(7).toInt();
                                string ballparkTypology = query1.value(8).toString().toStdString();
                                string roofType = query1.value(9).toString().toStdString();

                                if (teamName != "")
                                {
                                    // Create Team Object
                                    Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                    sortedDate.insert(t);
                                }
                            }

            }
            else
            {
                msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
                msgBox.exec();
                dbHandler.close();
            }

        showStadiums(ui, sortedDate);
}

void ViewingPage::showGreatestDTC()
{
    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> greatestDTC;

    // Count variable
    int count = 0;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY DISTANCE_TO_CENTER_FIELD DESC");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "" && roofType == "Open" && count < 2)
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                greatestDTC.insert(t);
                                count++;
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, greatestDTC);
}

void ViewingPage::showSmallestDTC()
{
    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> sortedSeat;

    // count variable
    int count = 0;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY DISTANCE_TO_CENTER_FIELD");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName != "" && roofType == "Open" && count < 2)
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                sortedSeat.insert(t);
                                count++;
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, sortedSeat);
}

void ViewingPage::showStadiums(Ui::ViewingPage* ui, TeamList<Team> list)
{

    // Ensure the table is clear
    ui->teamView->clear();

    // Row and Column variables
    int row = 0;
    int column = 0;

    // Set the number of columns and rows
    ui->teamView->setColumnCount(10);
    ui->teamView->setRowCount(35);

    // Fix column widths
    ui->teamView->setColumnWidth(0, 130);
    ui->teamView->setColumnWidth(1, 210);
    ui->teamView->setColumnWidth(2, 65);
    ui->teamView->setColumnWidth(3, 150);
    ui->teamView->setColumnWidth(4, 90);
    ui->teamView->setColumnWidth(5, 65);
    ui->teamView->setColumnWidth(6, 65);
    ui->teamView->setColumnWidth(7, 110);
    ui->teamView->setColumnWidth(8, 90);
    ui->teamView->setColumnWidth(9, 80);

    // Set the names of the columns
    QStringList labels = { "Team Name","Stadium Name", "Capacity", "Location", "Playing Surface", "League",
                           "Opened", "Distance to Center", "Ballpark Type", "Roof Type"};
    ui->teamView->setHorizontalHeaderLabels(labels);

    // Create current node for iteration
    TeamNode<Team> *currentNode = list.getHead();
    while(currentNode != nullptr)
    {
        // Get all the data from the node
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getName())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getStadium())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getCapacity())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getLocation())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getSurface())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getLeague())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getDate())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getDTC())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getTypology())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getRoof())));

        // Move to next node
        currentNode = currentNode->next;

        column = 0;
        row++;
    }

    delete currentNode;
}


void ViewingPage::on_viewTeam_box_currentTextChanged(const QString &arg1)
{
    // Hide seating capacity
    ui->seatingCapcity_label->hide();
    ui->seatNum_label->hide();
    // Get data from database
    QMessageBox msgBox;

    TeamList<Team> team;

    // count variable
    int count = 0;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY DISTANCE_TO_CENTER_FIELD");

                        while(query1.next())
                        {
                            string teamName = query1.value(0).toString().toStdString();
                            string stadiumName = query1.value(1).toString().toStdString();
                            int seatCapacity = query1.value(2).toInt();
                            string location = query1.value(3).toString().toStdString();
                            string playingSurface = query1.value(4).toString().toStdString();
                            string league = query1.value(5).toString().toStdString();
                            int dateOpened = query1.value(6).toInt();
                            int distanceToCenter = query1.value(7).toInt();
                            string ballparkTypology = query1.value(8).toString().toStdString();
                            string roofType = query1.value(9).toString().toStdString();

                            if (teamName == arg1.toStdString())
                            {
                                // Create Team Object
                                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                                team.insert(t);
                                count++;
                            }
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, team);
}

