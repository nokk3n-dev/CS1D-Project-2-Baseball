#ifndef STADIUMTRIPPAGE_H
#define STADIUMTRIPPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "team.h"
#include <QSqlQuery>
#include "teamList.h"
#include "global.h"

namespace Ui {
class StadiumTripPage;
}

class StadiumTripPage : public QDialog
{
    Q_OBJECT

public:
    explicit StadiumTripPage(TeamList<Team> TripList, QWidget *parent = nullptr);
    ~StadiumTripPage();
    void setTrip(const QString tripType);
private slots:
    void on_Next_Button_clicked();

    //void on_ListStadiumShop_activated(const QModelIndex &index);

    void on_ButtonPurchase_clicked();

private:

    //Souvenir
    QString currentStadium;
    //QVector<Souvenir> cart;
    double total = 0.00;
    int row;

    Ui::StadiumTripPage *ui;
    TeamList<Team> TeamList;
    string lastLocName;
    int totalDistance;
};

#endif // STADIUMTRIPPAGE_H
