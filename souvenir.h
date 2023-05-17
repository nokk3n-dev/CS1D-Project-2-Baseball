#ifndef SOUVENIR_H
#define SOUVENIR_H

#include "dbhandler.h"
#include <QVector>

class Souvenir
{

public:
    Souvenir();

    /* Constructor, includes the following into items and prices
     *  ⦁	Baseball cap			$19.99
        ⦁	Baseball bat			$89.39
        ⦁	Team pennant			$17.99
        ⦁	Autographed baseball	$29.99
        ⦁	Team jersey             $199.99
     * */

    Souvenir(string stadName);

    //Inserts the item into the two arrays
    void insertItem(string item, double price);

    //Place dictates location in the vector ie: price[place]
    void changePrice(double price, int place);

    //Removes item, place dictates location
    void removeItem(int place);

    void removeItemIter(QVector<Souvenir>::iterator iter);

    string getStadium();
    string getItem(int place);
    double getPrice(int place);

    int    getSize();

private:
    //Acts as key for unordermap
    string stadium;
    //Vector of items, the place of the item's info should match between the two vectors
    QVector<string> items;
    QVector<double> prices;
};


#endif // SOUVENIR_H
