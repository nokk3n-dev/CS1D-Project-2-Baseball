#include "dfsbfspage.h"
#include "ui_dfsbfspage.h"

DfsBfsPage::DfsBfsPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DfsBfsPage)
{
    ui->setupUi(this);
}

DfsBfsPage::~DfsBfsPage()
{
    delete ui;
}
