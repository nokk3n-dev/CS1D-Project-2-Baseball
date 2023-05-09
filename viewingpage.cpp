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

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                             "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information");

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

                            // Create Team Object
                            Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                            teamList.insert(t);
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui, teamList);
}

ViewingPage::~ViewingPage()
{
    delete ui;
}

void ViewingPage::on_sortBox_currentTextChanged(const QString &sortOption)
{
    if (sortOption == "Team Name")
    {
        sortByTeam();
    } else if (sortOption == "Stadium Name")
    {
        sortByStadiumName();
    } else if (sortOption == "American League")
    {
        sortByLeague(sortOption.toStdString());
    } else if (sortOption == "National League")
    {
        sortByLeague(sortOption.toStdString());
    } else if (sortOption == "Typology")
    {
        sortByTypology();
    } else if (sortOption == "Date Opened")
    {
        sortByDate();
    } else if (sortOption == "Seating Capcity")
    {
        sortBySeat();
    } else if (sortOption == "Greatest Distance to Centre Field")
    {
        showGreatestDTC();
    } else if (sortOption == "Smallest Distance to Centre Field")
    {
        showSmallestDTC();
    } else if (sortOption == "Open Roof")
    {
        showOpenRoof();
    }
}

void ViewingPage::sortByTeam()
{
    // Row and Column Variables
    int row = 0;
    int column = 0;

    // Set the number of columns and rows
    ui->teamView->setColumnCount(10);
    ui->teamView->setRowCount(35);

    // Set the names of the columns
    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
    ui->teamView->setHorizontalHeaderLabels(labels);

    Team team_array[31] = {
        Team("Arizona Diamondbacks", "Chase Field", 48686, "Phoenix, Arizona", "Grass", "National", 1998, 407, "Retro Modern", "Retractable"),
        Team("Atlanta Braves", "SunTrust Park", 41149, "Cumberland, Georgia", "Grass", "National", 2017, 400, "Retro Modern", "Open"),
        Team("Baltimore Orioles", "Oriole Park at Camden Yards", 45971, "Baltimore, Maryland", "Grass", "American", 1992, 410, "Retro Classic", "Open"),
        Team("Boston Red Sox", "Fenway Park", 37731, "Boston, Massachusetts", "Grass", "American", 1912, 420, "Jewel Box", "Open"),
        Team("Chicago Cubs", "Wrigley Field", 41268, "Chicago, Illinois", "Grass", "National", 1914, 400, "Jewel Box", "Open"),
        Team("Chicago White Sox", "Guaranteed Rate Field", 40615, "Chicago, Illinois", "Grass", "American", 1991, 400, "Retro Classic", "Open"),
        Team("Cincinnati Reds", "Great American Ball Park", 42319, "Cincinnati, Ohio", "Grass", "National", 2003, 404, "Retro Modern", "Open"),
        Team("Cleveland Indians", "Progressive Field", 35051, "Cleveland, Ohio", "Grass", "American", 1994, 410, "Retro Modern", "Open"),
        Team("Colorado Rockies", "Coors Field", 50398, "Denver, Colorado", "Grass", "National", 1995, 415, "Retro Classic", "Open"),
        Team("Detroit Tigers", "Comerica Park", 41299, "Detroit, Michigan", "Grass", "American",2000, 420, "Retro Classic", "Open"),
        Team("Houston Astros", "Minute Maid Park", 41168, "Houston, Texas", "Grass", "American", 2000, 409, "Retro Modern", "Retractable"),
        Team("Kansas City Royals", "Kauffman Stadium", 37903, "Kansas City, Missouri", "Grass", "American", 1973, 410, "Retro Modern", "Open"),
        Team("Los Angeles Angels", "Angel Stadium", 45477, "Anaheim, California", "Grass", "American", 1966, 396, "Retro Modern", "Open"),
        Team("Los Angeles Dodgers", "Dodger Stadium", 56000, "Los Angeles, California", "Grass", "National", 1962, 400, "Modern", "Open"),
        Team("Miami Marlins", "Marlins Park", 36742, "Miami, Florida", "Grass", "National", 2012, 407, "Contemporary", "Retractable"),
        Team("Milwaukee Brewers", "Miller Park", 41900, "Milwaukee, Wisconsin", "Grass", "National", 2001, 400, "Retro Modern", "Retractable"),
        Team("Minnesota Twins", "Target Field", 38885, "Minneapolis, Minnesota", "Grass", "American", 2010, 404, "Retro Modern", "Open"),
        Team("New York Mets", "Citi Fields", 41922, "Queens, New York", "Grass", "National", 2009, 408, "Retro Classic", "Open"),
        Team("New York Yankees", "Yankee Stadium", 47422, "Bronx, New York", "Grass", "American", 2009, 408, "Retro Classic", "Open"),
        Team("Oakland Athletics", "Oakland Alameda County Coliseum", 47170, "Oakland, California", "Grass", "American", 1966, 400, "Multipurpose", "Open"),
        Team("Philadelphia Phillies", "Citizens Bank Park", 43651, "Philadelphia, Pennsylvania", "Grass", "National", 2004, 401, "Retro Classic", "Open"),
        Team("Pittsburgh Pirates", "PNC Park", 38362, "Pittsburgh, Pennsylvania", "Grass", "National", 2001, 399, "Retro Classic", "Open"),
        Team("San Diego Padres", "Petco Park", 40209, "San Diego, California", "Grass", "National", 2004, 396, "Retro Modern", "Open"),
        Team("San Francisco Giants", "Oracle Park", 41915, "San Francisco, California", "Grass", "National", 2000, 399, "Retro Classic", "Open"),
        Team("Seattle Mariners", "Safeco Field", 47943, "Seattle, Washington", "Grass", "American", 1999, 401, "Retro Modern", "Retractable"),
        Team("St. Louis Cardinals", "Busch Stadium", 45529, "St. Louis, Missouri", "Grass", "National", 2006, 400, "Retro Classic", "Open"),
        Team("Tampa Bay Rays", "Tropicana Field", 31042, "St. Petersburg, Florida", "AstroTurf GameDay Grass", "American", 1990, 404, "Multipurpose", "Fixed"),
        Team("Texas Rangers", "Globe Life Park in Arlington", 48114, "Arlington, Texas", "Grass", "American", 1994, 400, "Retro Classic", "Open"),
        Team("Toronto Blue Jays", "Rogers Centre", 49282, "Toronto, Ontario", "AstroTurf GameDay Grass 3D", "American", 1989, 400, "Multipurpose", "Retractable"),
        Team("Washington Nationals", "Nationals Park", 41339, "Washington, D.C.", "Grass", "National", 2008, 402, "Retro Modern", "Open"),
        Team("", "", 0, "", "", "", 0, 0, "", "")
    };

    // Loop through the array
    for (Team team : team_array)
    {
        // Store data in the UI
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getName())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getStadium())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getCapacity())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getLocation())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getSurface())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getLeague())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getDate())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getDTC())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getTypology())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getRoof())));

        // Increment columns and rows
        column = 0;
        row++;
    }
}

void ViewingPage::sortByStadiumName()
{

}

void ViewingPage::sortBySeat()
{

}

void ViewingPage::sortByLeague(string league)
{

}

void ViewingPage::sortByTypology()
{

}

void ViewingPage::showOpenRoof()
{
    // Row and Column Variables
    int row = 0;
    int column = 0;

    // Set the number of columns and rows
    ui->teamView->setColumnCount(10);
    ui->teamView->setRowCount(24);

    // Set the names of the columns
    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
    ui->teamView->setHorizontalHeaderLabels(labels);

    Team team_array[24] = {
        Team("Atlanta Braves", "SunTrust Park", 41149, "Cumberland, Georgia", "Grass", "National", 2017, 400, "Retro Modern", "Open"),
        Team("Baltimore Orioles", "Oriole Park at Camden Yards", 45971, "Baltimore, Maryland", "Grass", "American", 1992, 410, "Retro Classic", "Open"),
        Team("Boston Red Sox", "Fenway Park", 37731, "Boston, Massachusetts", "Grass", "American", 1912, 420, "Jewel Box", "Open"),
        Team("Chicago Cubs", "Wrigley Field", 41268, "Chicago, Illinois", "Grass", "National", 1914, 400, "Jewel Box", "Open"),
        Team("Chicago White Sox", "Guaranteed Rate Field", 40615, "Chicago, Illinois", "Grass", "American", 1991, 400, "Retro Classic", "Open"),
        Team("Cincinnati Reds", "Great American Ball Park", 42319, "Cincinnati, Ohio", "Grass", "National", 2003, 404, "Retro Modern", "Open"),
        Team("Cleveland Indians", "Progressive Field", 35051, "Cleveland, Ohio", "Grass", "American", 1994, 410, "Retro Modern", "Open"),
        Team("Colorado Rockies", "Coors Field", 50398, "Denver, Colorado", "Grass", "National", 1995, 415, "Retro Classic", "Open"),
        Team("Detroit Tigers", "Comerica Park", 41299, "Detroit, Michigan", "Grass", "American",2000, 420, "Retro Classic", "Open"),
        Team("Kansas City Royals", "Kauffman Stadium", 37903, "Kansas City, Missouri", "Grass", "American", 1973, 410, "Retro Modern", "Open"),
        Team("Los Angeles Angels", "Angel Stadium", 45477, "Anaheim, California", "Grass", "American", 1966, 396, "Retro Modern", "Open"),
        Team("Los Angeles Dodgers", "Dodger Stadium", 56000, "Los Angeles, California", "Grass", "National", 1962, 400, "Modern", "Open"),
        Team("Minnesota Twins", "Target Field", 38885, "Minneapolis, Minnesota", "Grass", "American", 2010, 404, "Retro Modern", "Open"),
        Team("New York Mets", "Citi Fields", 41922, "Queens, New York", "Grass", "National", 2009, 408, "Retro Classic", "Open"),
        Team("New York Yankees", "Yankee Stadium", 47422, "Bronx, New York", "Grass", "American", 2009, 408, "Retro Classic", "Open"),
        Team("Oakland Athletics", "Oakland Alameda County Coliseum", 47170, "Oakland, California", "Grass", "American", 1966, 400, "Multipurpose", "Open"),
        Team("Philadelphia Phillies", "Citizens Bank Park", 43651, "Philadelphia, Pennsylvania", "Grass", "National", 2004, 401, "Retro Classic", "Open"),
        Team("Pittsburgh Pirates", "PNC Park", 38362, "Pittsburgh, Pennsylvania", "Grass", "National", 2001, 399, "Retro Classic", "Open"),
        Team("San Diego Padres", "Petco Park", 40209, "San Diego, California", "Grass", "National", 2004, 396, "Retro Modern", "Open"),
        Team("San Francisco Giants", "Oracle Park", 41915, "San Francisco, California", "Grass", "National", 2000, 399, "Retro Classic", "Open"),
        Team("St. Louis Cardinals", "Busch Stadium", 45529, "St. Louis, Missouri", "Grass", "National", 2006, 400, "Retro Classic", "Open"),
        Team("Texas Rangers", "Globe Life Park in Arlington", 48114, "Arlington, Texas", "Grass", "American", 1994, 400, "Retro Classic", "Open"),
        Team("Washington Nationals", "Nationals Park", 41339, "Washington, D.C.", "Grass", "National", 2008, 402, "Retro Modern", "Open"),
        Team("", "", 0, "", "", "", 0, 0, "", "")
    };

    // Loop through the array
    for (Team team : team_array)
    {
        // Store data in the UI
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getName())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getStadium())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getCapacity())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getLocation())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getSurface())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getLeague())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getDate())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::number(team.getDTC())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getTypology())));
        ui->teamView->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(team.getRoof())));

        // Increment columns and rows
        column = 0;
        row++;
    }
}

void ViewingPage::sortByDate()
{

}

void ViewingPage::showGreatestDTC()
{

}

void ViewingPage::showSmallestDTC()
{

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

