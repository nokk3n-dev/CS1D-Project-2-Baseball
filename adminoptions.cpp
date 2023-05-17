#include "adminoptions.h"
#include "ui_adminoptions.h"


AdminOptions::AdminOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOptions)
{
    ui->setupUi(this);
    ui->Stack->setCurrentWidget(ui->AdminHome);

    // Get data from database
    extern Map mainSouv;

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

                            mainSouv.insert(stadiumName);
                        }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }

    showStadiums(ui);
}

AdminOptions::~AdminOptions()
{
    ui->Stack->setCurrentWidget(ui->AdminHome);
}


void AdminOptions::showStadiums(Ui::AdminOptions* ui)
{
    // Row and Column variables
    int row = 0;
    int column = 0;

    // Set the number of columns and rows
    ui->stadiumDisplayWidget->setColumnCount(10);
    ui->stadiumDisplayWidget->setRowCount(35);

    // Set the names of the columns
    QStringList labels = { "Team Name","Stadium Name", "Seat Capacity", "Location", "Playing Surface", "League",
                           "Date Opened", "Distance to Center Field", "Ballpark Typology", "Roof Type"};
    ui->stadiumDisplayWidget->setHorizontalHeaderLabels(labels);

    // Create current node for iteration
    TeamNode<Team> *currentNode = teamList.getHead();
    while(currentNode != nullptr)
    {
        // Get all the data from the node
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getName())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getStadium())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getCapacity())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getLocation())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getSurface())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getLeague())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getDate())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::number(currentNode->data.getDTC())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getTypology())));
        ui->stadiumDisplayWidget->setItem(row,column++,new QTableWidgetItem(QString::fromStdString(currentNode->data.getRoof())));

        // Move to next node
        currentNode = currentNode->next;
        column = 0;
        row++;
    }

    delete currentNode;
}

bool AdminOptions::checkNum(string num){
    bool check = false;

    for(int i = 0; i < num.length(); i++){

        if(num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3'
                && num[i] != '4' && num[i] != '5'
                && num[i] != '6' && num[i] != '7'
                && num[i] != '8' && num[i] != '9' && num[i] != '.')
        {
            check = true;
            break;
        }
    }
    return check;
}

void AdminOptions::on_adminHomeButton_clicked()
{
    this->close();
}


void AdminOptions::on_adminAddStad_clicked()
{
    string startStad;
    string endStad;
    double numDist;

    string teamName;
    int capacity;
    string location;
    string surface;
    string league;
    int date;
    int center;
    string typology;
    string roofType;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Distance File"),"/Desktop", tr("Txt Files (*.txt)"));
    QFile file(fileName);

    std::ifstream inFile;
    inFile.open(fileName.toStdString());

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,QObject::tr("System Message"),tr("File is invalid! Cannot be found."),QMessageBox::Ok);
        return;
    }
    else
    {
         while(inFile) {
            getline(inFile, startStad);
            getline(inFile, endStad);
            inFile >> numDist;
            inFile.ignore(10000,'\n');

            QString start_stad = QString::fromStdString(startStad);
            QString end_stad = QString::fromStdString(endStad);

            QSqlQuery query;
            query.prepare("INSERT INTO Distance(Start_Stadium, End_Stadium, Distance)"
                          " VALUES (:start_stad, :end_stad, :addDist)");
            query.bindValue(":start_stad", start_stad);
            query.bindValue(":end_stad", end_stad);
            query.bindValue(":addDist", numDist);

            if(query.exec())
            {
                qDebug() << "Query executed";
            }
            else
            {
                qDebug() << "Query UNABLE to execute!";
                QMessageBox::information(this,QObject::tr("System Message"),tr("Failure to input the desired stadium, already included."),QMessageBox::Ok);
                break;
            }
        }

        inFile.close();
        file.close();

         QMessageBox::information(this,QObject::tr("System Message"),tr("Stadium Distances Added, now add Information"),QMessageBox::Ok);

         fileName = QFileDialog::getOpenFileName(this, tr("Open Info File"),"/Desktop", tr("Txt Files (*.txt)"));

         qDebug() << fileName;
         std::ifstream twoFile;

         twoFile.open(fileName.toStdString());

         if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             QMessageBox::information(this,QObject::tr("System Message"),tr("File is invalid! Cannot be found."),QMessageBox::Ok);
             return;
         }
         else
         {
              while(twoFile) {
                 getline(twoFile, teamName);
                 getline(twoFile, startStad);
                 twoFile >> capacity;
                 twoFile.ignore(10000,'\n');
                 getline(twoFile, location);
                 getline(twoFile, surface);
                 getline(twoFile, league);
                 twoFile >> date;
                 twoFile.ignore(10000,'\n');
                 twoFile >> center;
                 twoFile.ignore(10000,'\n');
                 getline(twoFile, typology);
                 getline(twoFile, roofType);


                 /*
                 QString team = QString::fromStdString(teamName);
                 QString stadName = QString::fromStdString(startStad);
                 QString loc = QString::fromStdString(location);
                 QString sur = QString::fromStdString(surface);
                 QString lea = QString::fromStdString(league);
                 QString typo = QString::fromStdString(typology);
                 */

                 QSqlQuery query;
                 qDebug() << date << center << QString::fromStdString(typology);
                 query.prepare("INSERT INTO MLB_Information(Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League, Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type)"
                               " VALUES                    (:teamName, :stadiumName, :seatCapacity, :location, :playingSurface, :league, :dateOpen, :distanceToCenter, :ballParkTypology, :roofType)");
                 query.bindValue(":teamName", QString::fromStdString(teamName));
                 query.bindValue(":stadiumName", QString::fromStdString(startStad));
                 query.bindValue(":seatCapacity", QString::number(capacity));
                 query.bindValue(":location", QString::fromStdString(location));
                 query.bindValue(":playingSurface", QString::fromStdString(surface));
                 query.bindValue(":league", QString::fromStdString(league));
                 query.bindValue(":dateOpen", QString::number(date));
                 query.bindValue(":distanceToCenter", QString::number(center));
                 query.bindValue(":ballParkTypology", QString::fromStdString(typology));
                 query.bindValue(":roofType", QString::fromStdString(roofType));

                 if(query.exec())
                 {
                     qDebug() << "Query executed";
                     break;
                 }
                 else
                 {
                     qDebug() << "Query UNABLE to execute!";
                     QMessageBox::information(this,QObject::tr("System Message"),tr("Failure to input the desired stadium, already included."),QMessageBox::Ok);
                     break;
                 }
             }
             QMessageBox::information(this,QObject::tr("System Message"),tr("Stadium Information Added"),QMessageBox::Ok);
             twoFile.close();
         }
    }
}


void AdminOptions::on_adminAddSouv_clicked()
{
    extern Map mainSouv;
    ui->Stack->setCurrentWidget(ui->AddSouv);

    //For the Combo Box
    for (int iter = 0; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->addSouvStadiumComboBox->addItem(tempText);
    }

}


void AdminOptions::on_adminChaSouv_clicked()
{
    extern Map mainSouv;

    ui->Stack->setCurrentWidget(ui->ChangeSouvPrice);

    //For the Combo Box
    for (int iter = 0; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->changeSouvStadiumComboBox->addItem(tempText);
    }

}


void AdminOptions::on_adminDelSouv_clicked()
{

    extern Map mainSouv;
    //For the Combo Box
    for (int iter = 0; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->removeSouvStadiumComboBox->addItem(tempText);
    }

    ui->Stack->setCurrentWidget(ui->DeleteSouv);

}


void AdminOptions::on_AcceptDelete_clicked()
{
    QString stadName;
    QString souvName;
    int cycle;

    stadName = ui->removeSouvStadiumComboBox->currentText();
    souvName = ui->textDeleteSouvName->text();

    QVector<Souvenir>::iterator iter = mainSouv.find(stadName.QString::toStdString());

    for(cycle = 0; cycle < iter->getSize(); cycle++){
        if(souvName.QString::toStdString() == iter->getItem(cycle)){
            iter->removeItem(cycle);
            QMessageBox::information(this,QObject::tr("System Message"),tr("Item Removed"),QMessageBox::Ok);
            break;
        }
    }

    if(cycle == iter->getSize()){
        QMessageBox::information(this,QObject::tr("System Message"),tr("Failed to Find Item"),QMessageBox::Ok);
    }

}


void AdminOptions::on_AcceptAddSouv_clicked()
{
    QString stadName;
    QString souvName;
    QString souvPrice;
    bool valid = false;

    stadName = ui->addSouvStadiumComboBox->currentText();
    souvName = ui->textNewSouvName->text();
    souvPrice = ui->textNewSouvPrice->text();

    valid = checkNum(souvPrice.toStdString());

    if(valid == false){
        QVector<Souvenir>::iterator iter = mainSouv.find(stadName.QString::toStdString());



        iter->insertItem(souvName.QString::toStdString(), souvPrice.toDouble());

        QMessageBox::information(this,QObject::tr("System Message"),tr("Item Added"),QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this,QObject::tr("System Message"),tr("Please Write a Valid Price"),QMessageBox::Ok);
    }

}


void AdminOptions::on_AcceptChangePrice_clicked()
{
    QString stadName;
    QString souvName;
    QString souvPrice;
    bool found = false;
    bool valid = false;
    int cycle;

    stadName = ui->changeSouvStadiumComboBox->currentText();
    souvName = ui->textChangeName->text();
    souvPrice = ui->textChangePrice->text();

    valid = checkNum(souvPrice.toStdString());

    if(valid == false){

        QVector<Souvenir>::iterator iter = mainSouv.find(stadName.QString::toStdString());

        for(cycle = 0; cycle < iter->getSize(); cycle++){
            if(souvName.QString::toStdString() == iter->getItem(cycle)){
                iter->changePrice(souvPrice.toDouble(), cycle);
                found = true;
                QMessageBox::information(this,QObject::tr("System Message"),tr("Price Changed"),QMessageBox::Ok);
                break;
            }
        }
        //If Item isn't Found
        if(found == false){
            QMessageBox::information(this,QObject::tr("System Message"),tr("Failed to find item"),QMessageBox::Ok);
        }
    }
    //If price isn't valid
    else{
        QMessageBox::information(this,QObject::tr("System Message"),tr("Please Write a Valid Price"),QMessageBox::Ok);
    }
}


void AdminOptions::on_adminChaStad_clicked()
{
    extern Map mainSouv;
    ui->Stack->setCurrentWidget(ui->ChangeStad);

    //For the Combo Box
    TeamNode<Team>* currentNode = teamList.getHead();
    while (currentNode!=nullptr){
        ui->changeStadComboBox->addItem(QString::fromStdString(currentNode->data.getStadium()));
        currentNode = currentNode->next;
    }
}


void AdminOptions::on_Confirm_Button_clicked()
{
    if (ui->textChaStadName->text().isEmpty() || ui->textChaCapacity->text().isEmpty() ||
            ui->textChaCenter->text().isEmpty() || ui->textChaDate->text().isEmpty() ||
            ui->textChaLeague->text().isEmpty() || ui->textChaLocation->text().isEmpty() ||
            ui->textChaRoof->text().isEmpty() || ui->textChaSurface->text().isEmpty() ||
            ui->textChaTypology->text().isEmpty())
        {
            QMessageBox::information(this, tr("System Message"), tr("Please fill in all the fields."), QMessageBox::Ok);
            return;
        }
    // Set the text from line edits to the same data type as the variables
    string newStadiumName = ui->textChaStadName->text().toStdString();
    int newStadiumCapacity = ui->textChaCapacity->text().toInt();
    int newStadiumCenter = ui->textChaCenter->text().toInt();
    string newStadiumDate = ui->textChaDate->text().toStdString();
    string newStadiumLeague = ui->textChaLeague->text().toStdString();
    string newStadiumLocation = ui->textChaLocation->text().toStdString();
    string newStadiumRoof = ui->textChaRoof->text().toStdString();
    string newStadiumSurface = ui->textChaSurface->text().toStdString();
    string newStadiumTypology = ui->textChaTypology->text().toStdString();

    string stadiumToChange = ui->changeStadComboBox->currentText().toStdString();

    // Update the database with the new information
    QSqlQuery query;
    query.prepare("UPDATE MLB_Information SET Stadium_Name = :stadiumName, Seat_Capacity = :seatCapacity, "
                  "Location = :location, Playing_Surface = :playingSurface, League = :league, Date_Opened = :dateOpened, "
                  "Distance_to_Center_Field = :distanceToCenter, Ballpark_Typology = :ballparkTypology, Roof_Type = :roofType "
                  "WHERE Stadium_Name = :stadiumToChange");

    // Bind the values to the query
    query.bindValue(":stadiumName", QString::fromStdString(newStadiumName));
    query.bindValue(":seatCapacity", QString::number(newStadiumCapacity));
    query.bindValue(":location", QString::fromStdString(newStadiumLocation));
    query.bindValue(":playingSurface", QString::fromStdString(newStadiumSurface));
    query.bindValue(":league", QString::fromStdString(newStadiumLeague));
    query.bindValue(":dateOpened", QString::fromStdString(newStadiumDate));
    query.bindValue(":distanceToCenter", QString::number(newStadiumCenter));
    query.bindValue(":ballparkTypology", QString::fromStdString(newStadiumTypology));
    query.bindValue(":roofType", QString::fromStdString(newStadiumRoof));
    query.bindValue(":stadiumToChange", QString::fromStdString(stadiumToChange));

    if (query.exec())
    {
        QMessageBox::information(this, tr("System Message"), tr("Stadium information updated."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("System Message"), tr("Failed to update stadium information."), QMessageBox::Ok);
    }
}





