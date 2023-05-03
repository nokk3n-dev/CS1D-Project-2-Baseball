#include "kruskal.h"
#include "ui_kruskal.h"



const int NUM_TEAMS = 50;
int kruskalGraph[NUM_TEAMS][NUM_TEAMS];
unordered_map<string, int> cityIndices;
unordered_map<int, string> indexToCity;
vector<string> mstTree;
int mstWeight = 0;

kruskal::kruskal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kruskal)
{
    ui->setupUi(this);
    ui->kruskalDisplayWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showData(ui);
}


kruskal::~kruskal()
{
    delete ui;
}


void kruskal::initEdges(vector<Edge>& edges)
{
    for(int i = 0; i < NUM_TEAMS; i++)
    {
        for(int j = i; j < NUM_TEAMS; j++)
        {
            if(kruskalGraph[i][j] != 0)
            {
                Edge e;
                e.source = i;
                e.destination = j;
                e.weight = kruskalGraph[i][j];
                edges.push_back(e);
            }
        }
    }
}


void kruskal::createMap()
{
    QMessageBox msgBox;
    QString team;
    string teamS;
    QString firstTeam;
    QString secondTeam;
    string firstTeamS;
    string secondTeamS;
    int distance = 0;;
    int currentIndex = 0;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        QSqlQuery query("SELECT Stadium_Name FROM MLB_Information");
        QSqlQuery query1("SELECT Start_Stadium, End_Stadium, distance FROM Distance");

        while(query.next())
        {
            team = query.value(0).toString();
            teamS = team.toStdString();
            if (cityIndices.find(teamS) == cityIndices.end())
            {
                cityIndices[teamS] = currentIndex;
                indexToCity[currentIndex] = teamS;
                currentIndex++;

            }

        }





        while(query1.next())
        {
            firstTeam = query1.value(0).toString();
            secondTeam = query1.value(1).toString();
            distance = query1.value(2).toInt();
            firstTeamS = firstTeam.toStdString();
            secondTeamS = secondTeam.toStdString();

            kruskalGraph[cityIndices[firstTeamS]][cityIndices[secondTeamS]] = distance;
            kruskalGraph[cityIndices[secondTeamS]][cityIndices[firstTeamS]] = distance;

        }
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
        dbHandler.close();
    }
}




void kruskal::kruskalAlgo()
{
    vector<Edge> edges;
    initEdges(edges);


    vector<int> parent(NUM_TEAMS);
    for(int i = 0; i < NUM_TEAMS; i++)
    {
        parent[i] = i;
    }

    vector<Edge> mst;
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        int edgesSize = edges.size();
        for (int i = 0; i < edgesSize - 1; i++)
        {
            if (edges[i].weight > edges[i+1].weight)
            {
                swap(edges[i], edges[i+1]);
                sorted = false;
            }
        }
    }
    int edgesSize = edges.size();
    for(int i = 0; i < edgesSize; i++)
    {
        Edge e = edges[i];
        int sourceParent = parent[e.source];
        int destParent = parent[e.destination];
        if(sourceParent != destParent)
        {
            mst.push_back(e);
            for(int j = 0; j < NUM_TEAMS; j++)
            {
                if(parent[j] == destParent)
                {
                    parent[j] = sourceParent;
                }
            }
        }
    }

    int totalWeight = 0;
    int mstSize = mst.size();
    for(int i = 0; i < mstSize; i++)
    {
        totalWeight += mst[i].weight;
    }

    mstWeight = totalWeight;
    for(int i = 0; i < mstSize; i++)
    {
        string path = indexToCity[mst[i].source] + " -> " + indexToCity[mst[i].destination];
        mstTree.push_back(path);
    }


}




void kruskal::showData(Ui::kruskal* ui)
{
    createMap();
    kruskalAlgo();


    QString pathName;



    ui->kruskalDisplayWidget->setColumnCount(2);
    ui->kruskalDisplayWidget->setRowCount(35);
    QStringList labels = { "MST weight", "MST paths"};



    ui->kruskalDisplayWidget->setHorizontalHeaderLabels(labels);

    ui->kruskalDisplayWidget->setItem(0,0,new QTableWidgetItem(QString::number(mstWeight)));
    int row = 0;
    int size = mstTree.size();
    for(int i = 0; i < size; i++)
    {
        string path;
        path = mstTree[i];
        pathName = QString::fromStdString(path);
        ui->kruskalDisplayWidget->setItem(row++,1,new QTableWidgetItem(pathName));

    }


}

