#include "souvenir.h"

Souvenir::Souvenir(){
    double arr[] = {19.99, 89.39, 17.99, 29.99, 199.99};
    string sarr[] = {"Basseball Cap, Baseball Bat, Team Pennant, Autographed Baseball, Team Jersey"};
    prices.insert(prices.end(), arr, arr+5);
    items.insert(items.end(), sarr, sarr+5);

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

string Souvenir::getStadium(){
    return stadium;
}

string Souvenir::getItem(int place){
    return items[place];
}

double Souvenir::getPrice(int place){
    return prices[place];
}
