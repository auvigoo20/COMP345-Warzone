#pragma once
#include "GameEngine.h"
#include <iostream>
#include <fstream>
using std::ifstream;


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
        virtual string readCommand();
        void saveCommand(Command* command);
        friend ostream& operator<<(ostream&, const CommandProcessor&);
public:
        CommandProcessor();
        CommandProcessor(GameEngine*);
        ~CommandProcessor();
        Command* getCommand();
        bool validate(Command*);
};

class FileLineReader{
    private:
        ifstream input;
    public:
        FileLineReader(string fileName);
        FileLineReader();
        ~FileLineReader();
        string readLineFromFile();
};


class FileCommandProcessorAdapter: public CommandProcessor{
    private:
        FileLineReader* flr;
        string readCommand();
    public:
        FileCommandProcessorAdapter(GameEngine* gameEngine, string fileName);
        FileCommandProcessorAdapter();
        ~FileCommandProcessorAdapter();
};
