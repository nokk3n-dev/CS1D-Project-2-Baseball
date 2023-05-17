#ifndef TEAMGRAPH_H
#define TEAMGRAPH_H
#pragma once
#include <list>
#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <QString>
using namespace std;

enum TeamName {
    DIAMONDBACKS = 0,
    BRAVES = 1,
    ORIOLES = 2,
    RED_SOX = 3,
    CUBS = 4,
    WHITE_SOX = 5,
    REDS = 6,
    INDIANS = 7,
    ROCKIES = 8,
    TIGERS = 9,
    ASTROS = 10,
    ROYALS = 11,
    ANGELS = 12,
    DODGERS = 13,
    MARLINS = 14,
    BREWERS = 15,
    TWINS = 16,
    METS = 17,
    YANKEES = 18,
    ATHLETICS = 19,
    PHILLIES = 20,
    PIRATES = 21,
    PADRES = 22,
    GIANTS = 23,
    MARINERS = 24,
    CARDINALS = 25,
    RAYS = 26,
    RANGERS = 27,
    BLUE_JAYS = 28,
    NATIONALS = 29,
    GAMBLERS = 30
};

struct TeamDist {
    TeamName team = DIAMONDBACKS;
    int distance = -1;
    bool discovery = false;
};

struct Weight {
    int distance = 0;
    bool discovery = false;
};

string printTeam(TeamName team)
{
    switch(team)
    {
    case DIAMONDBACKS:
        return "Diamondbacks";
        break;
    case BRAVES:
        return "Braves";
        break;
    case ORIOLES:
        return "Orioles";
        break;
    case RED_SOX:
        return "Red Sox";
        break;
    case CUBS:
        return "Cubs";
        break;
    case WHITE_SOX:
        return "White Sox";
        break;
    case REDS:
        return "Reds";
        break;
    case INDIANS:
        return "Indians";
        break;
    case ROCKIES:
        return "Rockies";
        break;
    case TIGERS:
        return "Tigers";
        break;
    case ASTROS:
        return "Astros";
        break;
    case ROYALS:
        return "Royals";
        break;
    case ANGELS:
        return "Angels";
        break;
    case DODGERS:
        return "Dodgers";
        break;
    case MARLINS:
        return "Marlins";
        break;
    case BREWERS:
        return "Brewers";
        break;
    case TWINS:
        return "Twins";
        break;
    case METS:
        return "Mets";
        break;
    case YANKEES:
        return "Yankees";
        break;
    case ATHLETICS:
        return "Athletics";
        break;
    case PHILLIES:
        return "Phillies";
        break;
    case PIRATES:
        return "Pirates";
        break;
    case PADRES:
        return "Padres";
        break;
    case GIANTS:
        return "Giants";
        break;
    case MARINERS:
        return "Mariners";
        break;
    case CARDINALS:
        return "Cardinals";
        break;
    case RAYS:
        return "Rays";
        break;
    case RANGERS:
        return "Rangers";
        break;
    case BLUE_JAYS:
        return "Blue Jays";
        break;
    case NATIONALS:
        return "Nationals";
    case GAMBLERS:
        return "Gamblers";
    default:
        return "No such team";
        break;
    }
}

TeamName returnTeam(int teamNum)
{
    switch(teamNum)
    {
    case 0:
        return DIAMONDBACKS;
        break;
    case 1:
        return BRAVES;
        break;
    case 2:
        return ORIOLES;
        break;
    case 3:
        return RED_SOX;
        break;
    case 4:
        return CUBS;
        break;
    case 5:
        return WHITE_SOX;
        break;
    case 6:
        return REDS;
        break;
    case 7:
        return INDIANS;
        break;
    case 8:
        return ROCKIES;
        break;
    case 9:
        return TIGERS;
        break;
    case 10:
        return ASTROS;
        break;
    case 11:
        return ROYALS;
        break;
    case 12:
        return ANGELS;
        break;
    case 13:
        return DODGERS;
        break;
    case 14:
        return MARLINS;
        break;
    case 15:
        return BREWERS;
        break;
    case 16:
        return TWINS;
        break;
    case 17:
        return METS;
        break;
    case 18:
        return YANKEES;
        break;
    case 19:
        return ATHLETICS;
        break;
    case 20:
        return PHILLIES;
        break;
    case 21:
        return PIRATES;
        break;
    case 22:
        return PADRES;
        break;
    case 23:
        return GIANTS;
        break;
    case 24:
        return MARINERS;
        break;
    case 25:
        return CARDINALS;
        break;
    case 26:
        return RAYS;
        break;
    case 27:
        return RANGERS;
        break;
    case 28:
        return BLUE_JAYS;
        break;
    case 29:
        return NATIONALS;
    case 30:
        return GAMBLERS;
    default:
        break;
    }
}

TeamName toTeam(string teamName)
{
    if (teamName == "Chase Field")
    {
        return DIAMONDBACKS;
    } else if (teamName == "SunTrust Park"){
        return BRAVES;
    } else if (teamName == "Oriole Park at Camden Yards"){
        return ORIOLES;
    } else if (teamName == "Fenway Park"){
        return RED_SOX;
    } else if (teamName == "Wrigley Field"){
        return CUBS;
    } else if (teamName == "Guaranteed Rate Field"){
        return WHITE_SOX;
    } else if (teamName == "Great American Ball Park"){
        return REDS;
    } else if (teamName == "Progressive Field"){
        return INDIANS;
    } else if (teamName == "Coors Field"){
        return ROCKIES;
    } else if (teamName == "Comerica Park"){
        return TIGERS;
    } else if (teamName == "Minute Maid Park"){
        return ASTROS;
    } else if (teamName == "Kauffman Stadium"){
        return ROYALS;
    } else if (teamName == "Angel Stadium"){
        return ANGELS;
    } else if (teamName == "Dodger Stadium"){
        return DODGERS;
    } else if (teamName == "Marlins Park"){
        return MARLINS;
    } else if (teamName == "Miller Park"){
        return BREWERS;
    } else if (teamName == "Target Field"){
        return TWINS;
    } else if (teamName == "Citi Field"){
        return METS;
    } else if (teamName == "Yankee Stadium"){
        return YANKEES;
    } else if (teamName == "Oakland-Alameda County Coliseum"){
        return ATHLETICS;
    } else if (teamName == "Citizens Bank Park"){
        return PHILLIES;
    } else if (teamName == "PNC Park"){
        return PIRATES;
    } else if (teamName == "Petco Park"){
        return PADRES;
    } else if (teamName == "Oracle Park"){
        return GIANTS;
    } else if (teamName == "Safeco Field"){
        return MARINERS;
    } else if (teamName == "Busch Stadium"){
        return CARDINALS;
    } else if (teamName == "Tropicana Field"){
        return RAYS;
    } else if (teamName == "Globe Life Park in Arlington"){
        return RANGERS;
    } else if (teamName == "Rogers Centre"){
        return BLUE_JAYS;
    } else if (teamName == "Nationals Park"){
        return NATIONALS;
    } else {
        return ATHLETICS;
    }
}

class TeamGraph
{
public:
    map<TeamName, bool> visited;
    map<int, list<TeamDist>> adj;
    vector<vector<Weight>> adjacencyMatrix;

    void initializeMatrix()
    {
        vector<Weight> rowInit;
        for (int count = 1; count < 31; count++)
        {
            // Fill with unvisited
            Weight temp;
            temp.distance = 0;
            temp.discovery = false;
            rowInit.push_back(temp);
        }

        vector<vector<Weight>> temp (31, rowInit);
        adjacencyMatrix = temp;
    }

    void addEdge(TeamName first, TeamName second, int distance)
    {
        // Initialize the TeamDist
        TeamDist temp;
        temp.team = second;
        temp.distance = distance;
        temp.discovery = false;

        // add to the first team's lsit of connecting teams
        adj[first].push_back(temp);

        // set the first team's distance and discovery
        adjacencyMatrix[first][second].distance = distance;
        adjacencyMatrix[first][second].discovery = false;

        // Set the second city's distance and discovery
        adjacencyMatrix[second][first].distance = distance;
        adjacencyMatrix[second][first].discovery = false;
    }

    void DFS(TeamName team, int& totalDistance)
    {
        visited[team] = true;

        bool loop = true;
        while (loop)
        {
            loop = false;

            TeamName closest = team;
            int minDistance = 1000000;
            list<TeamDist>::iterator i;
            for (i = adj[team].begin(); i != adj[team].end(); i++)
            {
                // Determine of this is the closest team
                if (!visited[i->team] && i->distance < minDistance)
                {
                    minDistance = i->distance;
                    closest = i->team;
                }
            }

            if (minDistance != 1000000)
            {
                loop = true;

                bool found = false;
                list<TeamDist>::iterator j = adj[team].begin();
                while(!found && j != adj[team].end())
                {
                    if (closest == j->team)
                    {
                        j->discovery = true;
                        found = true;
                    } else
                    {
                        j++;
                    }
                }

                totalDistance = totalDistance + minDistance;
                DFS(closest, totalDistance);
            }
        }
    }

    void BFS(TeamName start, int& totalDistance)
    {
        int distance = 0;
        vector<bool> visited(adjacencyMatrix.size(), false);
        vector<TeamName> t;
        t.push_back(start);

        visited[start] = true;

        TeamName temp;
        while (!t.empty())
        {
            temp = t[0];

            // ADD ROW SAYING THE FOLLOWING
            // Visited Team

            t.erase(t.begin());

            bool loop = true;
            while(loop)
            {
                loop = false;

                int minDistance = 1000000;
                int visitNum = start;
                for (int i = 0; i < adjacencyMatrix[temp].size(); i++)
                {
                    if (adjacencyMatrix[temp][returnTeam(i)].distance != 0 && (!visited[returnTeam(i)]) && (adjacencyMatrix[temp][returnTeam(i)].distance < minDistance))
                    {
                        minDistance = adjacencyMatrix[temp][returnTeam(i)].distance;
                        visitNum = i;
                    }
                }

                if (minDistance != 1000000)
                {
                    loop = true;
                    distance += minDistance;
                    adjacencyMatrix[temp][visitNum].discovery = true;
                    t.push_back(returnTeam(visitNum));
                    visited[visitNum] = true;
                }
            }
        }

        totalDistance = distance;
    }

    void ListPrintEdgeType()
    {
        for (int count = 0; count < 31; count++)
        {
            list<TeamDist>::iterator j;
            for (j = adj[count].begin(); j != adj[count].end(); j++)
            {
                string temp = "(";
                temp += printTeam(returnTeam(count));
                temp += ", ";
                temp += printTeam(j->team);
                temp += ")";
                // Need cout
                cout << temp;
                if (j->discovery == true)
                {
                    cout << " - Discovery Edge";
                } else
                {
                    cout << " - Back Edge";
                }
                cout << endl;
            }
        }
    }

    string MatrixPrintEdgeType()
    {
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                if (adjacencyMatrix[returnTeam(i)][returnTeam(j)].distance != 0)
                {
                    string temp = "(";
                    temp += printTeam(returnTeam(i));
                    temp += ", ";
                    temp += printTeam(returnTeam(j));
                    temp += ")";
                    // Need cout
                    cout << temp;
                    if (adjacencyMatrix[returnTeam(i)][returnTeam(j)].discovery == true)
                    {
                        cout << " - Discovery Edge";
                    } else
                    {
                        cout << " - Back Edge";
                    }
                    cout << endl;
                }
            }
        }
    }
};

#endif // TEAMGRAPH_H
