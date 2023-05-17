#ifndef PRIMS_H
#define PRIMS_H

#include <QDialog>
#include <QMessageBox>
#include "dbhandler.h"
#include <QSqlQuery>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace Ui {
class prims;
}

class prims : public QDialog
{
    Q_OBJECT

public:
    struct Edge {
        int source;
        int destination;
        int weight;
    };

    explicit prims(QWidget *parent = nullptr);
    ~prims();
    void createMap();
    void primsAlgo();
    void showData(Ui::prims* ui);
    void primsAlgo(int graph[50][50]);


private:
    Ui::prims *ui;
};

#endif // PRIMS_H
