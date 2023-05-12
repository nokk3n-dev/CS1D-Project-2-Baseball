#include "map.h"

int Map::convertStadium(string stadium){
    int temp;

    return temp;
};

Map* Map::iterator(string stadium){
    Map* temp = root;
        while (temp != nullptr && temp->stadium != stadium) {
            if (stadium < temp->stadium) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return temp;
};

void Map::insert(string place, string item, double price){
    Map* temp = iterator(place);

    // If element doesnot exist already
    if (temp == nullptr)
        insert(place)->items.push_back(item);

    // If element exists already update it
    else
        temp->second = second;
};
