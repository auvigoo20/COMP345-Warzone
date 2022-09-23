#include <string>
#include <vector>
using std::string;
using std::vector;

class Continent{

};

class Player;

class Territory{
    private:
        Player* owner;
        Continent* continent;
        int numOfArmies;
        string name;
        vector<Territory*> adjacentTerritories;
        int x, y;

    public:
        Territory();
        Territory(const Territory &t);
        Territory(string name, int x, int y);
        Territory(Player* owner, Continent* continent, int numOfArmies, string name, vector<Territory*>, int x, int y);
        Territory(Player *owner, Continent* continent, int numOfArmies, string name, int x, int y);
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
        void dfs(vector<string>* visitedTerritories, Territory* currentTerritory);

    public:
        Map();
        Map(const Map &map);

        vector<Territory*> getAllTerritories() { return allTerritories; }
        vector<Continent*> getAllContinents() { return allContinents; }
        void setAllTerritories(vector<Territory*> territories);
        void setAllContinents(vector<Continent*> continents);

        void addTerritory(Territory* t);
        void addContinent(Continent* c);
        bool isConnectedTerritories();
        bool isConnectedContinents();
        bool validate();




};