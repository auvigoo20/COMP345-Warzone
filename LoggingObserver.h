#pragma once
#include <string>
#include <list>
#include <iostream>
using std::string;
using std::list;
using std::ostream;

class ILoggable{
    public:
        virtual ~ILoggable();
        virtual string stringToLog() = 0;
};
ostream& operator<<(ostream &strm, const ILoggable &il);

class Observer{
    public:
        virtual ~Observer();
        virtual void update(ILoggable*) = 0;
    protected:
        Observer();
};

ostream& operator<<(ostream &strm, const Observer &o);

class Subject{
    public:
        virtual void attach(Observer* o);
        virtual void detach(Observer* o);
        virtual void notify(ILoggable* il);
        Subject();
        ~Subject();
        Subject(const Subject &s);
        Subject& operator =(const Subject& s);

private:
        list<Observer*>* observers;
        friend ostream& operator<<(ostream&, const Subject&);
};

ostream& operator<<(ostream &strm, const Subject &s);

class LogObserver: public Observer{
    public:
        LogObserver();
        void update(ILoggable*);
};
ostream& operator<<(ostream &strm, const LogObserver &lo);
