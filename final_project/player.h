#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

class Player {

    private:  
        int balance = 1500;
        string name; 
        int position = 0;
        int gOJFCards = 0;
        int jailTurns = 0;
        int numUtils = 0;
        int numRail = 0;
        int numProperties = 0;
        bool inJail = false;
    public: 
        Player(string name);
        ~Player();
        void setPosition(int position);
        int getPosition();
        void setBalance(int balance);
        int getBalance();
        string getName();
        int getNumRailroads();
        int getNumUtils();
        int getNumProperties();
        void setNumProperties(int num);
        void goToJail();
        bool isInJail();
};

#endif