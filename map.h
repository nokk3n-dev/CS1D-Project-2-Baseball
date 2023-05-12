#ifndef SOUVENIR_H
#define SOUVENIR_H

#include "dbhandler.h"
#include <vector>

class Map{
public:

    //Insert key-value pair, first is key, second is value
    void insert(string place, string item, double price);

    //Find node, first is key
    Map* find(int first);

    //Returns node price, stadium is key, place for which item's price to return in the vector
    double searchPrice(string stadium, int place) const;

    //Returns node item, same deal as searchPrice
    string searchItem(string stadium, int place) const;

    //Update Value, Insert also supports update by this won't create a new node if it doesn't find a key
    void updatePrice(int first, int second);

    //Erases Item along with its price on both vectors
    void eraseItem(string stadium, int place);

    //Erase node, replaced with in-order sucessor
    void erase(string stadium, Map* temp = root);

    //Clears whole map
    void clear();


private:

    static class Map* root;

    //Locates node, used for the searches
    int convertStadium(string stadium);

    Map* iterator(string stadium);

    //# of Elements in Map
    static int cnt;

    //Left and right child, parent
    Map *left, *right, *par;

    //Height of subtree
    int depth;

    //Node Key
    int stadNum;
    //Vector of items
    vector<string> items;
    //Vector of prices
    vector<double> prices;

};

#endif // SOUVENIR_H
