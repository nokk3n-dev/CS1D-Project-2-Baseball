#ifndef VIEWINGPAGE_H
#define VIEWINGPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "dbhandler.h"
#include "team.h"
#include <QSqlQuery>

namespace Ui {
class ViewingPage;
}

class ViewingPage : public QDialog
{
    Q_OBJECT

public:
    explicit ViewingPage(QWidget *parent = nullptr);
    ~ViewingPage();
    void showStadiums(Ui::ViewingPage* ui);

private slots:
    void on_sortBox_currentTextChanged(const QString &arg1);

private:
    Ui::ViewingPage *ui;
};

#endif // VIEWINGPAGE_H
