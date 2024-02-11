#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include "player.h"
using namespace std;

class Properties {
    private:
        int price;
        bool isAvailable;
        bool isMortgaged;
        Player* owner = NULL;
        string name;
        string color;
    public:
        Properties(string name, int price);
        //~Properties();
        void assignOwner(Player* owner);
        Player* getOwner();
        void mortgage(Player* player);
        void unmortgage(Player* player);
        void sell(Player* newOwner);
        string getName();
        int getPrice();
        int getRent();
        string getColor();
};

class Housing: public Properties{
    private:
        int buildingPrice;
        int* rent;
        int numBuildings = 0;
        string color;
    public:
        Housing(string name, int price, int* rent, int buildingPrice, string color);
        void upgrade();
        int getRent();
        int getBuildings();
        int sell();
};

class Utilities: public Properties {
    private:
        string color;
    public:
        Utilities(string name, int price);
        int getRent(Player* player);
};

class Railroads: public Properties{
    private:
        string color;
    public:
        Railroads(string name, int price);
        int getRent(Player* player);
};

class Special: public Properties{
    private:
        int rent;
        string color;
    public:
        Special(string name, int price, int rent);
        int getRent();
};

#endif