#include "MapDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "CommandProcessingDriver.h"
#include <string>
#include <vector>

#include <iostream>
using namespace std;

int main(int argc, char** argv){
    if(argc == 1){

//        testLoadMaps();
//        testPlayer();
//        testOrdersLists();
//        testCards();
//        testGameStates();
//        vector<int*> num;
//        for (int j=0; j < 6; j++){
//
//            num.push_back(new int(j));
//            cout << *num.at(j);
//        }
//
//        srand(time(NULL));
//
//        for (int j=0; j < 12; j++){
//            int playerSwap1 = (rand() % 6);
//            int playerSwap2 = (rand() % 6);
//            cout << endl << playerSwap1 << endl;
//            cout << playerSwap2 << endl;
//
//            num.emplace_back(num.at(playerSwap1));
//            num.erase(num.begin()+playerSwap1,num.begin()+playerSwap1+1);
//
//
//            for (int j=0; j < 6; j++){
//                cout << *num.at(j);
//            }
//
//        }
//        testCommandProcessor();

        int x = 20;
        int y = 3;
        cout << x/y ;

        }
        else{
            if(string(argv[1]) == "-console"){
                testCommandProcessorConsole();
            }
            else if(string(argv[1]) == "-file"){
                testCommandProcessorFile(string(argv[2]));
            }
        }


        return 0;
}
