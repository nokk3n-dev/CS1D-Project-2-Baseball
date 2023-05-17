#include "planningtourpage.h"
#include "ui_planningtourpage.h"
#include "planningtourpage.h"
#include "prims.h"
#include "kruskal.h"
#include "stadiumtrippage.h"
#include "dfsbfspage.h"
#include "customtrippage.h"
planningTourPage::planningTourPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::planningTourPage)
{
    ui->setupUi(this);

    // Set up background
    QPixmap bkgnd("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\dfsbfsPage.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->SelectTripLabel->setStyleSheet("QLabel { background-color : white; }");
    ui->label->setStyleSheet("QLabel { color : white; }");
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
    CustomTripPage tripPage;
    tripPage.setModal(true);
    tripPage.exec();
}


void planningTourPage::on_dfs_clicked()
{
    DfsBfsPage DFSPage;
    DFSPage.setModal(true);
    DFSPage.exec();
}


void planningTourPage::on_bfs_clicked()
{
    DfsBfsPage BFSPage;
    BFSPage.setModal(true);
    BFSPage.exec();
}

