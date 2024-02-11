#include "properties.h"
#include "player.h"
#include "iostream"
#include <string>

Properties::Properties(string name, int price){
    this->price = price;
    this->isMortgaged = false;
    this->isAvailable = true;
    this->name = name;
}
/*
Properties::~Properties(){

}
*/
Housing::Housing(string name, int price, int* rent, int buildingPrice, string color):Properties(name,price){
    this->rent = rent;
    this->buildingPrice = buildingPrice;
    this->color = color;
}

/*
Housing::~Housing(){

};
*/

Railroads::Railroads(string name, int price):Properties(name,price){
    this->color = "rr";
}
/*
Railroads::~Railroads(){

};
*/

Utilities::Utilities(string name, int price):Properties(name,price){
    this->color = "util";
}

/*
Utilities::~Utilities(){
    
}
*/

Special::Special(string name, int price, int rent):Properties(name,price){
    this->rent = rent;
}

//
//METHODS START HERE
//

void Properties::assignOwner(Player* owner){
    this->owner = owner;
}

Player* Properties::getOwner(){
    return this->owner;
}


void Properties::mortgage(Player* player){
    //player loses property, gains half of properties price
    int mortgage = this->price/2;
    player->setBalance(player->getBalance() + mortgage);
    this->isMortgaged = true;
}

void Properties::unmortgage(Player* player){
    //player loses property, gains half of properties price
    int mortgage = this->price/2;
    int unmortgage = mortgage*1.1;
    player->setBalance(player->getBalance() + unmortgage);
    this->isMortgaged = false;
}

string Properties::getName(){
    return this->name;
}

int Properties::getPrice(){
    return this->price;
}

int Properties::getRent(){
    return 0;
}

string Properties::getColor(){
    return this->color;
}

int Housing::getRent(){
    int currentRent;

    if (this->numBuildings == 0){ //no house
        currentRent = this->rent[0];
    }
    else if (this->numBuildings == 1){ //one house
        currentRent = this->rent[1];
    }
    else if (this->numBuildings == 2){
        currentRent = this->rent[2];
    }
    else if (this->numBuildings == 3){
        currentRent = this->rent[3];
    }
    else if (this->numBuildings == 4){ //hotel
        currentRent = this->rent[4];
    }

    return currentRent;
}

int Housing::getBuildings(){
    return this->numBuildings;
}

void Housing::upgrade(){
    if(numBuildings < 4){ //can be 4 max
        this->numBuildings = this->numBuildings+1;
    }else{
        cout << "you cannot have more than a hotel" << "\n";
    }
}

int Housing::sell(){
    
}

int Utilities::getRent(Player* player){

    int currentRent;
    if (player->getNumUtils() == 0){ //no railroad owned
        currentRent = 0;
    }
    else if (player->getNumRailroads() == 1){
        //currentRent = player->getDiceRoll()*4;
    }else if (player->getNumRailroads() == 2){
        //currentRent = player->getDiceRoll()*10;
    }
    return currentRent;
}

int Railroads::getRent(Player* player){
    int currentRent; //watch out for potential bug with player paremeter used inside another parameter.
                    //not sure how to fix it if there is a bug, just watch out

    if (player->getNumRailroads() == 0){ //no railroad owned
        currentRent = 0;
    }
    else if (player->getNumRailroads() == 1){
        currentRent = 25;
    }
    else if (player->getNumRailroads() == 2){
        currentRent = 50;
    }
    else if (player->getNumRailroads() == 3){
        currentRent = 100;
    }
    else if (player->getNumRailroads() == 4){ //4 railroads owned
        currentRent = 200;
    }

    return currentRent;
}
