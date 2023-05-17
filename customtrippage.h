#ifndef CUSTOMTRIPPAGE_H
#define CUSTOMTRIPPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "team.h"
#include <QSqlQuery>
#include "teamList.h"
namespace Ui {
class CustomTripPage;
}

class CustomTripPage : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTripPage(QWidget *parent = nullptr);
    ~CustomTripPage();
    void sortByTeam();
private slots:
    void on_Add_Button_clicked();

    void on_Trip_Button_clicked();

    void on_Add_All_Button_clicked();

    void on_Sort_Button_clicked();

private:
    Ui::CustomTripPage *ui;
    TeamList<Team> TripList;
    TeamList<Team> TeamList;
};

#endif // CUSTOMTRIPPAGE_H
