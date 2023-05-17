#include "stadiumtrippage.h"
#include "ui_stadiumtrippage.h"
#include "dijk.h"
StadiumTripPage::StadiumTripPage(::TeamList<Team> TripList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StadiumTripPage)
{
    extern Map mainSouv;
    dijk dijkObj;
    QStringList title = {"Price", "Item"};
    QStringList cartTitle = {"Stadium", "Price", "Item", "Quantity"};

    ui->setupUi(this);

    //Ui Width
    int uiWidth = 70;

    //Shop
    ui->TableShop->setColumnCount(2);
    ui->TableShop->setHorizontalHeaderLabels(title);
    ui->TableShop->setRowCount(16);

    ui->TableShop->setColumnWidth(0, uiWidth+50);
    ui->TableShop->setColumnWidth(1, uiWidth+50);

    //Cart
    ui->TableCart->setColumnCount(4);
    ui->TableCart->setHorizontalHeaderLabels(cartTitle);
    ui->TableCart->setRowCount(150);

    ui->TableCart->setColumnWidth(0, uiWidth);
    ui->TableCart->setColumnWidth(1, uiWidth);
    ui->TableCart->setColumnWidth(2, uiWidth);


    row = 0;
    total = 0;

    TeamNode<Team> *currentNode = TripList.getHead();
    ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
    ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
    ui->DistanceText->setText("Distance from home stadium: 0");
    totalDistance = 0;


    QVector<Souvenir>::Iterator iter = mainSouv.find(currentNode->data.getStadium());
    currentStadium = QString::fromStdString(currentNode->data.getStadium());


    for(int i = 0; i < iter->getSize(); i++){
        QString testing = QString::fromStdString(iter->getItem(i));

        //qDebug() << testing << iter->getPrice(i);
        ui->TableShop->setItem(i,0,new QTableWidgetItem(QString::number(iter->getPrice(i))));
        ui->TableShop->setItem(i,1,new QTableWidgetItem(testing));

        ui->SouvenirComboBox->addItem(testing);
    }

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
    extern Map mainSouv;
    dijk dijkObj;

    ui->TableShop->clearContents();
    ui->SouvenirComboBox->clear();

    if (TeamList.getHead()!=nullptr){
        TeamNode<Team> *currentNode = TeamList.getHead();
        ui->StadiumText->setText(QString::fromStdString(currentNode->data.getStadium()));
        ui->WelcomeText->setText(QString::fromStdString("Welcome to the Home of the "+currentNode->data.getName()+"!"));
        totalDistance += dijkObj.calcDistance(lastLocName, currentNode->data.getStadium());
        ui->DistanceText->setText("Distance from home stadium: " + QString::number(totalDistance));
        lastLocName = currentNode->data.getStadium();

        QVector<Souvenir>::Iterator iter = mainSouv.find(currentNode->data.getStadium());
        currentStadium = QString::fromStdString(currentNode->data.getStadium());

        for(int i = 0; i < iter->getSize(); i++){
            QString testing = QString::fromStdString(iter->getItem(i));

            //qDebug() << testing << iter->getPrice(i);
            ui->TableShop->setItem(i,0,new QTableWidgetItem(QString::number(iter->getPrice(i))));
            ui->TableShop->setItem(i,1,new QTableWidgetItem(testing));

            ui->SouvenirComboBox->addItem(testing);
        }


        TeamList.remove(TeamList.getHead()->data);


    } else {
        ui->StadiumText->setText(QString::fromStdString("Congratulations!"));
        ui->WelcomeText->setText(QString::fromStdString("The trip is over!"));
    }
}



void StadiumTripPage::on_ButtonPurchase_clicked()
{
    Souvenir temp;
    QVector<Souvenir>::Iterator iter = mainSouv.find(currentStadium.toStdString());

    QString souvName;
    double souvPrice = 0;
    int quantity = 0;
    bool found = false;

    souvName = ui->SouvenirComboBox->currentText();
    quantity = ui->SouvenirQuantity->cleanText().toInt();

    if(quantity > 0){
        for(int i = 0; i < iter->getSize(); i++){
            if(iter->getItem(i) == souvName.toStdString()){
                souvPrice = iter->getPrice(i);
                found = true;
                break;
            }
        }
        if(found == true){
           // temp.insertCartItem(souvName.toStdString(),souvPrice,quantity);
            total += (quantity * souvPrice);

            //Stadium, Price, Item, Quantity
            ui->TableCart->setItem(row,0,new QTableWidgetItem(currentStadium));
            ui->TableCart->setItem(row,1,new QTableWidgetItem(QString::number(souvPrice)));
            ui->TableCart->setItem(row,2,new QTableWidgetItem(souvName));
            ui->TableCart->setItem(row,3,new QTableWidgetItem(ui->SouvenirQuantity->cleanText()));

            row++;

            ui->labelTotal->setText(QString::number(total));
        }
        //If it ain't found, error msg
        else{
            QMessageBox::information(this,QObject::tr("System Message"),tr("Item Not Found."),QMessageBox::Ok);
        }
    }
    else{
        QMessageBox::information(this,QObject::tr("System Message"),tr("Please Enter a value above 0."),QMessageBox::Ok);
    }
}

