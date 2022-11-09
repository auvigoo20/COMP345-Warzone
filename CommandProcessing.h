#pragma once
#include "GameEngine.h"

class Command{
    private:
        string command;
        string effect;
        friend ostream& operator<<(ostream&, const Command&);
public:
        Command();
        Command(string command);
        string getCommand();
        string getEffect();
        void saveEffect(string effect);
};

ostream& operator<<(ostream &strm, const Command &c);


class CommandProcessor{
    private:
        vector<Command*> commands;
        GameEngine* gameEngine;
        string readCommand();
        void saveCommand(Command* command);
        friend ostream& operator<<(ostream&, const CommandProcessor&);
public:
        CommandProcessor();
        CommandProcessor(GameEngine*);
        ~CommandProcessor();
        Command* getCommand();
        bool validate(Command*);
};