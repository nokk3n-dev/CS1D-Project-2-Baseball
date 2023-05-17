#ifndef ADMINOPTIONS_H
#define ADMINOPTIONS_H

#include <QDialog>
#include <QMessageBox>
#include "dbhandler.h"
#include <QSqlQuery>
#include "team.h"
#include "teamList.h"
#include "global.h"
#include <QFileDialog>
#include <fstream>

namespace Ui {
class AdminOptions;
}

class AdminOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOptions(QWidget *parent = nullptr);
    ~AdminOptions();
    void showStadiums(Ui::AdminOptions* ui);

    bool checkNum(string num);

private slots:

    void on_adminHomeButton_clicked();

    void on_adminAddStad_clicked();

    void on_adminAddSouv_clicked();

    void on_adminChaStad_clicked();

    void on_adminDelSouv_clicked();

    void on_AcceptDelete_clicked();

    void on_AcceptAddSouv_clicked();

    void on_AcceptChangePrice_clicked();

    void on_adminChaSouv_clicked();

    void on_Confirm_Button_clicked();

private:
    Ui::AdminOptions *ui;
    TeamList<Team> teamList;
};

#endif // ADMINOPTIONS_H
