#include "adminoptions.h"
#include "ui_adminoptions.h"


AdminOptions::AdminOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOptions)
{
    ui->setupUi(this);
    ui->Stack->setCurrentWidget(ui->AdminHome);

    // Get data from database
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
    delete ui;
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

void AdminOptions::on_adminHomeButton_clicked()
{
    this->close();
}


void AdminOptions::on_adminAddStad_clicked()
{
    std::string startStad;
    std::string endStad;
    double numDist;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/Desktop", tr("Txt Files (*.txt)"));     /// user picks the txt file to choose from
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

         QMessageBox::information(this,QObject::tr("System Message"),tr("Stadium Added"),QMessageBox::Ok);
    }
}


void AdminOptions::on_adminAddSouv_clicked()
{

    ui->Stack->setCurrentWidget(ui->AddSouv);

    //For the Combo Box
    for (int iter; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->addSouvStadiumComboBox->addItem(tempText);
    }


}


void AdminOptions::on_adminChaStad_clicked()
{
    ui->Stack->setCurrentWidget(ui->ChangeSouvPrice);

    //For the Combo Box
    for (int iter; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->changeSouvStadiumComboBox->addItem(tempText);
    }
}


void AdminOptions::on_adminDelSouv_clicked()
{
    //For the Combo Box
    for (int iter; iter < mainSouv.souvMap.size(); iter++){

        QString tempText = QString::fromStdString(mainSouv[iter].getStadium());
        ui->removeSouvStadiumComboBox->addItem(tempText);
    }

    ui->Stack->setCurrentWidget(ui->DeleteSouv);
}


void AdminOptions::on_AcceptDelete_clicked()
{
    QString stadName;
    QString souvName;

    stadName = ui->removeSouvStadiumComboBox->currentText();
    souvName = ui->textDeleteSouvName->text();


}

