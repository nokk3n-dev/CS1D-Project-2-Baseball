#include "dijk.h"
#include "ui_dijk.h"
const int NUM_TEAMS = 50;
int dijkGraph[NUM_TEAMS][NUM_TEAMS];
map<string, int> dijkCityIndices;
map<int, string> dijkIndexToCity;
const string START = "Dodger Stadium";
vector<int> pathForDijk;
int dijkDistance = 0;

dijk::dijk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dijk)
{
    ui->setupUi(this);
    ui->dijkTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showData(ui);
}

dijk::~dijk()
{
    delete ui;
}


int dijk::minimumDist(int dist[], bool Tset[])
{
    int min = INT_MAX;
    int index = 0;
    for (int i = 0; i < NUM_TEAMS; i++) {
        if (Tset[i] == false && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}


void dijk::createMap()
{
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
            QSqlQuery query("SELECT Start_Stadium, End_Stadium, distance FROM Distance");



            int index = 0;
            while(query.next())
            {
                firstTeam = query.value(0).toString();
                secondTeam = query.value(1).toString();
                distance = query.value(2).toInt();
                firstTeamS = firstTeam.toStdString();
                secondTeamS = secondTeam.toStdString();
                if (dijkCityIndices.find(firstTeamS) == dijkCityIndices.end()) {
                    dijkCityIndices[firstTeamS] = index++;
                }
                if (dijkCityIndices.find(secondTeamS) == dijkCityIndices.end()) {
                    dijkCityIndices[secondTeamS] = index++;
                }

                dijkGraph[dijkCityIndices[firstTeamS]][dijkCityIndices[secondTeamS]] = distance;
                dijkGraph[dijkCityIndices[secondTeamS]][dijkCityIndices[firstTeamS]] = distance;
            }
            for (auto it = dijkCityIndices.begin(); it != dijkCityIndices.end(); it++)
            {
                dijkIndexToCity[it->second] = it->first;
            }

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }
    }

}

void dijk::pathing(vector<int>& parent, int j)
{
    if(parent[j] == -1)
    {
        return;
    }
    pathing(parent, parent[j]);
    pathForDijk.push_back(j);

}

void dijk::dijkstra(int graph[NUM_TEAMS][NUM_TEAMS], int start, int target) {
    int dist[NUM_TEAMS];
    bool visited[NUM_TEAMS];
    vector<int> parent(NUM_TEAMS, -1);

    for (int i = 0; i < NUM_TEAMS; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int i = 0; i < NUM_TEAMS; i++) {
        int m = minimumDist(dist, visited);
        visited[m] = true;
        for (int i = 0; i < NUM_TEAMS; i++) {
            if (!visited[i] && graph[m][i] && dist[m] != INT_MAX && dist[m] + graph[m][i] < dist[i])
            {
                dist[i] = dist[m] + graph[m][i];
                parent[i] = m;
            }
        }
    }
    dijkDistance = dist[target];
    pathing(parent, target);

}

void dijk::showData(Ui::dijk* ui)
{
    dijkDistance = 0;
    pathForDijk.clear();
    createMap();
    int starting = dijkCityIndices[START];
    pathForDijk.push_back(starting);
    string targetStadiumString = "SunTrust Park";
    int target = dijkCityIndices[targetStadiumString];

    dijkstra(dijkGraph, starting, target);


    //TODO:
    //1. Pull master branch from github so you have the other trip UI/files
    //2.
//    QString pathName;



//    ui->dijkTableWidget->setColumnCount(2);
//    ui->dijkTableWidget->setRowCount(15);
//    QStringList labels = { "Distance", "path"};

//    ui->dijkTableWidget->setHorizontalHeaderLabels(labels);

//    ui->dijkTableWidget->setItem(0,0,new QTableWidgetItem(QString::number(dijkDistance)));
//    int row = 0;
//    int size = pathForDijk.size();
//    for(int i = 0; i < size; i++)
//    {
//        string path;
//        path = dijkIndexToCity[pathForDijk[i]];
//        pathName = QString::fromStdString(path);
//        ui->dijkTableWidget->setItem(row++,1,new QTableWidgetItem(pathName));

//    }



}
