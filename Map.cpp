#include "Map.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::getline;

/*
 * CONTINENT
 */

/**
 * Stream insertion operator overloading
 * @param strm
 * @param c
 * @return ostream&
 */
ostream& operator<<(ostream &strm, const Continent &c){
    return strm << "CONTINENT: Name:" << c.name << " - Bonus:" << c.bonus << endl;
}

/**
 * Default constructor
 */
Continent::Continent() {
    name = "";
    bonus = 0;
}

/**
 * Copy constructor
 * @param c
 */
Continent::Continent(const Continent &c) {
    name = c.name;
    bonus = c.bonus;
}

/**
 * Assignment operator overloading
 * @param c
 * @return
 */
Continent& Continent::operator=(const Continent &c) {
    this->name = c.name;
    this->bonus = c.bonus;
    return *this;
}

Continent::Continent(string name, int bonus) {
    this->name = name;
    this->bonus = bonus;
}

string Continent::getName() {
    return name;
}

int Continent::getBonus() {
    return bonus;
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

/**
 * Overloading stream insertion operator
 * @param strm
 * @param t
 * @return
 */
ostream& operator<<(ostream &strm, const Territory &t){
    return strm << "TERRITORY: Name:" << t.name << " - Continent:" << t.continent->getName() << endl;
}
Territory::Territory() {
    owner = nullptr;
    continent = nullptr;
    numOfArmies = 0;
    tempNumOfArmies = 0;
    name = "";
    x = 0;
    y = 0;
}

/**
 * Copy constructor (shallow because making a deep copy would lead to an infinite copy operation)
 * @param t
 */
Territory::Territory(const Territory &t) {
    owner = t.owner;
    numOfArmies = t.numOfArmies;
    tempNumOfArmies = t.tempNumOfArmies;
    name = t.name;
    x = t.x;
    y = t.y;
    for(auto territory:t.adjacentTerritories){
        adjacentTerritories.push_back(territory);
    }
}

/**
 * Overloading assignment operator
 * @param t
 * @return
 */
Territory& Territory::operator=(const Territory &t) {
    owner = t.owner;
    numOfArmies = t.numOfArmies;
    tempNumOfArmies = t.tempNumOfArmies;
    name = t.name;
    x = t.x;
    y = t.y;
    for(auto territory:t.adjacentTerritories){
        adjacentTerritories.push_back(territory);
    }
    return *this;
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
    this->tempNumOfArmies = numOfArmies;
    this->name = name;
    this->adjacentTerritories = adjacentTerritories;
    this->x = x;
    this->y = y;
}

Territory::Territory(Player *owner, Continent* continent, int numOfArmies, std::string name, int x, int y) {
    this->owner = owner;
    this->continent = continent;
    this->numOfArmies = numOfArmies;
    this->tempNumOfArmies = numOfArmies;
    this->name = name;
    this->x = x;
    this->y = y;
}

Player* Territory::getOwner() {
    return owner;
}

void Territory::setOwner(Player* player){
    this->owner = player;
}

Continent *Territory::getContinent() {
    return continent;
}

void Territory::setContinent(Continent* continent){
    this->continent = continent;
}

int Territory::getNumOfArmies() {
    return numOfArmies;
}

int Territory::getTempNumOfArmies() {
    return tempNumOfArmies;
}

void Territory::setNumOfArmies(int numOfArmies){
    this->numOfArmies = numOfArmies;
    this->tempNumOfArmies = numOfArmies;
}

void Territory::setTempNumOfArmies(int tempNumOfArmies) {
    this->tempNumOfArmies = tempNumOfArmies;
}

string Territory::getName() {
    return name;
}

/**
 * Checks if the provided territory is in the adjacentTerritory vector.
 * @param territory
 * @return Returns bool true if provided territory in adjacentTerritory vector.
 */
bool Territory::isAdjacentTerritory(Territory *territory) {
    if (adjacentTerritories.empty()) {
        return false;
    } else if (std::find(adjacentTerritories.begin(), adjacentTerritories.end(), territory)
    == adjacentTerritories.end()) {
        return false;
    }
    return true;
}

void Territory::setName(string name){
    this->name = name;
}

vector<Territory *> Territory::getAdjacentTerritories() {
    return adjacentTerritories;
}

void Territory::setAdjacentTerritories(vector<Territory*> territories){
    this->adjacentTerritories = territories;
}

int Territory::getX() {
    return x;
}

void Territory::setX(int x){
    this->x = x;
}

int Territory::getY() {
    return y;
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

/**
 * Overloading stream insertion operator
 * @param strm
 * @param m
 * @return
 */
ostream& operator<<(ostream &strm, const Map &m){
    return strm << "MAP: Number of territories:" << m.allTerritories.size() << " - Number of continents:" << m.allContinents.size() << endl;
}

Map::Map(){}

/**
 * Destructor for Map
 */
Map::~Map(){
    for(auto continent: allContinents){
        delete continent;
    }
    for(auto territory: allTerritories){
        delete territory;
    }
}

Map::Map(vector<Territory *> territories, vector<Continent *> continents) {
    this->allTerritories = territories;
    this->allContinents = continents;
}

/**
 * Copy constructor (shallow because making a deep copy would lead to an infinite copy operation)
 * @param map
 */
Map::Map(const Map &map) {
    for(auto territory:allTerritories){
        this->allTerritories.push_back(territory);
    }
    for(auto continent:allContinents){
        this->allContinents.push_back(continent);
    }

}

/**
 * Overloading assignment operator
 * @param m
 * @return
 */
Map& Map::operator=(const Map &m) {
    for(auto territory:allTerritories){
        this->allTerritories.push_back(territory);
    }
    for(auto continent:allContinents){
        this->allContinents.push_back(continent);
    }
    return *this;
}

vector<Territory *> Map::getAllTerritories() {
    return allTerritories;
}

void Map::setAllTerritories(vector<Territory *> territories) {
    this->allTerritories = territories;
}

vector<Continent *> Map::getAllContinents() {
    return allContinents;
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

/**
 * Depth-first search recursive algorithm to visit all adjacent territories to the current territory
 * @param visitedTerritoriesNames
 * @param currentTerritory
 */
void Map::dfs(vector<string> *visitedTerritoriesNames, Territory *currentTerritory) {

    vector<Territory*> currentAdjacentTerritories = currentTerritory->getAdjacentTerritories();

    // Base case: if current territory has already been visited, return
    if(std::find(visitedTerritoriesNames->begin(), visitedTerritoriesNames->end(), currentTerritory->getName()) != visitedTerritoriesNames->end()){
        return;
    }

    // Add current territory to visited territories
    visitedTerritoriesNames->push_back(currentTerritory->getName());

    for(int i = 0; i < currentAdjacentTerritories.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs(visitedTerritoriesNames, currentAdjacentTerritories.at(i));
    }
}

/**
 * Check if map is a connected graph
 * @return
 */
bool Map::isConnectedTerritories() {

    vector<string> visitedTerritoriesNames;
    bool isConnectedTerritories = false;

    // Perform DFS on every single node (Territory) until all territories are visited. This ensures that every possible
    // graph traversal is performed in the case that some edges are unidirectional
    for (auto startTerritory: allTerritories) {

        // start DFS at starting territory
        dfs(&visitedTerritoriesNames, startTerritory);

        // check if all territories have been visited after DFS
        if (visitedTerritoriesNames.size() == allTerritories.size()) {
            cout << "Territories form a connected graph!" << endl;
            isConnectedTerritories = true;
            break;
        }
        visitedTerritoriesNames.clear();

    }
    if(!isConnectedTerritories){
        cout << "Territories do not form a connected graph!" << endl;
    }

    return isConnectedTerritories;
}

vector<Territory*> Map::getAllTerritoriesByContinent(Continent* continent) {
    vector<Territory*> continentTerritories;
    for(int i = 0; i < allTerritories.size(); i++){
        if(allTerritories.at(i)->getContinent() == continent){
            continentTerritories.push_back(allTerritories.at(i));
        }
    }
    return continentTerritories;
}

/**
 * Depth-first search recursive algorithm to visit all adjacent territories to the current territory.
 * Slight variation in this algorithm since it does not take into account adjacent territories that are not part of
 * the currently searched Continent.
 * @param visitedTerritoriesNames
 * @param currentTerritory
 * @param currentContinent
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

    // Add current territory to visited territories
    visitedTerritoriesNames->push_back(currentTerritory->getName());

    for(int i = 0; i < currentAdjacentTerritoriesInContinent.size(); i++){
        // Recursive call to perform DFS for each adjacent territory
        dfs_continent(visitedTerritoriesNames, currentAdjacentTerritoriesInContinent.at(i), currentContinent);
    }
}

/**
 * Check if Map's continents are connected subgraphs
 * @return
 */
bool Map::isConnectedContinents() {

    // Create a map to store the connectivity of each Continent (initialize to false)
    map<string,bool> continentsConnectedMap;
    for(auto continent:allContinents){
        continentsConnectedMap.insert(pair<string,bool>(continent->getName(), false));
    }

    for (int i = 0; i < allContinents.size(); i++){
        Continent* currentContinent = allContinents.at(i);
        vector<Territory*> currentContinentTerritories = getAllTerritoriesByContinent(currentContinent);
        vector<string> visitedTerritories;

        // Perform DFS on every single node (Territory) until all territories of the continent are visited.
        // This ensures that every possible graph traversal is performed in the case that some edges are unidirectional
        for(auto startTerritory:currentContinentTerritories){

            // Start DFS at first territory
            dfs_continent(&visitedTerritories, startTerritory, currentContinent);

            // If number of visited territories is equal to the number of territories of a given continent, it is a connected subgraph
            if (visitedTerritories.size() == currentContinentTerritories.size()){
                continentsConnectedMap.find(currentContinent->getName())->second = true;
                break;
            }
            visitedTerritories.clear();
        }
    }

    for(auto continentsKeyValue:continentsConnectedMap){
        if(!continentsKeyValue.second){
            return false;
        }
    }

    cout << "All continents are connected subgraphs!" << endl;
    return true;
}

/**
 * Does the following checks:
 * 1) Map is a connected graph
 * 2) Continents of the map are connected subgraphs
 * 3) Each territory belongs to one and only one continent (this is not explicitly checked since Territories have been
 *      designed to only be possible to belong to one continent)
 * @return
 */
bool Map::validate() {
    cout << "*********** Validating Map... **********" << endl;
    bool connectedTerritories = isConnectedTerritories();
    bool connectedContinents = isConnectedContinents();
    if (connectedTerritories && connectedContinents){
        cout << "************* Map is Valid *************" << endl;
    }
    else{
        cout << "************ Map is Invalid ************" << endl;
    }
    return connectedTerritories && connectedContinents;
}

/*
 * MAPLOADER
 * */

MapLoader::MapLoader() {
}

/**
 * Helper function to get a Continent* from a vector of Continent*
 * @param continents
 * @param continentName
 * @return
 */
Continent* MapLoader::getContinentByNameFromSet(vector<Continent *> continents, std::string continentName) {
    for(auto continent: continents){
        if(continent->getName() == continentName){
            return continent;
        }
    }
}

/**
 * Helper function to get a Territory* from a vector of Territory*
 * @param territories
 * @param territoryName
 * @return
 */
Territory* MapLoader::getTerritoryByNameFromSet(vector<Territory *> territories, std::string territoryName) {
    for(auto territory:territories){
        if(territory->getName() == territoryName){
            return territory;
        }
    }
}

/**
 * Reads a .map file and creates a Map object. Includes file validation
 * @param filepath
 * @return
 */
Map* MapLoader::readMapFile(std::string filepath) {

    const char continentDelimiter = '=';
    const char territoryDelimiter = ',';

    vector <Continent*> createdContinents;
    vector <Territory*> createdTerritories;

    ifstream input;

    input.open(filepath);
    if (!input) {
        cout << "ERROR: File does not exist" << endl;
        return nullptr;
    }
    else {
        if (input.peek() == std::ifstream::traits_type::eof()) {
            cout << "ERROR: File is empty" << endl;
            return nullptr;
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

                            Continent *territoryContinent = getContinentByNameFromSet(createdContinents, territoryContinentName);
                            Territory *territory = new Territory(territoryName, territoryX, territoryY,territoryContinent);
                            createdTerritories.push_back(territory);

                        }
                    }
                }
            }
            if (createdTerritories.size() == 0 || createdContinents.size() == 0){
                cout << "ERROR: Missing section in file." << endl;
                input.close();
                return nullptr;
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
                                    Territory *currentTerritory = getTerritoryByNameFromSet(createdTerritories, currentTerritoryName);

                                    for (int i = adjacentTerritoryIndex; i < splitStrings.size(); i++) {
                                        Territory *adjacentTerritory = getTerritoryByNameFromSet(createdTerritories, splitStrings.at(i));
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
        return new Map(createdTerritories,createdContinents);

    }

}
