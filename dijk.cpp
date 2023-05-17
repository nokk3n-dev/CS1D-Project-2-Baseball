#include "dijk.h"
#include "ui_dijk.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <vector>
#include <map>
#include <string>
#include <limits>

const int NUM_TEAMS = 50;
int graph[NUM_TEAMS][NUM_TEAMS];
std::map<std::string, int> dijkCityIndices;
std::map<int, std::string> dijkIndexToCity;

dijk::dijk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dijk)
{
    ui->setupUi(this);
    createMap();
}

dijk::~dijk()
{
    delete ui;
}

void dijk::createMap()
{
    QMessageBox msgBox;
    QString firstTeam;
    QString secondTeam;
    int distance = 0;
    int currentIndex = 0;

    DbHandler dbHandler(DATABASE_PATH, DATABASE_CONNECTION_NAME);
    if (dbHandler.open())
    {
        QSqlQuery query("SELECT Start_Stadium, End_Stadium, distance FROM Distance");

        while (query.next())
        {
            firstTeam = query.value(0).toString();
            secondTeam = query.value(1).toString();
            distance = query.value(2).toInt();
            std::string firstTeamS = firstTeam.toStdString();
            std::string secondTeamS = secondTeam.toStdString();

            if (dijkCityIndices.find(firstTeamS) == dijkCityIndices.end()) {
                dijkCityIndices[firstTeamS] = currentIndex++;
            }
            if (dijkCityIndices.find(secondTeamS) == dijkCityIndices.end()) {
                dijkCityIndices[secondTeamS] = currentIndex++;
            }

            graph[dijkCityIndices[firstTeamS]][dijkCityIndices[secondTeamS]] = distance;
            graph[dijkCityIndices[secondTeamS]][dijkCityIndices[firstTeamS]] = distance;
        }

        for (const auto& cityIndex : dijkCityIndices) {
            dijkIndexToCity[cityIndex.second] = cityIndex.first;
        }

        // Dijkstra's algorithm
        for (int startVertex = 0; startVertex < currentIndex; ++startVertex) {
            // Initialize distances to infinity
            std::vector<int> distances(currentIndex, std::numeric_limits<int>::max());
            distances[startVertex] = 0;

            // Visited vertices
            std::vector<bool> visited(currentIndex, false);

            // Find the shortest path for all vertices
            for (int count = 0; count < currentIndex - 1; ++count) {
                int minDistance = std::numeric_limits<int>::max();
                int minIndex = -1;

                // Find the vertex with the minimum distance
                for (int i = 0; i < currentIndex; ++i) {
                    if (!visited[i] && distances[i] <= minDistance) {
                        minDistance = distances[i];
                        minIndex = i;
                    }
                }

                // Mark the selected vertex as visited
                visited[minIndex] = true;

                // Update distances of the adjacent vertices
                for (int i = 0; i < currentIndex; ++i) {
                    if (!visited[i] && graph[minIndex][i] &&
                        distances[minIndex] != std::numeric_limits<int>::max() &&
                        distances[minIndex] + graph[minIndex][i] < distances[i]) {
                        distances[i] = distances[minIndex] + graph[minIndex][i];
                    }
                }
            }

            // Update the graph with the calculated distances for the start vertex
            for (int i = 0; i < currentIndex; ++i) {
                graph[startVertex][i] = distances[i];
                graph[i][startVertex] = distances[i];
            }
        }
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
        dbHandler.close();
    }
}
int dijk::calcDistance(const string& teamOne, const string& teamTwo)
{
    int indexOne = dijkCityIndices[teamOne];
    int indexTwo = dijkCityIndices[teamTwo];
    return graph[indexOne][indexTwo];
}

int dijk::distCalc(const vector<string>& teams)
{
    int distance = 0;
    for (unsigned long long i = 0; i < teams.size() - 1; i++)
    {
        distance += graph[dijkCityIndices[teams[i]]][dijkCityIndices[teams[i + 1]]];
    }

    return distance;
}
