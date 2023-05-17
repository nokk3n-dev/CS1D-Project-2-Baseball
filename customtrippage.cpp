#include "customtrippage.h"
#include "stadiumtrippage.h"
#include "ui_customtrippage.h"
#include "dijk.h"
#include "dbhandler.h"
#include <QWidget>
CustomTripPage::CustomTripPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTripPage)
{
    ui->setupUi(this);
    QMessageBox msgBox;
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
                TeamList.insert(t);
            }
        }

    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
        dbHandler.close();
    }
    TeamNode<Team> *currentNode = TeamList.getHead();
    while(currentNode != nullptr)
    {
        ui->StartingLoc_Dropdown->addItem(QString::fromStdString(currentNode->data.getName()));
        ui->Stadium_Dropdown->addItem(QString::fromStdString(currentNode->data.getName()));
        currentNode = currentNode->next;
    }

    delete currentNode;
}

CustomTripPage::~CustomTripPage()
{
    delete ui;
}

void CustomTripPage::on_Add_Button_clicked()
{
    QString teamToAdd = ui->Stadium_Dropdown->currentText();
    QString startingLoc = ui->StartingLoc_Dropdown->currentText();

    QList<QListWidgetItem *> existingItems = ui->listWidget->findItems(teamToAdd, Qt::MatchExactly);
    if (existingItems.isEmpty()) {
        ui->listWidget->addItem(teamToAdd);
        TeamNode<Team> *currentNode = TeamList.getHead();
        while(currentNode != nullptr)
        {
            if (currentNode->data.getName()==teamToAdd.toStdString()){
                TripList.insert(currentNode->data);
            }
            currentNode = currentNode->next;
        }
        delete currentNode;
    }

    QListWidgetItem *firstItem = ui->listWidget->item(0);
    if (firstItem && firstItem->text() == startingLoc) {
        delete ui->listWidget->takeItem(0);
        TeamNode<Team> *currentNode = TeamList.getHead();
        while(currentNode != nullptr)
        {
            if (currentNode->data.getName()==teamToAdd.toStdString()){
                TripList.remove(currentNode->data);
            }
            currentNode = currentNode->next;
        }
        delete currentNode;
    }
}


void CustomTripPage::on_Trip_Button_clicked()
{
    TeamNode<Team> *startingLocNode = TeamList.getHead();
    while(startingLocNode != nullptr && startingLocNode->data.getName()!=ui->StartingLoc_Dropdown->currentText().toStdString())
    {
        startingLocNode = startingLocNode->next;
    }
    TripList.insertFront(startingLocNode->data);
    delete startingLocNode;
    StadiumTripPage TripPage(TripList, this);
    this->close();
    TripPage.setModal(true);
    TripPage.exec();
}



void CustomTripPage::on_Add_All_Button_clicked()
{
    QString startingLoc = ui->StartingLoc_Dropdown->currentText();
    ui->listWidget->clear();
    TeamNode<Team>* delNode = TripList.getHead();
    while (delNode != nullptr) {
        TeamNode<Team>* nextNode = delNode->next;
        delete delNode;
        delNode = nextNode;
    }
    TripList.setHead(nullptr);

    for (int i = 0; i < ui->Stadium_Dropdown->count(); i++) {
        QString teamToAdd = ui->Stadium_Dropdown->itemText(i);

        if (teamToAdd != startingLoc) {
            QList<QListWidgetItem *> existingItems = ui->listWidget->findItems(teamToAdd, Qt::MatchExactly);
            if (existingItems.isEmpty()) {
                ui->listWidget->addItem(teamToAdd);
                TeamNode<Team> *currentNode = TeamList.getHead();
                while (currentNode != nullptr) {
                    if (currentNode->data.getName() == teamToAdd.toStdString()) {
                        TripList.insert(currentNode->data);
                        break;
                    }
                    currentNode = currentNode->next;
                }
            }
        }
    }
}



void CustomTripPage::on_Sort_Button_clicked()
{
    dijk shortestPath;
    vector<string> sp;
    ::TeamList<Team> currentTrip;

    // Initializing current trip vector to store names of stadiums actually in the trip
    TeamNode<Team>* currentNode = TeamList.getHead();
    vector<string> currentStadiums;
    while (currentNode != nullptr) {
        currentTrip.insert(currentNode->data);
        currentStadiums.push_back(currentNode->data.getStadium());
        currentNode = currentNode->next;
    }

    currentNode = currentTrip.getHead();
    while (currentNode != nullptr) {
        if (currentNode->data.getName() == ui->StartingLoc_Dropdown->currentText().toStdString()) {
            sp = shortestPath.getStadiumsInOrder(currentNode->data.getStadium(), currentStadiums);
        }
        currentNode = currentNode->next;
    }

    // Clear the TeamList linked list object
    currentNode = TeamList.getHead();
    while (currentNode != nullptr) {
        TeamNode<Team>* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    TeamList.setHead(nullptr);

    currentNode = TripList.getHead();
    while (currentNode != nullptr) {
        TeamNode<Team>* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    TripList.setHead(nullptr);

    // Insert the stadiums in the order designated by the shortest path algorithm into the teamlist
    for (unsigned long long i = 0; i < sp.size(); i++) {
        string stadium = sp.at(i); // Stadium to add
        currentNode = currentTrip.getHead();
        while (currentNode != nullptr) {
            // Go through vector<string> sp and insert stadiums into TeamList based on the order of stadiums in sp.
            if (currentNode->data.getStadium() == stadium && stadium != ui->StartingLoc_Dropdown->currentText().toStdString()) {
                TeamList.insert(currentNode->data);
                TripList.insert(currentNode->data);
            }
            currentNode = currentNode->next;
        }
    }

    // Clear the list widget of all its contents
    ui->listWidget->clear();

    // Add the items from the sp vector to the list widget
    for (unsigned long long i = 0; i < sp.size(); i++) {
        if (sp.at(i) != ui->StartingLoc_Dropdown->currentText().toStdString()) {
            ui->listWidget->addItem(QString::fromStdString(sp.at(i)));
        }
    }
}





