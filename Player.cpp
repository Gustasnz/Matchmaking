#include "Player.hpp"

Player::Player(int id, std::string name, int score, int timestamp){
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
};
Player::~Player(){}

int Player::getId(){
    return id;
};
std::string Player::getName(){
    return name;
};
int Player::getScore(){
    return score;
};
int Player::getTimestamp(){
    return timestamp;
};