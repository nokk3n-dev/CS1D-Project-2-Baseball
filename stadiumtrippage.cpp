#include "stadiumtrippage.h"
#include "ui_stadiumtrippage.h"

StadiumTripPage::StadiumTripPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StadiumTripPage)
{
    ui->setupUi(this);
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
