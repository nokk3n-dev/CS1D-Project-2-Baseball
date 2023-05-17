#include "souvenir.h"

Souvenir::Souvenir(){

};

Souvenir::Souvenir(string stadName){
    stadium = stadName;

    double arr[] = {19.99, 89.39, 17.99, 29.99, 199.99};
    string sarr[] = {"Baseball Cap", "Baseball Bat", "Team Pennant", "Autographed Baseball", "Team Jersey"};

    for(int i = 0; i < sizeof(arr); i++){
        prices.push_back(arr[i]);
    }

    items.push_back("Baseball Cap");
    items.push_back("Baseball Bat");
    items.push_back("Team Pennant");
    items.push_back("Autographed Baseball");
    items.push_back("Team Jersey");
};

void Souvenir::insertItem(string item, double price){
    prices.push_back(price);
    items.push_back(item);
}

void Souvenir::changePrice(double price, int place){
    prices[place] = price;
}

void Souvenir::removeItem(int place){
    prices.erase(prices.begin()+place);
    items.erase(items.begin()+place);

}

/*
void Souvenir::removeItemIter(QVector<Souvenir>::iterator iter){
    int tempInt;
    tempInt = difference(prices.begin(), iter);

    prices.remove(tempInt);
    items.remove(tempInt);
}*/

string Souvenir::getStadium(){
    return stadium;
}

string Souvenir::getItem(int place){
    return items[place];
}

double Souvenir::getPrice(int place){
    return prices[place];
}

int Souvenir::getSize(){
    return prices.size();
}
