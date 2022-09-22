#pragma once
#include "Map.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
Territory::Territory() {
    owner = nullptr;
    numOfArmies = 0;
    name = "";
    x = 0;
    y = 0;
}

Territory::Territory(Territory &t) {
    owner = t.owner;
    numOfArmies = t.numOfArmies;
    name = t.name;
    adjacentTerritories = t.adjacentTerritories;
    x = t.x;
    y = t.y;
}

Territory::Territory(Player *owner, Continent* continent, int numOfArmies, std::string name, vector<Territory *>, int x, int y) {
    this->owner = owner;
    this->continent = continent;
    this->numOfArmies = numOfArmies;
    this->name = name;
    this->adjacentTerritories = adjacentTerritories;
    this->x = x;
    this->y = y;
}

Player* Territory::getOwner() {
    return this->owner;
}

int Territory::getNumOfArmies() {
    return this->numOfArmies;
}

string Territory::getName() {
    return this->name;
}

vector<Territory*> Territory::getAdjacentTerritories() {
    return this->adjacentTerritories;
}

int Territory::getX(){
    return this->x;
}

int Territory::getY(){
    return this->y;
}

void Territory::setOwner(Player* player){
    this->owner = player;
}

void Territory::setContinent(Continent* continent){
    this->continent = continent;
}
void Territory::setNumOfArmies(int numOfArmies){
    this->numOfArmies = numOfArmies;
}

void Territory::setName(string name){
    this->name = name;
}

void Territory::setAdjacentTerritories(vector<Territory*> territories){
    this->adjacentTerritories = territories;
}

void Territory::setX(int x){
    this->x = x;
}

void Territory::setY(int y){
    this->y = y;
}

void Territory::addAdjacentTerritory(Territory *territory) {
    adjacentTerritories.push_back(territory);
}