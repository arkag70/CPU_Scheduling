#ifndef TASK_HPP
#define TASK_HPP

#include<bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;

enum process_states{
    NEW = 0,
    READY,
    RUNNING,
    IO,
    TERMINATED,
    SUSPENDED_READY,
    SUSPENDED_WAIT
};

/*  Base class Task */
class Task{

private:
    int priority;
    int state;
    string name;
    pair<int, int> range;

public:
    Task(int prio, pair<int, int> r, int s = NEW):priority{prio}, range{r}{
        name = "Counting from " + to_string(range.first) + " to " + to_string(range.second);
        state = NEW;
    }
    virtual int getState() = 0;
    virtual int getPrio() = 0;
    virtual void setState(int) = 0;
    virtual string getName() = 0;
    virtual void show() = 0;
    virtual bool operator<(Task& rhs) = 0;
    virtual void prepare() = 0;

};

/*  Sub class : specific task to count numbers */
class countNumbers : public Task{

private:
    int priority;
    pair<int, int> range;
    string name;
    int state;
    long processID;
    struct mesg_buffer{
        long mesg_type;
        char status;
        long pid;
    };
    mesg_buffer message;

public:
    countNumbers(int prio, pair<int, int> r);
    virtual int getState();
    virtual int getPrio();
    virtual void setState(int);
    virtual string getName();
    virtual void show();
    virtual bool operator<(Task& rhs);
    virtual void prepare();

};

/*  Sub class : specific task to count numbers */
class countAlphabets : public Task{

private:
    int priority;
    pair<char, char> range;
    string name;
    int state;
    long processID;
    struct mesg_buffer{
        long mesg_type;
        char status;
        long pid;
    };
    mesg_buffer message;

public:
    countAlphabets(int prio, pair<char, char> r);
    virtual int getState();
    virtual int getPrio();
    virtual void setState(int);
    virtual string getName();
    virtual void show();
    virtual bool operator<(Task& rhs);
    virtual void prepare();
};
#endif
