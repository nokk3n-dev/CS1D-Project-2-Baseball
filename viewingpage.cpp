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
        sortByTeam(ui);
    } else if (sortOption == "Stadium Name")
    {
        sortByStadiumName(ui);
    } else if (sortOption == "American League")
    {
        sortByLeague(ui, sortOption.toStdString());
    } else if (sortOption == "National League")
    {
        sortByLeague(ui, sortOption.toStdString());
    } else if (sortOption == "Typology")
    {
        sortByTypology(ui);
    } else if (sortOption == "Date Opened")
    {
        sortByDate(ui);
    } else if (sortOption == "Seating Capcity")
    {
        sortBySeat(ui);
    }
}

void ViewingPage::sortByTeam(Ui::ViewingPage* ui)
{

}

void ViewingPage::sortByStadiumName(Ui::ViewingPage* ui) { }

void ViewingPage::sortBySeat(Ui::ViewingPage* ui) { }

void ViewingPage::sortByLeague(Ui::ViewingPage* ui, string league) { }

void ViewingPage::sortByTypology(Ui::ViewingPage* ui) { }

void ViewingPage::showOpenRoof(Ui::ViewingPage* ui) { }

void ViewingPage::sortByDate(Ui::ViewingPage* ui) { }

void ViewingPage::showGreatestDTC(Ui::ViewingPage* ui) { }

void ViewingPage::showSmallestDTC(Ui::ViewingPage* ui) { }

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

