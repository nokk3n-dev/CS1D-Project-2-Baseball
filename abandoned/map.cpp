#include "map.h"

void Map::insert(string place, string item, double price){
    Map* temp = iterator(place);

    // If element doesnot exist already
    if (temp == nullptr)
        insert(place)->items.push_back(item);

    // If element exists already update it
    else
        temp->second = second;
}
