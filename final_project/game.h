#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "properties.h"
using namespace std;

template <typename Item> 
class Game {
    private:
        LinkedList<Item>* board;
        Player** players;
        int numPlayers;
    public:
        Game(int numPlayers);
        ~Game();
        void playGame();
        bool takeTurn(Player* player);
        bool removePlayer(Player* player);
        void jailTurn(Player* player);
        void buyProperty(Player* player, Properties* property);
        void printProperties(Player* player);
        Properties** getProperties(Player* player);
        void makeBoard();
        //void trade();
        //void chanceChest();
};

#endif