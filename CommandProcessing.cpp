#include "CommandProcessing.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

Command::Command() {}

Command::Command(string command): command(command){}

void Command::saveEffect(string effect) {
    this->effect = effect;
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

