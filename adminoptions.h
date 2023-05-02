#ifndef ADMINOPTIONS_H
#define ADMINOPTIONS_H

#include <QDialog>
#include <QMessageBox>
#include "dbhandler.h"
#include "team.h"
#include <QSqlQuery>

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

private slots:
    void on_adminHomeButton_clicked();

private:
    Ui::AdminOptions *ui;
};

#endif // ADMINOPTIONS_H
