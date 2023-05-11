#include "customtrippage.h"
#include "qtablewidget.h"
#include "ui_customtrippage.h"
#include "dbhandler.h"
#include <QWidget>
CustomTripPage::CustomTripPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTripPage)
{
    ui->setupUi(this);
    QMessageBox msgBox;
    TeamList<Team> initialList;
    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query1("SELECT Team_Name, Stadium_Name, Seat_Capacity, Location, Playing_Surface, League,"
                         "Date_Opened, Distance_to_Center_Field, Ballpark_Typology, Roof_Type FROM MLB_Information ORDER BY TEAM_NAME");

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

            if (teamName != "")
            {
                // Create Team Object
                Team t(teamName, stadiumName, seatCapacity, location, playingSurface, league, dateOpened, distanceToCenter, ballparkTypology, roofType);
                initialList.insert(t);
            }
        }

    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
        dbHandler.close();
    }
    TeamNode<Team> *currentNode = initialList.getHead();
    while(currentNode != nullptr)
    {
        ui->StartingLoc_Dropdown->addItem(QString::fromStdString(currentNode->data.getName()));
        ui->Stadium_Dropdown->addItem(QString::fromStdString(currentNode->data.getName()));
        currentNode = currentNode->next;
    }

    delete currentNode;
}

CustomTripPage::~CustomTripPage()
{
    delete ui;
}

void CustomTripPage::on_Add_Button_clicked()
{
    QString teamToAdd = ui->Stadium_Dropdown->currentText();
    QString startingLoc = ui->StartingLoc_Dropdown->currentText();

    QList<QListWidgetItem *> existingItems = ui->listWidget->findItems(teamToAdd, Qt::MatchExactly);
    if (existingItems.isEmpty()) {
        ui->listWidget->addItem(teamToAdd);
    }

    QListWidgetItem *firstItem = ui->listWidget->item(0);
    if (firstItem && firstItem->text() == startingLoc) {
        delete ui->listWidget->takeItem(0);
    }
}


void CustomTripPage::on_Trip_Button_clicked()
{

}
