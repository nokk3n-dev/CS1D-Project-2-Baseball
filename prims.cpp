#include "prims.h"
#include "ui_prims.h"

const int INF = INT_MAX;

const int NUM_TEAMS = 50;
int primsGraph[NUM_TEAMS][NUM_TEAMS];
map<string, int> primsCityIndices;
map<int, string> primsIndexToCity;
vector<string> primsMstTree;
int teamCounter = 0;
int primsMstWeight = 0;
int primsIndexCounter = 0;
prims::prims(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prims)
{
    ui->setupUi(this);
    ui->primsDisplayWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showData(ui);


}

void prims::primsAlgo(int graph[50][50])
{
    int edge = 0;

    int visit[teamCounter];

    for (int i = 0; i < teamCounter; i++) {
        visit[i] = false;
    }

    edge = 0;

    visit[0] = true;

    int x;
    int y;

    int totalWeight = 0;

    while (edge < teamCounter - 1)
    {

        int minWeight = INT_MAX;
        x = 0;
        y = 0;

        for (int i = 0; i < teamCounter; i++)
        {
            if (visit[i]) {
                for (int j = 0; j < teamCounter; j++)
                {
                    if (!visit[j] && graph[i][j])
                    {
                        if (minWeight > graph[i][j])
                        {
                            minWeight = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        totalWeight += graph[x][y];
        int z = graph[x][y];
        string path =  primsIndexToCity[x] + " ---> " + primsIndexToCity[y] +  " " + to_string(z);
        primsMstTree.push_back(path);

        visit[y] = true;
        edge++;
    }


    primsMstWeight = totalWeight;
}

prims::~prims()
{
    delete ui;
}


void prims::createMap()
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
                if (primsCityIndices.find(firstTeamS) == primsCityIndices.end()) {
                    primsCityIndices[firstTeamS] = index++;
                }
                if (primsCityIndices.find(secondTeamS) == primsCityIndices.end()) {
                    primsCityIndices[secondTeamS] = index++;
                }

                primsGraph[primsCityIndices[firstTeamS]][primsCityIndices[secondTeamS]] = distance;
                primsGraph[primsCityIndices[secondTeamS]][primsCityIndices[firstTeamS]] = distance;
            }

            for (auto it = primsCityIndices.begin(); it != primsCityIndices.end(); it++)
            {
                primsIndexToCity[it->second] = it->first;
            }
            teamCounter = index;
            teamCounter -= 1;

        }
        else
        {
            msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
            msgBox.exec();
            dbHandler.close();
        }
    }


}



void prims::showData(Ui::prims* ui)
{
    createMap();
    primsAlgo(primsGraph);



    QString pathName;

    ui->primsDisplayWidget->setColumnCount(2);
    ui->primsDisplayWidget->setRowCount(35);
    QStringList labels = { "MST weight", "MST paths"};



    ui->primsDisplayWidget->setHorizontalHeaderLabels(labels);

    ui->primsDisplayWidget->setItem(0,0,new QTableWidgetItem(QString::number(primsMstWeight)));
    int row = 0;
    int size = primsMstTree.size();
    for(int i = 0; i < size; i++)
    {
        string path;
        path = primsMstTree[i];
        pathName = QString::fromStdString(path);
        ui->primsDisplayWidget->setItem(row++,1,new QTableWidgetItem(pathName));

    }


}


