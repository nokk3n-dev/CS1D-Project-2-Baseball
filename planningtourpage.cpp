#include "planningtourpage.h"
#include "ui_planningtourpage.h"
#include "planningtourpage.h"
#include "prims.h"
#include "kruskal.h"

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
    
void planningTourPage::on_kruskal_clicked()
{

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
