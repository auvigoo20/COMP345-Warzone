#pragma once
#include "GameEngine.h"

class Command{
    private:
        string command;
        string effect;
    public:
        Command();
        Command(string command);
        void saveEffect(string effect);

};

class CommandProcessor{
    private:
        vector<Command*> commands;
        GameEngine* gameEngine;
        string readCommand();
        void saveCommand(Command* command);
    public:
        CommandProcessor();
        CommandProcessor(GameEngine*);
        Command* getCommand();
        bool validate(Command*);


};