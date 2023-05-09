#ifndef VIEWINGPAGE_H
#define VIEWINGPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "team.h"
#include <QSqlQuery>
#include "teamList.h"

namespace Ui {
class ViewingPage;
}

class ViewingPage : public QDialog
{
    Q_OBJECT

public:
    explicit ViewingPage(QWidget *parent = nullptr);
    ~ViewingPage();
    void showStadiums(Ui::ViewingPage* ui, TeamList<Team> list);
    void sortByTeam();
    void sortByStadiumName();
    void sortBySeat();
    void sortByLeague(string league);
    void sortByTypology();
    void showOpenRoof();
    void sortByDate();
    void showGreatestDTC();
    void showSmallestDTC();

private slots:
    void on_sortBox_currentTextChanged(const QString &arg1);

private:
    Ui::ViewingPage *ui;
};

#endif // VIEWINGPAGE_H
