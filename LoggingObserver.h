#pragma once
#include <string>
#include <list>
using std::string;
using std::list;

class ILoggable{
    public:
        virtual string stringToLog() = 0;
};

class Observer{
    public:
        ~Observer();
        virtual void update(ILoggable*) = 0;
    protected:
        Observer();
};

class Subject{
    public:
        virtual void attach(Observer* o);
        virtual void detach(Observer* o);
        virtual void notify(ILoggable* il);
        Subject();
        ~Subject();
    private:
        list<Observer*>* observers;
};

class LogObserver: public Observer{
    public:
        void update(ILoggable*);
};