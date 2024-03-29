#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

int testGameStates(){

    cout << "****************************************" << endl;
    cout << "*          Testing Game Engine         *" << endl;
    cout << "****************************************" << endl;

    bool done = false;
    GameEngine testGameEngine {GameEngine::start};
    Command* latestCommand;

    cout << testGameEngine << endl;

    while(!done) {
        bool invalidCommand = true;

        latestCommand->getCommand();

        testGameEngine.setLatestCommand(latestCommand);

        for (int i=0; i < testGameEngine.getCurrentState()->getTransitions().size(); i++) {
            if (testGameEngine.getCurrentState()->getTransitions().at(i)->getName() == testGameEngine.getLatestCommand()->getCommand()) {
                if (testGameEngine.getCurrentState()->getTransitions().at(i)->getTo() == nullptr) {
                    invalidCommand = false;
                    done = true;
                    break;
                }
                testGameEngine.transition(testGameEngine.getCurrentState()->getTransitions().at(i)->getTo());
                cout << testGameEngine << endl;
                invalidCommand = false;
                break;
            }
        }

        if (invalidCommand) {
            cout << "Invalid command." << endl;
        }

        cout << endl;
    }

    cout << "Game ended." << endl;

    return 0;
}

int testStartupPhase(){
    cout << "****************************************" << endl;
    cout << "*         Testing Startup Phase        *" << endl;
    cout << "****************************************" << endl;

    GameEngine* ge = new GameEngine();
    CommandProcessor* commandProcessor = new CommandProcessor();
    ge->setCommandProcessor(commandProcessor);
    commandProcessor->setGameEngine(ge);
    ge->startupPhase();

    return 0;
}

int testMainGameLoop() {
    cout << "****************************************" << endl;
    cout << "*        Testing Main Game Loop        *" << endl;
    cout << "****************************************" << endl;

    GameEngine* ge;

    Hand* hand1 = new Hand();
    Hand* hand2 = new Hand();
    Hand* hand3 = new Hand();

    OrdersList* ordersList1 = new OrdersList();
    OrdersList* ordersList2 = new OrdersList();
    OrdersList* ordersList3 = new OrdersList();

    Player* player1 = new Player("Player1", hand1, ordersList1, 10);
    Player* player2 = new Player("Player2", hand2, ordersList2, 10);
    Player* player3 = new Player("Player3", hand3, ordersList3, 10);
    vector<Player*> players = {player1, player2, player3};

    hand1->setOwner(player1);
    hand2->setOwner(player2);
    hand3->setOwner(player3);

    Continent* continent =  new Continent("continent1", 5);
    Territory* ownedTerritory1 = new Territory("ownedTerritory1", 1, 1, continent);
    Territory* enemyTerritory1 = new Territory("enemyTerritory1", 1, 2, continent);
    Territory* enemyTerritory2 = new Territory("enemyTerritory1", 1, 2, continent);
    Territory* alliedAdjacentTer = new Territory("alliedAdjacentTer", 2, 1, continent);

    Continent* continent2 = new Continent("continent2", 5);
    Territory* loneTerritory = new Territory("loneTerritory", 1, 1, continent2);

    player1->addTerritory(ownedTerritory1);
    player1->addTerritory(alliedAdjacentTer);
    player1->addTerritory(loneTerritory);
    player2->addTerritory(enemyTerritory1);
    player3->addTerritory(enemyTerritory2);

    ownedTerritory1->addAdjacentTerritory(enemyTerritory1);
    ownedTerritory1->addAdjacentTerritory(enemyTerritory2);
    ownedTerritory1->addAdjacentTerritory(alliedAdjacentTer);
    ownedTerritory1->addAdjacentTerritory(loneTerritory);

    vector<Territory*> territories = {ownedTerritory1, enemyTerritory1, enemyTerritory2, alliedAdjacentTer, loneTerritory};
    vector<Continent*> continents = {continent, continent2};
    Map* map = new Map(territories, continents);

    Deck* deck = new Deck();

    for (int i = 0; i < players.size(); i++) {
        deck->addCard(new BombCard);
        deck->addCard(new BlockadeCard);
        deck->addCard(new AirliftCard);
        deck->addCard(new DiplomacyCard);
    }

    State* startingState = GameEngine::assignReinforcement;

    ge = new GameEngine(startingState, players, map);

    CommandProcessor* commandProcessor = new CommandProcessor();
    ge->setCommandProcessor(commandProcessor);
    commandProcessor->setGameEngine(ge);

    ge->setDeck(deck);

    hand1->setDeckList(ge->getDeck());
    hand2->setDeckList(ge->getDeck());
    hand3->setDeckList(ge->getDeck());

    ge->mainGameLoop(0, false);

    return 0;
}