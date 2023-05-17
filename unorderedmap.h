#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include "souvenir.h"
#include <QDebug>

class Map
{
public:
    Map();

    Map(string stadium);

    Souvenir operator[](int index);

    Souvenir operator[](QVector<Souvenir>::iterator iter);

    int size();

    bool empty();

    QVector<Souvenir>::iterator find(string key);

    void insert(string key);

    QVector<Souvenir>::iterator insertWhole(string key, Souvenir stadium);


    QVector<Souvenir>::iterator begin();

    QVector<Souvenir>::iterator end();

    QVector<Souvenir> souvMap;

};

#endif // UNORDEREDMAP_H
