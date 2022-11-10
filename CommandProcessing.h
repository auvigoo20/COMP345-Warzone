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
        Command(const Command &c);
        Command& operator =(const Command& c);
        string getCommand();
        string getEffect();
        void saveEffect(string effect);
};

ostream& operator<<(ostream &strm, const Command &c);


class CommandProcessor{
    private:
    GameEngine* gameEngine;
        virtual string readCommand();
        void saveCommand(Command* command);
        friend ostream& operator<<(ostream&, const CommandProcessor&);

protected:
    vector<Command*> commands;
public:
        CommandProcessor();
        CommandProcessor(GameEngine*);
        CommandProcessor(const CommandProcessor& c);
        ~CommandProcessor();
        CommandProcessor& operator=(const CommandProcessor& c);
        Command* getCommand();
        bool validate(Command*);
};
ostream& operator<<(ostream &strm, const CommandProcessor &c);


class FileLineReader{
    private:
        ifstream input;
        string fileName;
        friend ostream& operator<<(ostream&, const FileLineReader&);
public:
        FileLineReader(string fileName);
        FileLineReader();
        ~FileLineReader();
        string readLineFromFile();
};
ostream& operator<<(ostream &strm, const FileLineReader &f);

class FileCommandProcessorAdapter: public CommandProcessor{
    private:
        FileLineReader* flr;
        string readCommand();
        friend ostream& operator<<(ostream&, const FileCommandProcessorAdapter&);
public:
        FileCommandProcessorAdapter(GameEngine* gameEngine, string fileName);
        FileCommandProcessorAdapter();
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &f);
        ~FileCommandProcessorAdapter();
        FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& f);

};
ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &c);

