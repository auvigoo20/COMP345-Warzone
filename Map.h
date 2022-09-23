#include <string>
#include <vector>
using std::string;
using std::vector;

class Continent{
    private:
        int id;
        string name;
        int bonus;
    public:
        Continent();
        Continent(const Continent &c);
        Continent(int id, string name, int bonus);
        int getID() { return id; }
        string getName() { return name; }
        int getBonus() { return bonus; }

};

class Player;

class Territory{
    private:
        int id;
        Player* owner;
        Continent* continent;
        int numOfArmies;
        string name;
        vector<Territory*> adjacentTerritories;
        int x, y;

    public:
        Territory();
        Territory(const Territory &t);
        Territory(int id, string name, int x, int y);
        Territory(int id, Player* owner, Continent* continent, int numOfArmies, string name, vector<Territory*>, int x, int y);
        Territory(int id, Player *owner, Continent* continent, int numOfArmies, string name, int x, int y);
        int getID() { return id; }
        Player* getOwner() { return owner; }
        Continent* getContinent() { return continent; }
        int getNumOfArmies() { return numOfArmies; }
        string getName() { return name; }
        vector<Territory*> getAdjacentTerritories() { return adjacentTerritories; }
        int getX() { return x; }
        int getY() { return y; }

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
        vector <Territory*> allTerritories;
        vector <Continent*> allContinents;
        void dfs(vector<int>* visitedTerritoriesIds, Territory* currentTerritory);
        void dfs_continent(vector<int>* visitedTerritoriesIds, Territory* currentTerritory, Continent* currentContinent);

    public:
        Map();
        Map(const Map &map);

        vector<Territory*> getAllTerritories() { return allTerritories; }
        vector<Continent*> getAllContinents() { return allContinents; }
        Continent* getContinentById(int continentID);
        vector<Territory*> getAllTerritoriesByContinent(Continent* continent);
        void setAllTerritories(vector<Territory*> territories);
        void setAllContinents(vector<Continent*> continents);

        void addTerritory(Territory* t);
        void addContinent(Continent* c);
        bool isConnectedTerritories();
        bool isConnectedContinents();
        bool validate();




};