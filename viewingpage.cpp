#include "viewingpage.h"
#include "ui_viewingpage.h"
#include "dbhandler.h"

ViewingPage::ViewingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewingPage)
{
    ui->setupUi(this);
    ui->teamView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
        // Ensure the table is clear
        ui->teamView->clear();

        sortByTeam();
    } else if (sortOption == "Stadium Name")
    {    // Ensure the table is clear
        ui->teamView->clear();

        sortByStadiumName();
    } else if (sortOption == "American League")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        sortByLeague("American");
    } else if (sortOption == "National League")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        sortByLeague("National");
    } else if (sortOption == "Typology")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        sortByTypology();
    } else if (sortOption == "Date Opened")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        sortByDate();
    } else if (sortOption == "Seating Capacity")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        sortBySeat();
    } else if (sortOption == "Greatest Distance to Centre Field")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        showGreatestDTC();
    } else if (sortOption == "Smallest Distance to Centre Field")
    {
        // Ensure the table is clear
        ui->teamView->clear();

        showSmallestDTC();
    } else if (sortOption == "Open Roof")
    {
        // Ensure the table is clear
        ui->teamView->clear();

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
    // Row and Column variables
    int row = 0;
    int column = 0;

    // Set the number of columns and rows
    ui->teamView->setColumnCount(10);
    ui->teamView->setRowCount(35);

    // Set the names of the columns
    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
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

