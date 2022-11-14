#include "LoggingObserver.h"
#include <list>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::list;
using std::ios;
using std::endl;

ILoggable::~ILoggable() {}

ostream& operator<<(ostream &strm, const ILoggable &il){
    return strm << "ILoggable" << endl;
}

Observer::Observer() {}

Observer::~Observer() {}

ostream& operator<<(ostream &strm, const Observer &o){
    return strm << "Observer" << endl;
}

Subject::Subject() {
    observers = new list<Observer*>;
}

Subject::~Subject() {
    delete observers;
    observers = nullptr;
}

Subject::Subject(const Subject &s) {
    this->observers = s.observers;
}

Subject &Subject::operator=(const Subject &s) {
    this->observers = s.observers;
    return *this;
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

ostream& operator<<(ostream &strm, const Subject &s){
    return strm << "Number of observers attached to this subject: " << s.observers->size() << endl;
}

LogObserver::LogObserver() {}

void LogObserver::update(ILoggable* il) {
    const string logfile = "../gamelog.txt";
    string s = il->stringToLog();
    std::ofstream file;
    // Open the gamelog file in "append" mode
    file.open(logfile, ios::app);
    if(file.is_open()){
        file << s << std::endl;
        file.close();
    }
    else{
        std::cout << "ERROR: gamelog.txt cannot be opened." << std::endl;
    }
}

ostream& operator<<(ostream &strm, const LogObserver &lo){
    return strm << "LogObserver" << endl;
}
