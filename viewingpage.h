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
    void sortByTeam(Ui::ViewingPage* ui);
    void sortByStadiumName(Ui::ViewingPage* ui);
    void sortBySeat(Ui::ViewingPage* ui);
    void sortByLeague(Ui::ViewingPage* ui, string league);
    void sortByTypology(Ui::ViewingPage* ui);
    void showOpenRoof(Ui::ViewingPage* ui);
    void sortByDate(Ui::ViewingPage* ui);
    void showGreatestDTC(Ui::ViewingPage* ui);
    void showSmallestDTC(Ui::ViewingPage* ui);
    TeamList<Team> teamList;

private slots:
    void on_sortBox_currentTextChanged(const QString &arg1);

private:
    Ui::ViewingPage *ui;
};

#endif // VIEWINGPAGE_H
