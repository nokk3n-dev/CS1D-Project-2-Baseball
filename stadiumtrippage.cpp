#include "stadiumtrippage.h"
#include "ui_stadiumtrippage.h"
#include "dijk.h"
StadiumTripPage::StadiumTripPage(::TeamList<Team> TripList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StadiumTripPage)
{
    dijk dijkObj;
    ui->setupUi(this);
    TeamNode<Team> *currentNode = TripList.getHead();
    ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
    ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
    ui->DistanceText->setText("Distance from home stadium: 0");
    totalDistance = 0;
    while(currentNode != nullptr)
    {
        TeamList.insert(currentNode->data);
        currentNode = currentNode->next;
    }
    delete currentNode;
    lastLocName = TeamList.getHead()->data.getStadium();
    TeamList.remove(TeamList.getHead()->data);
}

StadiumTripPage::~StadiumTripPage()
{
    delete ui;
}

void setTrip(const QString tripType){
    if(tripType == QString::fromStdString("Dodger Stadium Dijkstra Trip")){

    } else if (tripType == QString::fromStdString("Miami Marlins Circuit Trip")){

    }
}

void StadiumTripPage::on_Next_Button_clicked()
{
    dijk dijkObj;
    if (TeamList.getHead()!=nullptr){
        TeamNode<Team> *currentNode = TeamList.getHead();
        ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
        ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
        totalDistance += dijkObj.calcDistance(lastLocName, currentNode->data.getStadium());
        ui->DistanceText->setText("Distance from home stadium: " + QString::number(totalDistance));
        lastLocName = currentNode->data.getStadium();
        TeamList.remove(TeamList.getHead()->data);
    } else {
        ui->StadiumText->setText(QString::fromStdString("Congratulations!"));
        ui->WelcomeText->setText(QString::fromStdString("The trip is over!"));
    }
}


