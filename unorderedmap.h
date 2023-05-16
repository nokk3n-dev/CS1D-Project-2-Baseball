#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include "souvenir.h"

class Map
{
public:
    Map();

    Souvenir operator[](int index);

    int size();

    bool empty();

    vector<Souvenir>::iterator find(string key);

    void insert(string key);

    vector<Souvenir>::iterator insertWhole(string key, Souvenir stadium);


    vector<Souvenir>::iterator begin();

    vector<Souvenir>::iterator end();

    vector<Souvenir> souvMap;

};


#endif // UNORDEREDMAP_H