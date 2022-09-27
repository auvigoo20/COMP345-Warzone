#include "Map.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::getline;

/*
 * CONTINENT
 */

ostream& operator<<(ostream &strm, const Continent &c){
    return strm << "CONTINENT: Name:" << c.name << " - Bonus:" << c.bonus << endl;
}

Continent::Continent() {
    name = "";
    bonus = 0;
}

Continent::Continent(const Continent &c) {
    name = c.name;
    bonus = c.bonus;
}

Continent::Continent(string name, int bonus) {
    this->name = name;
    this->bonus = bonus;
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
    return strm << "TERRITORY: Name:" << t.name << " - Continent:" << t.continent->getName() << endl;
}
Territory::Territory() {
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

Territory::Territory(string name, int x, int y, Continent* continent) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->continent = continent;
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

Territory::Territory(Player *owner, Continent* continent, int numOfArmies, std::string name, int x, int y) {
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

Map::~Map(){
    for(auto continent: allContinents){
        delete continent;
    }
    for(auto territory: allTerritories){
        delete territory;
    }
}

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
void Map::dfs(vector<string> *visitedTerritoriesNames, Territory *currentTerritory) {

    vector<Territory*> currentAdjacentTerritories = currentTerritory->getAdjacentTerritories();

    // Base case: if current territory has already been visited, return
    if(std::find(visitedTerritoriesNames->begin(), visitedTerritoriesNames->end(), currentTerritory->getName()) != visitedTerritoriesNames->end()){
        return;
    }

    cout << "visiting territory: " << *currentTerritory << std::endl;
    // Add current territory to visited territories
    visitedTerritoriesNames->push_back(currentTerritory->getName());

    for(int i = 0; i < currentAdjacentTerritories.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs(visitedTerritoriesNames, currentAdjacentTerritories.at(i));
    }
}

// Check if map is a connected graph
bool Map::isConnectedTerritories() {

    vector<string> visitedTerritoriesNames;
    Territory* startTerritory = allTerritories.at(0);

    // start DFS at first territory
    dfs(&visitedTerritoriesNames, startTerritory);

    // check if all territories have been visited after DFS
    for (int i = 0; i < allTerritories.size(); i++){
        if(std::find(visitedTerritoriesNames.begin(), visitedTerritoriesNames.end(), allTerritories.at(i)->getName()) == visitedTerritoriesNames.end()){
            cout << "Territories do not form a connected graph!" << endl;
            return false;
        }
    }
    cout << "Territories form a connected graph!" << endl;
    return true;
}

Continent* Map::getContinentByName(string continentName) {
    for(auto continent: allContinents){
        if(continent->getName() == continentName){
            return continent;
        }
    }
}

Territory* Map::getTerritoryByName(std::string territoryName) {
    for(auto territory: allTerritories){
        if(territory->getName() == territoryName){
            return territory;
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
void Map::dfs_continent(vector<string> *visitedTerritoriesNames, Territory *currentTerritory,
                        Continent* currentContinent) {

    // Need to remove adjacent territories that aren't in the current continent
    vector<Territory*> currentAdjacentTerritoriesInContinent;
    for(int i = 0 ;i < currentTerritory->getAdjacentTerritories().size(); i++){
        if(currentTerritory->getAdjacentTerritories().at(i)->getContinent() == currentContinent){
            currentAdjacentTerritoriesInContinent.push_back(currentTerritory->getAdjacentTerritories().at(i));
        }
    }

    // Base case: if current territory has already been visited, return
    if(std::find(visitedTerritoriesNames->begin(), visitedTerritoriesNames->end(), currentTerritory->getName()) != visitedTerritoriesNames->end()){
        return;
    }

    cout << "visiting territory: " << currentTerritory->getName() << std::endl;
    // Add current territory to visited territories
    visitedTerritoriesNames->push_back(currentTerritory->getName());

    for(int i = 0; i < currentAdjacentTerritoriesInContinent.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs_continent(visitedTerritoriesNames, currentAdjacentTerritoriesInContinent.at(i), currentContinent);
    }
}

// Check if Map's continents are connected subgraphs
bool Map::isConnectedContinents() {

    for (int i = 0; i < allContinents.size(); i++){
        Continent* currentContinent = allContinents.at(i);
        vector<Territory*> currentContinentTerritories = getAllTerritoriesByContinent(currentContinent);
        vector<string> visitedTerritories;
        Territory* startTerritory = currentContinentTerritories.at(0);

        // Start DFS at first territory
        dfs_continent(&visitedTerritories, startTerritory, currentContinent);

        // If number of visited territories is not equal to the number of territories of a given continent, it is not a connected subgraph
        if (visitedTerritories.size() != currentContinentTerritories.size()){
            cout << "Continents are not connected subgraphs!" << endl;
            return false;
        }
    }
    cout << "Continents are connected subgraphs!" << endl;
    return true;
}

/*
 * Does the following checks:
 * 1) Map is a connected graph
 * 2) Continents of the map are connected subgraphs
 * 3) Each territory belongs to one and only one continent (this is not explicitly checked since Territories have been
 *      designed to only be possible to belong to one continent)
 * */
bool Map::validate() {
    return isConnectedTerritories() && isConnectedContinents();
}

/*
 * MAPLOADER
 * */

MapLoader::MapLoader() {
    map = new Map();
}

MapLoader::~MapLoader() {
    delete map;
}

MapLoader::MapLoader(const MapLoader &m) {
    this->map = m.map;
}

void MapLoader::readMapFile(std::string filepath) {

    const char continentDelimiter = '=';
    const char territoryDelimiter = ',';

    vector <Continent*> createdContinents;
    vector <Territory*> createdTerritories;

    ifstream input;

    input.open(filepath);
    if (!input) {
        cout << "ERROR: File does not exist";
    }
    else {
        if (input.peek() == std::ifstream::traits_type::eof()) {
            cout << "ERROR: File is empty";
        }
        else {

            // First time reading the file: Create the Continents and Territories (without associating its adjacent territories)
            string currentLine;
            while (getline(input, currentLine)) {

                if (currentLine == "[Continents]") {
                    while (getline(input, currentLine)) {
                        if (currentLine.length() == 0) {
                            break;
                        } else {

                            std::size_t continentDelimiterIndex = currentLine.find(continentDelimiter);
                            string continentName = currentLine.substr(0, continentDelimiterIndex);
                            int continentBonus = std::stoi(
                                    currentLine.substr(continentDelimiterIndex + 1, currentLine.length()));

                            Continent *continent = new Continent(continentName, continentBonus);
                            createdContinents.push_back(continent);

                        }
                    }
                    map->setAllContinents(createdContinents);
                }
                else if (currentLine == "[Territories]") {
                    while (getline(input, currentLine)) {
                        if (currentLine.length() > 0) {

                            // Create all Territories without taking into account their adjacent territories since those may
                            // not have been created yet.

                            // Split each line by delimiter and store the strings in a vector.
                            std::stringstream lineToSplit(currentLine);
                            string segment;
                            vector<string> splitStrings;
                            while (getline(lineToSplit, segment, territoryDelimiter)) {
                                splitStrings.push_back(segment);
                            }
                            // Format of the map file is as follows for Territories:
                            // (1) Name, (2) X-coordinate, (3) Y-coordinate, (4) Continent, ...[adjacent territories]
                            string territoryName = splitStrings.at(0);
                            int territoryX = stoi(splitStrings.at(1));
                            int territoryY = stoi(splitStrings.at(2));
                            string territoryContinentName = splitStrings.at(3);

                            Continent *territoryContinent = map->getContinentByName(territoryContinentName);
                            Territory *territory = new Territory(territoryName, territoryX, territoryY,territoryContinent);
                            createdTerritories.push_back(territory);

                        }
                    }
                    map->setAllTerritories(createdTerritories);
                }
            }
            if (createdTerritories.size() == 0 || createdContinents.size() == 0){
                cout << "ERROR: Missing section in file." << endl;
            }
            else{
                // Second time reading file: Add the adjacent territories for each Territory

                // Reset the stream cursor to point to beginning of file
                input.clear();
                input.seekg(0);

                while (getline(input, currentLine)) {
                    if (currentLine == "[Territories]") {
                        while (getline(input, currentLine)) {
                            if (currentLine.length() > 0) {

                                // Split each line by delimiter and store the strings in a vector.
                                std::stringstream lineToSplit(currentLine);
                                string segment;
                                vector<string> splitStrings;
                                while (getline(lineToSplit, segment, territoryDelimiter)) {
                                    splitStrings.push_back(segment);
                                }

                                // Format of the map file is as follows for Territories:
                                // (1) Name, (2) X-coordinate, (3) Y-coordinate, (4) Continent, ...[adjacent territories]

                                // Check if current territory has adjacent territories
                                if (splitStrings.size() > 4) {

                                    // Start from index 4 to obtain adjacent territories
                                    int adjacentTerritoryIndex{4};
                                    string currentTerritoryName = splitStrings.at(0);
                                    Territory *currentTerritory = map->getTerritoryByName(currentTerritoryName);

                                    for (int i = adjacentTerritoryIndex; i < splitStrings.size(); i++) {
                                        Territory *adjacentTerritory = map->getTerritoryByName(splitStrings.at(i));
                                        currentTerritory->addAdjacentTerritory(adjacentTerritory);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        input.close();
    }

}



int main(){

    MapLoader m;
    m.readMapFile("../map_files/canada_valid.map");
    Map* map = m.getMap();
    cout << map->validate();

//    Continent* c1 = new Continent(1, "continent1", 5);
//    Continent* c2 = new Continent(2, "continent2", 5);
//
//    cout << *c1;
//    cout << *c2;
//
//    Territory* t1 = new Territory(1,"territory1", 2, 3);
//    Territory* t2 = new Territory(2,"territory2", 2, 3);
//    Territory* t3 = new Territory(3,"territory3", 2, 3);
//    Territory* t4 = new Territory(4,"territory4", 2, 3);
//    Territory* t5 = new Territory(5,"territory5", 2, 3);
//
//    t1->setContinent(c1);
//    t2->setContinent(c1);
//    t3->setContinent(c2);
//    t4->setContinent(c2);
//    t5->setContinent(c2);
//
//    t1->addAdjacentTerritory(t3);
//    t1->addAdjacentTerritory(t2);
//
//    t2->addAdjacentTerritory(t3);
//    t2->addAdjacentTerritory(t1);
//
//
//    t3->addAdjacentTerritory(t1);
//    t3->addAdjacentTerritory(t2);
//    t3->addAdjacentTerritory(t4);
//
//    t4->addAdjacentTerritory(t3);
//    t4->addAdjacentTerritory(t5);
//
//    t5->addAdjacentTerritory(t4);
//
//    Map map;
//    map.addTerritory(t1);
//    map.addTerritory(t2);
//    map.addTerritory(t3);
//    map.addTerritory(t4);
//    map.addTerritory(t5);
//
//    map.addContinent(c1);
//    map.addContinent(c2);
//
//
//
//    bool x = map.isConnectedTerritories();
//    cout << "connected territories?:" << x << endl;
//
//    Continent* cont1 = map.getContinentById(1);
//    vector<Territory*> t = map.getAllTerritoriesByContinent(cont1);
//
//    Continent* cont2 = map.getContinentById(2);
//    vector<Territory*> tt = map.getAllTerritoriesByContinent(cont2);
//
//    bool y = map.isConnectedContinents();
//    cout << "connected continents?:" << y << endl;
//
//    cout << map;
//
//    bool mapIsvalidated = map.validate();
//    cout << "Is the map validated?: " << mapIsvalidated;
//
//    delete c1;
//    delete c2;
//
//    delete t1;
//    delete t2;
//    delete t3;
//    delete t4;
//    delete t5;



}