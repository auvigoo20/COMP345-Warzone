#include "LoggingObserver.h"
#include <list>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::list;
using std::ios;


Observer::Observer() {}

Observer::~Observer() {}

Subject::Subject() {
    observers = new list<Observer*>;
}

Subject::~Subject() {
    delete observers;
    observers = nullptr;
}

void Subject::attach(Observer *o) {
    observers->push_back(o);
}

void Subject::detach(Observer *o) {
    observers->remove(o);
}

void Subject::notify(ILoggable *il) {
    list<Observer*>::iterator i = observers->begin();
    for(; i != observers->end(); ++i){
        (*i)->update(il);
    }
}

void LogObserver::update(ILoggable* il) {
    const string logfile = "../gamelog.txt";
    string s = il->stringToLog();
    std::ofstream file;
    file.open(logfile, ios::app);
    if(file.is_open()){
        file << s << std::endl;
        file.close();
    }
    else{
        std::cout << "ERROR: gamelog.txt cannot be opened." << std::endl;
    }



}