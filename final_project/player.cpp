#include "player.h"
#include <iostream>
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()
using namespace std;

Player::Player(string name) {
    this->name = name;
}

Player::~Player(){

}

void Player::setPosition(int position) {
    this->position = position;
}

int Player::getPosition(){
    return this->position;
}

void Player::setBalance(int balance) {
    this->balance = balance;
}

int Player::getBalance() {
    return this->balance;
}

string Player::getName() {
    return this->name;
}

int Player::getNumRailroads() {
    return this->numRail;
}

int Player::getNumUtils() {
    return this->numUtils;
}

int Player::getNumProperties(){
    return this->numProperties;
}

void Player::setNumProperties(int num){
    this->numProperties = num;
}

void Player::goToJail(){
    this->position = 10;
    this->inJail = true;
}

bool Player::isInJail(){
    return inJail;
}