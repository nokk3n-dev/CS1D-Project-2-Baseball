#include "dfsbfspage.h"
#include "ui_dfsbfspage.h"
#include "TeamGraph.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "dbhandler.h"

DfsBfsPage::DfsBfsPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DfsBfsPage)
{
    ui->setupUi(this);

    // Set up background
    QPixmap bkgnd("C:\\Coding\\CS1D-Project-2-Baseball\\CS1D-Project-2-Baseball\\Resources\\dfsbfsPage.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->backgroundLabel->setStyleSheet("QLabel { background-color : white; }");

}

DfsBfsPage::~DfsBfsPage()
{
    delete ui;
}

void DfsBfsPage::on_dfs_button_clicked()
{
    // For the db
    QMessageBox msgBox;
    QString firstTeam;
    QString secondTeam;
    int distance = 0;

    TeamGraph teams;
    int dfsDistance = 0;
    teams.initializeMatrix();

    // Get the edges
    DbHandler dbHandler(DATABASE_PATH, DATABASE_CONNECTION_NAME);
    if (dbHandler.open())
    {
        QSqlQuery query("SELECT Start_Stadium, End_Stadium, distance FROM Distance");

        while(query.next())
        {
            firstTeam = query.value(0).toString();
            secondTeam = query.value(1).toString();
            distance = query.value(2).toInt();

            TeamName team1 = toTeam(firstTeam.toStdString());
            TeamName team2 = toTeam(secondTeam.toStdString());

            teams.addEdge(team1, team2, distance);
        }

    }

    teams.DFS(GIANTS, dfsDistance);
    //teams.ListPrintEdgeType();

    QString dfsDist = QString::fromStdString(to_string(dfsDistance));
    ui->distanceLabel->setText(dfsDist);
}


void DfsBfsPage::on_bfs_button_clicked()
{
    // For the db
    QMessageBox msgBox;
    QString firstTeam;
    QString secondTeam;
    int distance = 0;

    TeamGraph teams;
    int bfsDistance = 0;
    teams.initializeMatrix();

    // Get the edges
    DbHandler dbHandler(DATABASE_PATH, DATABASE_CONNECTION_NAME);
    if (dbHandler.open())
    {
        QSqlQuery query("SELECT Start_Stadium, End_Stadium, distance FROM Distance");

        while(query.next())
        {
            firstTeam = query.value(0).toString();
            secondTeam = query.value(1).toString();
            distance = query.value(2).toInt();

            TeamName team1 = toTeam(firstTeam.toStdString());
            TeamName team2 = toTeam(secondTeam.toStdString());

            teams.addEdge(team1, team2, distance);
        }

    }

    teams.BFS(TWINS, bfsDistance);
    //teams.MatrixPrintEdgeType();

    QString bfsDist = QString::fromStdString(to_string(bfsDistance));
    ui->distanceLabel->setText(bfsDist);
}

