#ifndef KRUSKAL_H
#define KRUSKAL_H

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
class kruskal;
}

class kruskal : public QDialog
{
    Q_OBJECT

public:
    struct Edge {
        int source;
        int destination;
        int weight;
    };
    explicit kruskal(QWidget *parent = nullptr);
    ~kruskal();
    void createMap();
    void kruskalAlgo();
    void showData(Ui::kruskal* ui);
    void initEdges(vector<Edge>& edges);




private:
    Ui::kruskal *ui;
};

#endif // KRUSKAL_H
