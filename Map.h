#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;

// Forward declaration
class Player;

class Continent{
    private:
        friend ostream& operator<<(ostream&, const Continent&);
        string name;
        int bonus;
    public:
        Continent();
        Continent(const Continent &c);
        Continent(string name, int bonus);
        Continent& operator =(const Continent& c);
        string getName();
        int getBonus();
        void setName(string name);
        void setBonus(int bonus);

};

class Territory{
    private:
        friend ostream& operator<<(ostream&, const Territory&);
        Player* owner;
        Continent* continent;
        int numOfArmies;
        string name;
        vector<Territory*> adjacentTerritories;
        int x, y;

    public:
        Territory();
        Territory(const Territory &t);
        Territory(string name, int x, int y, Continent* continent);
        Territory(Player* owner, Continent* continent, int numOfArmies, string name, vector<Territory*>, int x, int y);
        Territory(Player *owner, Continent* continent, int numOfArmies, string name, int x, int y);
        Territory& operator=(const Territory& t);
        Player* getOwner();
        Continent* getContinent();
        int getNumOfArmies();
        string getName();
        vector<Territory*> getAdjacentTerritories();
        bool isAdjacentTerritory(Territory* territory);
        int getX();
        int getY();

        void setOwner(Player* player);
        void setContinent(Continent* continent);
        void setNumOfArmies(int numOfArmies);
        void setName(string name);
        void setAdjacentTerritories(vector<Territory*> territories);
        void setX(int x);
        void setY(int y);

        void addAdjacentTerritory(Territory* territory);
};

class Map{
    private:
        friend ostream& operator<<(ostream&, const Map&);
        vector <Territory*> allTerritories;
        vector <Continent*> allContinents;
        void dfs(vector<string>* visitedTerritoriesNames, Territory* currentTerritory);
        void dfs_continent(vector<string>* visitedTerritoriesNames, Territory* currentTerritory, Continent* currentContinent);

    public:
        Map();
        ~Map();
        Map(vector<Territory*> territories, vector<Continent*> continents);
        Map(const Map &map);
        Map& operator=(const Map &m);

        vector<Territory*> getAllTerritories();
        vector<Continent*> getAllContinents();
        vector<Territory*> getAllTerritoriesByContinent(Continent* continent);
        void setAllTerritories(vector<Territory*> territories);
        void setAllContinents(vector<Continent*> continents);

        void addTerritory(Territory* t);
        void addContinent(Continent* c);
        bool isConnectedTerritories();
        bool isConnectedContinents();
        bool validate();
};

class MapLoader{
    public:
        MapLoader();
        Map* readMapFile(string filepath);

    private:
        Continent* getContinentByNameFromSet(vector<Continent*> continents, string continentName);
        Territory* getTerritoryByNameFromSet(vector<Territory*> territories, string territoryName);

};