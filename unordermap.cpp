#include "unorderedmap.h"

Map::Map()
{

}

int Map::size()
{
    return souvMap.size();
}

bool Map::empty()
{
    return souvMap.empty();
}

vector<Souvenir>::iterator Map::find(string key)
{
    // Creates an iterator to traverse the map.
    vector<Souvenir>::iterator iter = souvMap.begin();

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

void Map::insert(string key){
    vector<Souvenir>::iterator iter = find(key);

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

vector<Souvenir>::iterator Map::insertWhole(string key, Souvenir stadium)
{
    // Creates an iterator and immediately calls find() to determine
    // whether or not a value with the same key already exists.
    vector<Souvenir>::iterator iter = find(key);

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

vector<Souvenir>::iterator Map::begin()
{
    return souvMap.begin();
}

vector<Souvenir>::iterator Map::end()
{
    return souvMap.end();
}
