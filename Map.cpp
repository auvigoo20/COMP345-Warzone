#include "Map.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

/*
 * CONTINENT
 */

ostream& operator<<(ostream &strm, const Continent &c){
    return strm << "CONTINENT: ID:" << c.id << " - Name:" << c.name << " - Bonus:" << c.bonus << endl;
}

Continent::Continent() {
    id = 0;
    name = "";
    bonus = 0;
}

Continent::Continent(const Continent &c) {
    id = c.id;
    name = c.name;
    bonus = c.bonus;
}

Continent::Continent(int id, string name, int bonus) {
    this->id = id;
    this->name = name;
    this->bonus = bonus;
}

void Continent::setID(int id) {
    this->id = id;
}

void Continent::setBonus(int bonus) {
    this->bonus = bonus;
}

void Continent::setName(std::string name) {
    this->name = name;
}

/*
 * TERRITORY
 */

ostream& operator<<(ostream &strm, const Territory &t){
    return strm << "TERRITORY: ID:" << t.id << " - Name:" << t.name << endl;
}
Territory::Territory() {
    id = 0;
    owner = nullptr;
    continent = nullptr;
    numOfArmies = 0;
    name = "";
    x = 0;
    y = 0;
}

// Copy constructor
Territory::Territory(const Territory &t) {
    owner = t.owner;
    numOfArmies = t.numOfArmies;
    name = t.name;
    adjacentTerritories = t.adjacentTerritories;
    x = t.x;
    y = t.y;
}

Territory::Territory(int id, string name, int x, int y) {
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
}

Territory::Territory(int id, Player *owner, Continent* continent, int numOfArmies, std::string name, vector<Territory *>, int x, int y) {
    this->id = id;
    this->owner = owner;
    this->continent = continent;
    this->numOfArmies = numOfArmies;
    this->name = name;
    this->adjacentTerritories = adjacentTerritories;
    this->x = x;
    this->y = y;
}

Territory::Territory(int id, Player *owner, Continent* continent, int numOfArmies, std::string name, int x, int y) {
    this->id = id;
    this->owner = owner;
    this->continent = continent;
    this->numOfArmies = numOfArmies;
    this->name = name;
    this->x = x;
    this->y = y;
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

/*
 * MAP
 */

ostream& operator<<(ostream &strm, const Map &m){
    return strm << "MAP: Number of territories:" << m.allTerritories.size() << " - Number of continents:" << m.allContinents.size() << endl;
}

Map::Map(){}

Map::Map(const Map &map) {
    this ->allTerritories = map.allTerritories;
    this->allContinents = map.allContinents;
}

void Map::setAllTerritories(vector<Territory *> territories) {
    this->allTerritories = territories;
}

void Map::setAllContinents(vector<Continent *> continents) {
    this->allContinents = continents;
}

void Map::addTerritory(Territory *t) {
    allTerritories.push_back(t);
}

void Map::addContinent(Continent *c) {
    allContinents.push_back(c);
}

// Depth-first search recursive algorithm to visit all adjacent territories to the current territory
void Map::dfs(vector<int> *visitedTerritoriesIds, Territory *currentTerritory) {

    vector<Territory*> currentAdjacentTerritories = currentTerritory->getAdjacentTerritories();

    // Base case: if current territory has already been visited, return
    if(std::find(visitedTerritoriesIds->begin(), visitedTerritoriesIds->end(), currentTerritory->getID()) != visitedTerritoriesIds->end()){
        return;
    }

    cout << "visiting territory: " << *currentTerritory << std::endl;
    // Add current territory to visited territories
    visitedTerritoriesIds->push_back(currentTerritory->getID());

    for(int i = 0; i < currentAdjacentTerritories.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs(visitedTerritoriesIds, currentAdjacentTerritories.at(i));
    }
}

// Check if map is a connected graph
bool Map::isConnectedTerritories() {

    vector<int> visitedTerritoriesIds;
    Territory* startTerritory = allTerritories.at(0);

    // start DFS at first territory
    dfs(&visitedTerritoriesIds, startTerritory);

    // check if all territories have been visited after DFS
    for (int i = 0; i < allTerritories.size(); i++){
        if(std::find(visitedTerritoriesIds.begin(), visitedTerritoriesIds.end(), allTerritories.at(i)->getID()) == visitedTerritoriesIds.end()){
            return false;
        }
    }
    return true;
}

Continent* Map::getContinentById(int continentID) {
    for (int i = 0; i < allContinents.size(); i++){
        if (allContinents.at(i)->getID() == continentID){
            return allContinents.at(i);
        }
    }
}

vector<Territory*> Map::getAllTerritoriesByContinent(Continent* continent) {
    vector<Territory*> continentTerritories;
    cout << endl << continent->getName() << ":";
    for(int i = 0; i < allTerritories.size(); i++){
        if(allTerritories.at(i)->getContinent() == continent){
            continentTerritories.push_back(allTerritories.at(i));
            cout << allTerritories.at(i)->getName() << " ";
        }
    }
    cout << endl;
    return continentTerritories;
}

/*
 * Depth-first search recursive algorithm to visit all adjacent territories to the current territory.
 * Slight variation in this algorithm since it does not take into account adjacent territories that are not part of
 * the currently searched Continent.
*/
void Map::dfs_continent(vector<int> *visitedTerritoriesIds, Territory *currentTerritory,
                        Continent* currentContinent) {

    // Need to remove adjacent territories that aren't in the current continent
    vector<Territory*> currentAdjacentTerritoriesInContinent;
    for(int i = 0 ;i < currentTerritory->getAdjacentTerritories().size(); i++){
        if(currentTerritory->getAdjacentTerritories().at(i)->getContinent() == currentContinent){
            currentAdjacentTerritoriesInContinent.push_back(currentTerritory->getAdjacentTerritories().at(i));
        }
    }

    // Base case: if current territory has already been visited, return
    if(std::find(visitedTerritoriesIds->begin(), visitedTerritoriesIds->end(), currentTerritory->getID()) != visitedTerritoriesIds->end()){
        return;
    }

    cout << "visiting territory: " << currentTerritory->getName() << std::endl;
    // Add current territory to visited territories
    visitedTerritoriesIds->push_back(currentTerritory->getID());

    for(int i = 0; i < currentAdjacentTerritoriesInContinent.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs_continent(visitedTerritoriesIds, currentAdjacentTerritoriesInContinent.at(i), currentContinent);
    }
}

// Check if Map's continents are connected subgraphs
bool Map::isConnectedContinents() {

    for (int i = 0; i < allContinents.size(); i++){
        Continent* currentContinent = allContinents.at(i);
        vector<Territory*> currentContinentTerritories = getAllTerritoriesByContinent(currentContinent);
        vector<int> visitedTerritories;
        Territory* startTerritory = currentContinentTerritories.at(0);

        // Start DFS at first territory
        dfs_continent(&visitedTerritories, startTerritory, currentContinent);

        // If number of visited territories is not equal to the number of territories of a given continent, it is not a connected subgraph
        if (visitedTerritories.size() != currentContinentTerritories.size()){
            return false;
        }
    }
    return true;
}


int main(){
    Continent* c1 = new Continent(1, "continent1", 5);
    Continent* c2 = new Continent(2, "continent2", 5);

    cout << *c1;
    cout << *c2;

    Territory* t1 = new Territory(1,"territory1", 2, 3);
    Territory* t2 = new Territory(2,"territory2", 2, 3);
    Territory* t3 = new Territory(3,"territory3", 2, 3);
    Territory* t4 = new Territory(4,"territory4", 2, 3);
    Territory* t5 = new Territory(5,"territory5", 2, 3);

    t1->setContinent(c1);
    t2->setContinent(c1);
    t3->setContinent(c2);
    t4->setContinent(c2);
    t5->setContinent(c2);

    t1->addAdjacentTerritory(t3);
    t1->addAdjacentTerritory(t2);

    t2->addAdjacentTerritory(t3);
    t2->addAdjacentTerritory(t1);


    t3->addAdjacentTerritory(t1);
    t3->addAdjacentTerritory(t2);
    t3->addAdjacentTerritory(t4);

    t4->addAdjacentTerritory(t3);
    t4->addAdjacentTerritory(t5);

    t5->addAdjacentTerritory(t4);

    Map map;
    map.addTerritory(t1);
    map.addTerritory(t2);
    map.addTerritory(t3);
    map.addTerritory(t4);
    map.addTerritory(t5);

    map.addContinent(c1);
    map.addContinent(c2);



    bool x = map.isConnectedTerritories();
    cout << "connected territories?:" << x << endl;

    Continent* cont1 = map.getContinentById(1);
    vector<Territory*> t = map.getAllTerritoriesByContinent(cont1);

    Continent* cont2 = map.getContinentById(2);
    vector<Territory*> tt = map.getAllTerritoriesByContinent(cont2);

    bool y = map.isConnectedContinents();
    cout << "connected continents?:" << y << endl;

    cout << map;

    delete c1;
    delete c2;

    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
}