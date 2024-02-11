#include "player.h"
#include "properties.h"
#include "game.h"
#include <iostream>

template <typename Item> 
Game<Item>::Game(int numPlayers){
    this->numPlayers = numPlayers;
    Player* playas[numPlayers] = {};
    this->players = playas;
    string name;
    for(int i = 0; i < numPlayers; i++){
        cout << "Enter name of player " << i << ": ";
        cin >> name;
        Player* newPlayer = new Player(name);
        players[i] = newPlayer;
    }
}

template <typename Item> 
Game<Item>::~Game(){

}

template <typename Item> 
void Game<Item>::playGame(){
    bool gameOver = false;
    makeBoard();
    while(!gameOver){
        for(int i = 0; i < numPlayers; i++){
            cout << "Player " << i << "'s turn:\n";
            if(players[i]->isInJail()){
                jailTurn(players[i]);
            }
            if(takeTurn(players[i])){
                gameOver = true;
            }
        }
    }
    cout << "Congratulations " << players[0]->getName() << "! You've won!";
}

template <typename Item> 
bool Game<Item>::takeTurn(Player* player){
    bool gameOver = false;
    int playerBalance = player->getBalance();
    string input;
    Properties** playerProperties = this->getProperties(player);
    bool notDone = true;
    if(playerBalance < 1){
        if(player->getNumProperties() < 1){
            cout << player->getName() << " has been eliminated due to no money and no mortgageable property!\n";
            gameOver = this->removePlayer(player);
            notDone = false;
        } else {
            bool notDoner = true;
            while(notDoner){
                cout << player->getName() << " has to mortgage a property/sell houses to continue playing! Input \"m\" or \"mortgage\" to mortgage, or \"s\" or \"sell\" to sell houses.\n";
                cin >> input;
                if(input == "m" || input == "mortgage"){
                    cout << "\nWhich property will you mortgage?\n";
                    this->printProperties(player);
                    cin >> input;
                    bool properInput = false;
                    while(!properInput){
                        for(int i = 0; i < player->getNumProperties(); i++){
                            if(playerProperties[i]->getName() == input){
                                playerProperties[i]->mortgage(player);
                                i = player->getNumProperties();
                                player->setNumProperties(player->getNumProperties()-1);
                                properInput = true;
                            }
                        }
                        if(!properInput){
                            cout << "\nPlease input a proper property name\n";
                        }
                    }
                    if(player->getNumProperties() < 1){
                        cout << player->getName() << " no more properties to mortgage...\n";
                        if(player->getBalance() < 1){
                            cout << "and still not enough money! " << player->getName() << " has been eliminated!";
                            this->removePlayer(player);
                            notDone = false;
                            notDoner = false;
                        }
                    }
                } else if (input == "s" || input == "sell"){
                    cout << "\nwhich property's houses would you like to sell?\n";
                    cin >> input;

                } else {
                    cout << "please input \"m\" or \"mortgage\" to mortgage, or \"s\" or \"sell\" to sell houses.\n";
                }
                if(player->getBalance() > 0){
                    notDoner = false;
                }
            }
        }
    }
    while(notDone){
        cout << player->getName() <<"'s turn, what will you do?\n";
        cout << "Balance: " << player->getBalance() << "\n";
        cout << "Properties: " << this->getProperties(player);
        cout << "Available actions:\nroll (r), build (b), sell (s), mortgage (m), unmortgage (u)\n";
        bool properInput = false;
        while(!properInput){
            cin >> input;
            if(input == "r" || input == "roll"){
                bool doubles = true;
                while(doubles) {
                    int rollO = rand() % 6 + 1;
                    int rollT = rand() % 6 + 1;
                    cout << "\nRolled a " << rollO << " and a " << rollT << "\n";
                    player->setPosition(player->getPosition() + rollO + rollT);
                    if(player->getPosition() > 39){
                        player->setPosition(player->getPosition() - 40);
                        cout << "Passed go! Collect $200\n";
                        player->setBalance(player->getBalance()+200);
                    }
                    if(rollO == rollT){
                        if(player->getPosition() == 29){
                            cout << "Landed on go to jail!\n";
                            player->goToJail();
                            doubles = false;
                        } else {
                            cout << "Doubles! Roll again!";
                        }
                    } else {
                        doubles = false;
                    }
                }
                Properties* currentPlace = board->get(player->getPosition());
                cout << "Landed on " << currentPlace->getName();
                if(player->getPosition() == 29){
                    cout << "\nGo to jail!\n";
                    player->goToJail();
                } else if(player->getPosition() == 2 || player->getPosition() == 4 || player->getPosition() == 7 ||
                            player->getPosition() == 10 || player->getPosition() == 17 || player->getPosition() == 20 ||
                            player->getPosition() == 22 || player->getPosition() == 33 || player->getPosition() == 36 ||
                            player->getPosition() == 38){
                    cout << "\nLost $" << currentPlace->getRent() << "\n";
                    player->setBalance(player->getBalance()-currentPlace->getRent());
                } else {
                    if(currentPlace->getOwner() != NULL){
                        cout << "\nThis property is owned by " << currentPlace->getOwner() << "\n";
                        if(currentPlace->getOwner()->getName() == player->getName()){
                            cout << "It's your own property! No need to pay rent.\n";
                        } else {
                            cout << "You pay $" << currentPlace->getRent() << " to " << currentPlace->getOwner() << "\n";
                            player->setBalance(player->getBalance() - currentPlace->getRent());
                        }
                    } else {
                        cout << "This property has no owner. Would you like to purchase it?\nThe price is " << currentPlace->getPrice() << "\n";
                        cin >> input;
                        bool propererInput = false;
                        while(!propererInput){
                            if(input == "y" || input == "yes"){
                                cout << "\nSold! " << currentPlace->getPrice() << " has been deducted from your balance.\n";
                                currentPlace->assignOwner(player);
                                player->setBalance(player->getBalance() - currentPlace->getPrice());
                                player->setNumProperties(player->getNumProperties()+1);
                                propererInput = true;
                            } else if(input == "n" || input == "no"){
                                propererInput = true;
                            } else {
                                cout << "\nPlease input y/yes or n/no\n";
                            }
                        }
                    }
                }
                properInput = true;
                notDone = false;
            } else if(input == "b" || input == "build"){
                int broCount = 0;
                int ligCount = 0;
                int purCount = 0;
                int oraCount = 0;
                int redCount = 0;
                int yelCount = 0;
                int greCount = 0;
                int darCount = 0;
                string monopolyList = "";
                for(int i = 0; i < player->getNumProperties(); i++){
                    string currentColor = playerProperties[i]->getColor();
                    switch (currentColor){
                        case "brown":
                            broCount++;
                            break;
                        case "lightblue":
                            ligCount++;
                            break;
                        case "purple":
                            purCount++;
                            break;
                        case "orange":
                            oraCount++;
                            break;
                        case "red":
                            redCount;
                            break;
                        case "yellow":
                            yelCount++;
                            break;
                        case "green":
                            greCount++;
                            break;
                        case "darkblue":
                            darCount++;
                            break;
                    }
                }
                bool hasMonopoly = false;
                if(broCount > 1){
                    monopolyList = monopolyList + "brown ";
                    hasMonopoly = true;
                }
                if(ligCount > 2){
                    monopolyList = monopolyList + "lightblue ";
                    hasMonopoly = true;
                }
                if(purCount > 2){
                    monopolyList = monopolyList + "purple ";
                    hasMonopoly = true;
                }
                if(oraCount > 2){
                    monopolyList = monopolyList + "orange ";
                    hasMonopoly = true;
                }
                if(redCount > 2){
                    monopolyList = monopolyList + "red ";
                    hasMonopoly = true;
                }
                if(yelCount > 2){
                    monopolyList = monopolyList + "yellow ";
                    hasMonopoly = true;
                }
                if(greCount > 2){
                    monopolyList = monopolyList + "green ";
                    hasMonopoly = true;
                }
                if(darCount > 1){
                    monopolyList = monopolyList + "darkblue ";
                    hasMonopoly = true;
                }
                if(!hasMonopoly){
                    cout << "You have no monopolies to build houses on!\n";
                } else {
                    cout << "You can build properties on " << monopolyList << "\nWhere do you want to build?\n";
                    cin >> input;
                    bool propererInput = false;
                    while(!propererInput){
                        for(int i = 0; i < player->getNumProperties(); i++){
                            Housing* currentProp = Housing(playerProperties[i]);
                            if(currentProp->getName() == input){
                                if(currentProp->getBuildings() > 3){
                                    cout << "This property already has a hotel!\n";
                                    propererInput = true;
                                } else {
                                    currentProp->upgrade();
                                    i = player->getNumProperties();
                                    propererInput = true;
                                }
                            }
                        }
                        if(!propererInput){
                            cout << "\nPlease input a proper property name\n";
                        }
                    }
                }
            } else if(input == "s" || input == "sell"){
                cout << "Which property would you like to sell buildings from?\n";
                cin >> input;
                bool propererInput = false;
                while(!propererInput){
                    for(int i = 0; i < player->getNumProperties(); i++){
                        Housing* currentProp = Housing(playerProperties[i])
                        if(currentProp->getName() == input){
                            if(currentProp->getBuildings() > 0){
                                cout << "How many buildings would you like to sell?\n";
                                bool properestInput = false;
                                int inputBuilds;
                                cin >> inputBuilds
                                while(!properestInput){
                                    if(inputBuilds > currentProp->getBuildings()){
                                        cout << "\nToo many buildings.\n";
                                    } else {
                                        
                                    }
                                }
                                propererInput = true;
                            } else {
                                cout << "This property has no buildings to sell!\n";
                                propererInput = true;
                            }
                        }
                    }
                    if(!propererInput){
                        cout << "\nPlease input a proper property name\n";
                    }
                }
            } else if(input == "m" || input == "mortgage"){

            } else if(input == "u" || input == "unmortgage"){
            
            }else {
                cout << "\nImproper input, please input r/roll, b/build, s/sell, m/mortgage or u/unmortgage.\nRemember that all inputs are lowercase!\n";
            }
        }
    }
    return gameOver;
}

template <typename Item> 
bool Game<Item>::removePlayer(Player* player){
    bool gameOver = false;

    return gameOver;
}

template <typename Item> 
void Game<Item>::jailTurn(Player* player){

}

template <typename Item> 
void Game<Item>::printProperties(Player* player){

}

template <typename Item> 
Properties** Game<Item>::getProperties(Player* player){
    
}

template <typename Item> 
void Game<Item>::makeBoard(){
    int medAveRent[] = {2, 10, 30, 90, 160, 250};
    Housing* medAve = new Housing("medave", 60, medAveRent, 50, "brown");

    int balticAveRent[] = {4, 20, 60, 180, 320, 450};
    Housing* balticAve = new Housing("balave", 60, balticAveRent, 50, "brown");

    // Light blue properties
    int orientalAveRent[] = {6, 30, 90, 270, 400, 550};
    Housing* orientalAve = new Housing("oriave", 100, orientalAveRent, 50, "lightblue");

    int vermontAveRent[] = {6, 30, 90, 270, 400, 550};
    Housing* vermontAve = new Housing("verave", 100, vermontAveRent, 50, "lightblue");

    int connecticutAveRent[] = {8, 40, 100, 300, 450, 600};
    Housing* connecticutAve = new Housing("conave", 120, connecticutAveRent, 50, "lightblue");

    // Pink properties
    int stCharlesPlaceRent[] = {10, 50, 150, 450, 625, 750};
    Housing* stCharlesPlace = new Housing("stcplace", 140, stCharlesPlaceRent, 100, "purple");

    int statesAveRent[] = {10, 50, 150, 450, 625, 750};
    Housing* statesAve = new Housing("staave", 140, statesAveRent, 100, "purple");

    int virginiaAveRent[] = {12, 60, 180, 500, 700, 900};
    Housing* virginiaAve = new Housing("virave", 160, virginiaAveRent, 100, "purple");

    // Orange properties
    int stJamesPlaceRent[] = {14, 70, 200, 550, 750, 950};
    Housing* stJamesPlace = new Housing("stjplace", 180, stJamesPlaceRent, 100, "orange");

    int tennesseeAveRent[] = {14, 70, 200, 550, 750, 950};
    Housing* tennesseeAve = new Housing("tenave", 180, tennesseeAveRent, 100, "orange");

    int newYorkAveRent[] = {16, 80, 220, 600, 800, 1000};
    Housing* newYorkAve = new Housing("newave", 200, newYorkAveRent, 100, "orange");

    // Red properties
    int kentuckyAveRent[] = {18, 90, 250, 700, 875, 1050};
    Housing* kentuckyAve = new Housing("kenave", 220, kentuckyAveRent, 150, "red");

    int indianaAveRent[] = {18, 90, 250, 700, 875, 1050};
    Housing* indianaAve = new Housing("indave", 220, indianaAveRent, 150, "red");

    int illinoisAveRent[] = {20, 100, 300, 750, 925, 1100};
    Housing* illinoisAve = new Housing("illave", 240, illinoisAveRent, 150, "red");

    // Yellow properties
    int atlanticAveRent[] = {22, 110, 330, 800, 975, 1150};
    Housing* atlanticAve = new Housing("atlave", 260, atlanticAveRent, 150, "yellow");

    int ventnorAveRent[] = {22, 110, 330, 800, 975, 1150};
    Housing* ventnorAve = new Housing("venave", 260, ventnorAveRent, 150, "yello");

    int marvinGardensRent[] = {24, 120, 360, 850, 1025, 1200};
    Housing* marvinGardens = new Housing("margardens", 280, marvinGardensRent, 150, "yellow");

    // Green properties
    int pacificAveRent[] = {26, 130, 390, 900, 1100, 1275};
    Housing* pacificAve = new Housing("pacave", 300, pacificAveRent, 200, "green");

    int northCarolinaAveRent[] = {28, 150, 450, 1000, 1200, 1400};
    Housing* northCarolinaAve = new Housing("norave", 300, northCarolinaAveRent, 200, "green");

    int pennsylvaniaAveRent[] = {35, 175, 500, 1100, 1300, 1500};
    Housing* pennsylvaniaAve = new Housing("penave", 320, pennsylvaniaAveRent, 200, "green");

    // Dark blue properties
    int parkPlaceRent[] = {50, 200, 600, 1400, 1700, 2000};
    Housing* parkPlace = new Housing("parplace", 350, parkPlaceRent, 200, "darkblue");

    int boardwalkRent[] = {50, 200, 600, 1400, 1700, 2000};
    Housing* boardwalk = new Housing("boardwalk", 400, boardwalkRent, 200, "darkblue");

    // Utilities
    Utilities* electricCompany = new Utilities("electriccompany", 150);

    Utilities* waterWorks = new Utilities("waterworks", 150);

    // Railroads
    Railroads* readingRR = new Railroads("rearr", 200);

    Railroads* pennsylvaniaRR = new Railroads("penrr", 200);

    Railroads* bnoRR = new Railroads("b&orr", 200);

    Railroads* shortLine = new Railroads("shorr", 200);

    // Exceptions

    Special* go = new Special("go", 0, 0);

    Special* freeParking = new Special("freeparking", 0, 0);

    Special* passJail = new Special("passjail", 0, 0);

    Special* goToJail = new Special("gotojail", 0, 0);

    Special* incomeTax = new Special("incometax", 0, 200);

    Special* luxuryTax = new Special("luxurytax", 0, 100);

    Special* chanceFirst = new Special("chance", 0 , 0);

    Special* chanceMid = new Special("chance", 0 , 0);

    Special* chanceLast = new Special("chance", 0 ,0);

    Special* commChestFirst = new Special("communitychest", 0, 0);

    Special* commChestMid = new Special("communitychest", 0, 0);
    
    Special* commChestLast = new Special("communitychest", 0, 0);

    board->addLast(go);
    board->addLast(medAve);
    board->addLast(commChestFirst);
    board->addLast(balticAve);
    board->addLast(incomeTax);
    board->addLast(readingRR);
    board->addLast(orientalAve);
    board->addLast(chanceFirst);
    board->addLast(vermontAve);
    board->addLast(connecticutAve);
    board->addLast(passJail);
    board->addLast(stCharlesPlace);
    board->addLast(electricCompany);
    board->addLast(statesAve);
    board->addLast(virginiaAve);
    board->addLast(pennsylvaniaRR);
    board->addLast(stJamesPlace);
    board->addLast(commChestMid);
    board->addLast(tennesseeAve);
    board->addLast(newYorkAve);
    board->addLast(freeParking);
    board->addLast(kentuckyAve);
    board->addLast(chanceMid);
    board->addLast(indianaAve);
    board->addLast(illinoisAve);
    board->addLast(bnoRR);
    board->addLast(atlanticAve);
    board->addLast(ventnorAve);
    board->addLast(waterWorks);
    board->addLast(marvinGardens);
    board->addLast(goToJail);
    board->addLast(pacificAve);
    board->addLast(northCarolinaAve);
    board->addLast(commChestLast);
    board->addLast(pennsylvaniaAve);
    board->addLast(shortLine);
    board->addLast(chanceLast);
    board->addLast(parkPlace);
    board->addLast(luxuryTax);
    board->addLast(boardwalk);
}