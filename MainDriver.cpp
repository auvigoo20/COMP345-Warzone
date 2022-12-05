#include "PlayerStrategiesDriver.h"
#include "TournamentDriver.h"
#include <string>
using std::string;

int main(int argc, char** argv){
    if(argc == 1){
        testPlayerStrategies();
        testTournament();
    }
    else{
        if(string(argv[1]) == "-console"){
            testTournament();
        }
        else if(string(argv[1]) == "-file"){
            testTournamentFile(string(argv[2]));
        }
    }

    return 0;
}
