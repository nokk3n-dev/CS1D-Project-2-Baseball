#include "planningtourpage.h"
#include "ui_planningtourpage.h"
#include "planningtourpage.h"
#include "prims.h"
#include "kruskal.h"
#include "stadiumtrippage.h"
#include "customtrippage.h"
planningTourPage::planningTourPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::planningTourPage)
{
    ui->setupUi(this);
}

planningTourPage::~planningTourPage()
{
    delete ui;
}

void planningTourPage::on_kruskal_clicked()
{
    kruskal go;
    go.setModal(true);
    go.exec();
}

void planningTourPage::on_prims_clicked()
{
    prims go;
    go.setModal(true);
    go.exec();


}

void planningTourPage::on_shortest_path_clicked()
{

}

void planningTourPage::on_Trip_Button_clicked()
{
    if(this->ui->Trip_Selection->currentText()==QString::fromStdString("Dodger Stadium Dijkstra Trip")){
        //Option 1: Start at Dodger Stadium & visit any other stadium of the user's choice. Use Dijkstra or A* algorithm to determine shortest path
//        StadiumTripPage tripPage;
//        tripPage.setModal(true);
//        tripPage.exec();
//        tripPage.setTrip(this->ui->Trip_Selection->currentText());
    } else if (this->ui->Trip_Selection->currentText()=="Custom Trip"){
        //Option 2: Plan a custom trip with a designated order of visiting each stadium
        CustomTripPage tripPage;
        tripPage.setModal(true);
        tripPage.exec();
    }else if (this->ui->Trip_Selection->currentText()==QString::fromStdString("Miami Marlins Circuit Trip")){
//        StadiumTripPage tripPage;
//        tripPage.setModal(true);
//        tripPage.exec();
//        tripPage.setTrip(this->ui->Trip_Selection->currentText());
        //Option 3: Start at the Miami Marlins stadium and visit all other stadiums while traveling the shortest distance
    }else if (this->ui->Trip_Selection->currentText()=="Efficient Trip"){
        //Option 4: Recursively iterate through each stadium chosen by the user, starting at the user's starting location
        CustomTripPage tripPage;
        tripPage.setModal(true);
        tripPage.exec();
    }
}


void planningTourPage::on_dfs_clicked()
{

}


void planningTourPage::on_bfs_clicked()
{

}

