#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::cout;
using std::cin;


Command::Command() {}

Command::Command(string command): command(command){}

void Command::saveEffect(string effect) {
    this->effect = effect;
}

string Command::getCommand() {
    return command;
}

CommandProcessor::CommandProcessor() {}

CommandProcessor::CommandProcessor(GameEngine* gameEngine): gameEngine(gameEngine) {}

string CommandProcessor::readCommand() {
    string command;
    cin >> command;
    return command;
}

void CommandProcessor::saveCommand(Command *command) {
    this->commands.push_back(command);
}

Command* CommandProcessor::getCommand() {
    string userCommand = readCommand();
    Command* command = new Command(userCommand);
    saveCommand(command);
    return command;
}

bool CommandProcessor::validate(Command* command) {
    string currentState = gameEngine->getCurrentState()->getName();
    bool commandIsValid = false;

    if(command->getCommand().find("loadmap") != string::npos){
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

        if(currentState == "start" || currentState == "map loaded"){
            commandIsValid = true;
        }
    }
    else if(command->getCommand() == "validatemap" && currentState == "map loaded"){
        commandIsValid = true;
    }
    else if (command->getCommand().find("addplayer") != string::npos){
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

        if(currentState == "map validated" || currentState == "players added"){
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
        command->saveEffect("Invalid command in current state.");
    }

    return commandIsValid;


}

