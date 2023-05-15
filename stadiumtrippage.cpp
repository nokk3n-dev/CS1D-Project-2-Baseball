#include "stadiumtrippage.h"
#include "ui_stadiumtrippage.h"

StadiumTripPage::StadiumTripPage(::TeamList<Team> TripList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StadiumTripPage)
{
    ui->setupUi(this);
    TeamNode<Team> *currentNode = TripList.getHead();
    ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
    ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
    while(currentNode != nullptr)
    {
        TeamList.insert(currentNode->data);
        currentNode = currentNode->next;
    }
    delete currentNode;
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
    if (TeamList.getHead()!=nullptr){
        TeamNode<Team> *currentNode = TeamList.getHead();
        ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
        ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
        TeamList.remove(TeamList.getHead()->data);
    } else {
        ui->StadiumText->setText(QString::fromStdString("Congratulations!"));
        ui->WelcomeText->setText(QString::fromStdString("The trip is over!"));
    }
}


