#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;


Command::Command() {}

Command::Command(string command): command(command){}

/**
 * Copy constructor
 * @param c
 */
Command::Command(const Command &c) {
    this->command = c.command;
    this->effect = c.effect;
}

/**
 * Overloading assignment operator
 * @param c
 * @return
 */
Command& Command::operator=(const Command &c) {
    this->command = c.command;
    this->effect = c.effect;
    return *this;
}

string Command::getCommand() {
    return command;
}

string Command::getEffect() {
    return effect;
}

void Command::saveEffect(string effect) {
    this->effect = effect;
    notify(this);   //notify the observer of the state change
}

string Command::stringToLog() {
    return "Command's effect: " + effect;
}

/**
 * Overloading stream insertion operator
 * @param strm
 * @param c
 * @return
 */
ostream& operator<<(ostream &strm, const Command &c){
    return strm << "Command: " << c.command << endl << "Effect: " << c.effect << endl;
}


CommandProcessor::CommandProcessor() {}

CommandProcessor::CommandProcessor(GameEngine* gameEngine): gameEngine(gameEngine) {}

/**
 * Copy constructor that creates deep copies of Command objects
 * @param c
 */
CommandProcessor::CommandProcessor(const CommandProcessor &c) {
    for(auto cmd: c.commands){
        this->commands.push_back(new Command(*cmd));
    }
}

CommandProcessor::~CommandProcessor() {
    for(auto cmd:commands){
        delete cmd;
        cmd = nullptr;
    }
}

/**
 * Overloading assignment operator
 * @param c
 * @return
 */
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &c) {
    for(auto cmd: c.commands){
        this->commands.push_back(new Command(*cmd));
    }
    return *this;
}

void CommandProcessor::setGameEngine(GameEngine *ge) {
    this->gameEngine = ge;
}

GameEngine *CommandProcessor::getGameEngine() {
    return gameEngine;
}

string CommandProcessor::readCommand() {
    string command;
    getline(cin, command);
    return command;
}

void CommandProcessor::saveCommand(Command *command) {
    this->commands.push_back(command);
    notify(this);   // notify the observer of the state change
}

Command* CommandProcessor::getCommand() {
    cout << "Enter a command: " << endl;
    string userCommand = readCommand();
    cout << endl;
    Command* command = new Command(userCommand);
    saveCommand(command);
    return command;
}

bool CommandProcessor::validateTournamentCommand(Command* command) {

    // if validating another tournament command, or replaying another tournament, reset GameEngine fields
    if(gameEngine->getTournamentMapFiles().size() != 0){
        vector<string> emptyStringVector;
        gameEngine->setTournamentMapFiles(emptyStringVector);
    }
    if(gameEngine->getTournamentPlayerStrategies().size() != 0){
        vector<string> emptyStringVector;
        gameEngine->setTournamentPlayerStrategies(emptyStringVector);
    }
    if(gameEngine->getTournamentNumOfGames() != 0){
        gameEngine->setTournamentNumOfGames(0);
    }
    if(gameEngine->getTournamentMaxNumOfTurns() != 0){
        gameEngine->setTournamentMaxNumOfTurns(0);
    }

    // Split each line by delimiter (" ") and store the strings in a vector.
    // tournament command format is:
    // tournament -M <listofmapfiles>(1-5) -P <listofplayerstrategies>(2-4) -G <numberofgames>(1-5) -D <maxnumberofturns>(10-50)
    std::stringstream commandToSplit(command->getCommand());
    string segment;
    vector<string> splitCommand;
    while (getline(commandToSplit, segment, ' ')) {
        splitCommand.push_back(segment);
    }
    if(splitCommand.size() < 9){
        command->saveEffect("Invalid amount of arguments passed for tournament mode.");
        return false;
    }

    int currentIndex = 1;
    // Validate -M part
    int numOfMaps = 0;
    while(splitCommand.at(currentIndex) != "-P"){
        // Skip -M flag
        if(splitCommand.at(currentIndex) == "-M"){
            currentIndex++;
            continue;
        }

        if(numOfMaps >= 5){
            command->saveEffect("Invalid amount of maps passed for tournament mode.");
            return false;
        }
        gameEngine->addTournamentMapFile(splitCommand.at(currentIndex));
        numOfMaps++;
        currentIndex++;
    }
    if(numOfMaps < 1){
        command->saveEffect("Invalid amount of maps passed for tournament mode.");
        return false;
    }

    // Validate -P part
    int numOfPlayerStrategies = 0;
    vector<string> possibleStrategies{"aggressive", "benevolent", "neutral", "cheater"};
    while (splitCommand.at(currentIndex) != "-G"){
        // Skip -P flag
        if(splitCommand.at(currentIndex) == "-P"){
            currentIndex++;
            continue;
        }
        if(numOfPlayerStrategies >= 4){
            command->saveEffect("Invalid amount of player strategies passed for tournament mode.");
            return false;
        }
        // If the player strategy does not correspond to the predefined strategies
        if(std::find(possibleStrategies.begin(), possibleStrategies.end(), splitCommand.at(currentIndex)) == possibleStrategies.end()){
            command->saveEffect("Invalid player strategy passed for tournament mode.");
            return false;
        }
        gameEngine->addTournamentPlayerStrategy(splitCommand.at(currentIndex));
        numOfPlayerStrategies++;
        currentIndex++;
    }
    if(numOfPlayerStrategies < 2 || numOfPlayerStrategies > 4){
        command->saveEffect("Invalid amount of player strategies passed for tournament mode.");
        return false;
    }

    // Validate -G part
    while(splitCommand.at(currentIndex) != "-D"){
        // Skip -G flag
        if(splitCommand.at(currentIndex) == "-G"){
            currentIndex++;
            continue;
        }
        int numOfGames = std::stoi(splitCommand.at(currentIndex));
        if(numOfGames < 1 || numOfGames > 5){
            command->saveEffect("Invalid number of games for tournament mode.");
            return false;
        }
        gameEngine->setTournamentNumOfGames(numOfGames);
        currentIndex++;
    }

    // Validate -D part
    while(currentIndex < splitCommand.size()){
        // Skip -D flag
        if(splitCommand.at(currentIndex) == "-D"){
            currentIndex++;
            continue;
        }
        int numOfTurns = std::stoi(splitCommand.at(currentIndex));
        if(numOfTurns < 10 || numOfTurns > 50){
            command->saveEffect("Invalid number of maximum turns for tournament mode.");
            return false;
        }
        gameEngine->setTournamentMaxNumOfTurns(numOfTurns);
        currentIndex++;
    }
    return true;

}

bool CommandProcessor::validate(Command* command) {
    string currentState = gameEngine->getCurrentState()->getName();
    bool commandIsValid = false;

    if(command->getCommand().find("loadmap") != string::npos && (currentState == "start" || currentState == "map loaded")){
        // Check if command is followed by a file name
        // Split each line by delimiter and store the strings in a vector.
        std::stringstream commandToSplit(command->getCommand());
        string segment;
        vector<string> splitCommand;
        while (getline(commandToSplit, segment, ' ')) {
            splitCommand.push_back(segment);
        }
        if(splitCommand.size() != 2){
            command->saveEffect("Invalid command due to invalid number of arguments.");
        }
        else{
            commandIsValid = true;
        }
    }
    else if(command->getCommand() == "validatemap" && currentState == "map loaded"){
        commandIsValid = true;
    }
    else if (command->getCommand().find("addplayer") != string::npos && (currentState == "map validated" || currentState == "players added")){
        // Check if command is followed by a player name
        // Split each line by delimiter and store the strings in a vector.
        std::stringstream commandToSplit(command->getCommand());
        string segment;
        vector<string> splitCommand;
        while (getline(commandToSplit, segment, ' ')) {
            splitCommand.push_back(segment);
        }
        if(splitCommand.size() != 2){
            command->saveEffect("Invalid command due to invalid number of arguments.");
        }
        else{
            commandIsValid = true;
        }
    }
    else if(command->getCommand() == "gamestart" && currentState == "players added"){
        commandIsValid = true;
    }
    else if((command->getCommand() == "replay" || command->getCommand() == "quit") && currentState == "win"){
        commandIsValid = true;
    }
    else if (command->getCommand().find("tournament") != string::npos && currentState == "start"){
        commandIsValid = validateTournamentCommand(command);
    }
    else{
        command->saveEffect("Invalid command.");
    }

    return commandIsValid;
}

string CommandProcessor::stringToLog() {
    // Return the last created command (whether it's valid or not)
    Command* lastCreatedCommand = commands.back();
    return "Command: " + lastCreatedCommand->getCommand();
}

/**
 * Overloading output stream operator
 * @param strm
 * @param c
 * @return
 */
ostream& operator<<(ostream &strm, const CommandProcessor &c){
    for(auto command : c.commands){
       strm << command->getCommand() << ": " << command->getEffect() << endl;
    }
    return strm;
}

FileLineReader::FileLineReader(string fileName) {
    this->fileName = fileName;
    input.open(fileName);
}

FileLineReader::FileLineReader() {}

FileLineReader::~FileLineReader() {
    input.close();
}

string FileLineReader::readLineFromFile() {
    if(!input){
        cout << "ERROR: FILE COULD NOT BE READ" << endl;
        exit(0);
    }
    string line;
    getline(input, line);
    return line;
}

/**
 * Overloading stream insertion operator
 * @param strm
 * @param f
 * @return
 */
ostream& operator<<(ostream &strm, const FileLineReader &f){
    return strm << "FileLineReader reading file: " << f.fileName << endl;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine *gameEngine, std::string fileName) : CommandProcessor(gameEngine){
    flr = new FileLineReader(fileName);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string fileName){
    flr = new FileLineReader(fileName);
}

/**
 * Copy constructor. Shallow copy to use the same file line reader to maintain current cursor position in file
 * @param f
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &f) {
    this->flr = f.flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = nullptr;
}

/**
 * Overloading assignment operator
 * @param f
 * @return
 */
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &f) {
    this->flr = f.flr;
    return *this;
}

string FileCommandProcessorAdapter::readCommand() {
    return flr->readLineFromFile();
}

/**
 * Overloading output stream operator
 * @param strm
 * @param f
 * @return
 */
ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &f){
    for(auto command : f.commands){
        strm << command->getCommand() << ": " << command->getEffect() << endl;
    }
    return strm;
}




