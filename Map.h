#include <string>
#include <vector>
using std::string;
using std::vector;

class Map{

};

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
        Territory(Territory &t);
        Territory(Player* owner, Continent* continent, int numOfArmies, string name, vector<Territory*>, int x, int y);

        Player* getOwner();
        Continent* getContinent();
        int getNumOfArmies();
        string getName();
        vector<Territory*> getAdjacentTerritories();
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