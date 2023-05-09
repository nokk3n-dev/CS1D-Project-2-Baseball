#ifndef TEAM_H
#define TEAM_H
#pragma once
#include <QSqlQuery>
#include <string>
#include <QVector>
#pragma once
using namespace std;

class Team
{

public:

    // Constructors
    Team();
    Team(string name, string stadium, int capacity, string location, string surface, string league, int date, int distance, string typology, string roof);
    Team(const Team &t);
    ~Team();

    // Getter function
    string getName();
    string getStadium();
    int getCapacity();
    string getLocation();
    string getSurface();
    string getLeague();
    int getDate();
    int getDTC();
    string getTypology();
    string getRoof();

    Team* operator=(const Team &t);

protected:

private:
    string team_name;
    string stadium_name;
    int seat_capacity;
    string location;
    string playing_surface;
    string league;
    int date_opened;
    int distance_to_center;
    string ballpark_typology;
    string roof_type;

};

#endif // TEAM_H
