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
    void kruskalAlgo();
    int minimumDist(int dist[], bool visited[]);
    void showData(Ui:: dijk* ui);
    void pathing(vector<int>& parent, int j);
    void dijkstra(int graph[50][50], int start, int target);

private:
    Ui::dijk *ui;


};

#endif // DIJK_H
