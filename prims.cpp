#include "prims.h"
#include "ui_prims.h"
#include <unordered_map>

const int INF = 10000000;
const int NUM_TEAMS = 50;
int primsGraph[NUM_TEAMS][NUM_TEAMS];
unordered_map<string, int> primsCityIndices;
unordered_map<int, string> primsIndexToCity;
vector<string> primsMstTree;
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

prims::~prims()
{
    delete ui;
}


void prims::createMap()
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
            if (primsCityIndices.find(teamS) == primsCityIndices.end())
            {
                primsCityIndices[teamS] = currentIndex;
                primsIndexToCity[currentIndex] = teamS;
                currentIndex++;

            }

        }
        primsIndexCounter = currentIndex;





        while(query1.next())
        {
            firstTeam = query1.value(0).toString();
            secondTeam = query1.value(1).toString();
            distance = query1.value(2).toInt();
            firstTeamS = firstTeam.toStdString();
            secondTeamS = secondTeam.toStdString();

            primsGraph[primsCityIndices[firstTeamS]][primsCityIndices[secondTeamS]] = distance;
            primsGraph[primsCityIndices[secondTeamS]][primsCityIndices[firstTeamS]] = distance;

        }
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
        dbHandler.close();
    }
}

void prims::primsAlgo()
{
    vector<int> parent(NUM_TEAMS, -1);
    vector<int> key(NUM_TEAMS, INF);
    vector<bool> inMST(NUM_TEAMS, false);

    key[0] = 0;

    for (int i = 0; i < NUM_TEAMS - 1; i++) {
        int u = -1;
        for (int j = 0; j < NUM_TEAMS; j++) {
            if (!inMST[j] && (u == -1 || key[j] < key[u])) {
                u = j;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < NUM_TEAMS; v++)
        {
            if (primsGraph[u][v] != 0 && !inMST[v] && primsGraph[u][v] < key[v])
            {
                key[v] = primsGraph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalWeight = 0;
    for (int i = 1; i < primsIndexCounter; i++)
    {
        totalWeight += primsGraph[i][parent[i]];
    }
    primsMstWeight = totalWeight;


    for (int i = 1; i < primsIndexCounter; i++)
    {
        string msttreee = primsIndexToCity[parent[i]] + " -> " + primsIndexToCity[i];
        primsMstTree.push_back(msttreee);
    }
}


void prims::showData(Ui::prims* ui)
{
    createMap();
    primsAlgo();


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
