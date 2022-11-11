#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <sstream>

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

string CommandProcessor::readCommand() {
    string command;
    getline(cin, command);
    return command;
}

void CommandProcessor::saveCommand(Command *command) {
    this->commands.push_back(command);
}

Command* CommandProcessor::getCommand() {
    cout << "Enter a command: " << endl;
    string userCommand = readCommand();
    Command* command = new Command(userCommand);
    saveCommand(command);
    return command;
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
    else{
        command->saveEffect("Invalid command.");
    }

    return commandIsValid;
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




