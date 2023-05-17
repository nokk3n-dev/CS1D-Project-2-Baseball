#include "unorderedmap.h"

Map::Map()
{

}

Map::Map(string stadium){
    this->insert(stadium);
}

int Map::size()
{
    return souvMap.size();
}

bool Map::empty()
{
    return souvMap.empty();
}

QVector<Souvenir>::iterator Map::find(string key)
{
    // Creates an iterator to traverse the map.
    QVector<Souvenir>::iterator iter = souvMap.begin();

    // Boolean variable used to determine whether the
    // key already exists in the map.
    bool found = false;

    // Traverses the map until the key is found or the
    // end of the map is reached.
    while(iter != souvMap.end() && !found)
    {
        if(iter->getStadium() == key)
        {
            found = true;
        }
        else
        {
            iter++;
        }
    }

    return iter;
}

/*
int Map::findInt(string key)
{
    // Creates an iterator to traverse the map.
    QVector<Souvenir>::iterator iter = souvMap.begin();
    int i = 0;

    // Boolean variable used to determine whether the
    // key already exists in the map.
    bool found = false;

    // Traverses the map until the key is found or the
    // end of the map is reached.
    while(iter != souvMap.end() && !found)
    {
        if(iter->getStadium() == key)
        {
            found = true;
        }
        else
        {
            iter++;
            i++;
        }
    }

    return i;
}
*/

void Map::insert(string key){
    QVector<Souvenir>::iterator iter = find(key);

    if(iter == souvMap.end())
    {
        Souvenir temp(key);
        souvMap.push_back(temp);
        iter--;
    }
    else
    {
        qDebug() << "\nKey already in, use insertWhole to replace";
    }

}

QVector<Souvenir>::iterator Map::insertWhole(string key, Souvenir stadium)
{
    // Creates an iterator and immediately calls find() to determine
    // whether or not a value with the same key already exists.
    QVector<Souvenir>::iterator iter = find(key);

    // If there is no value with the specified key, the value is added
    // to the end of the map, else the value with the same key is
    // replaced with the new value.
    if(iter == souvMap.end())
    {
        souvMap.push_back(stadium);

        iter--;
    }
    else
    {
        *iter = stadium;
    }

    return iter;
}

Souvenir Map::operator[](int index)
{
    return souvMap.at(index);
}

Souvenir Map::operator[](QVector<Souvenir>::Iterator iter){
   //return souvMap.at(*iter);
}

QVector<Souvenir>::iterator Map::begin()
{
    return souvMap.begin();
}

QVector<Souvenir>::iterator Map::end()
{
    return souvMap.end();
}
