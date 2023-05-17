#ifndef DIJK_H
#define DIJK_H

#include <QDialog>
#include <QMessageBox>
#include "dbhandler.h"
#include <QSqlQuery>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iterator>
#include <unordered_map>



namespace Ui {
class dijk;
}

class dijk : public QDialog
{
    Q_OBJECT

public:

    explicit dijk(QWidget *parent = nullptr);
    ~dijk();
    void createMap();
    int calcDistance(const string& teamOne, const string& teamTwo);
    int distCalc(const vector<string>& teams);
private slots:

private:
    Ui::dijk *ui;


};

#endif // DIJK_H
