#ifndef TEAMGRAPH_H
#define TEAMGRAPH_H
#pragma once
#include <list>
#include <map>
#include <vector>
using namespace std;

enum City {
    DALLAS = 0,
    LOS_ANGELES = 1,
    KANSAS_CITY = 2,
    ATLANTA = 3,
    HOUSTON = 4,
    MIAMI = 5,
    SAN_FRANCISCO = 6,
    DENVER = 7,
    CHICAGO = 8,
    NEW_YORK = 9,
    SEATTLE = 10,
    BOSTON = 11
};

struct CityDist {
    City city = DALLAS;
    int distance = -1;
    bool discovery = false;
};

struct Weight {
    int distance = 0;
    bool discovery = false;
};

#endif // TEAMGRAPH_H
