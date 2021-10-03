#include "Task.hpp"
#include <unistd.h>
using namespace std;

countNumbers::countNumbers(int prio, pair<int, int> r)
    : Task(prio, r), priority{prio}, range{r}{
        name = "Counting from " + to_string(range.first) + " to " + to_string(range.second);
        state = NEW;
        srand(time(0));
        processID = rand() % 900000 + 100000;
        prepare();
    }

int countNumbers::getState(){
    return state;
}

string countNumbers::getName(){
    return name;
}

int countNumbers::getPrio(){
    return priority;
}

void countNumbers::setState(int st){
    state = st;
}

bool countNumbers::operator<(Task& rhs){
    return this->getPrio() < rhs.getPrio();
}

void countNumbers::show(){
    cout << "I will be counting from '" << range.first << "' to '" << range.second << "'\n"; 
}

void countNumbers::prepare(){
    key_t key = 16;
    int msgid;

    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;
    message.pid = processID;

    message.status = 'r';

    msgsnd(msgid, &message, sizeof(message), 0);
    cout << message.status << " state requested for task : "<< message.pid << endl;
    
    while(1){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        if(message.status == 's'){
            setState(READY);
            cout << "Process is in RAM and in ready to be executed\n";
            // msgctl(msgid, IPC_RMID, NULL);
            break;
        }
        usleep(1 * 1000 * 1000);
    }
}

countAlphabets::countAlphabets(int prio, pair<char, char> r)
    : Task(prio, r), priority{prio}, range{r}{

        name = "Counting from ";
        name += range.first;
        name += " to ";
        name += range.second;

        state = NEW;
        srand(time(0));
        processID = rand() % 900000 + 100000;
        prepare();
    }

int countAlphabets::getState(){
    return state;
}

string countAlphabets::getName(){
    return name;
}

int countAlphabets::getPrio(){
    return priority;
}

void countAlphabets::setState(int st){
    state = st;
}

bool countAlphabets::operator<(Task& rhs){
    return this->getPrio() < rhs.getPrio();
}

void countAlphabets::show(){
    cout << "I will be counting from '" << range.first << "' to '" << range.second << "'\n";
}

void countAlphabets::prepare(){

    int msgid;
    int key = 16;

    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;
    message.pid = processID;

    message.status = 'r';

    msgsnd(msgid, &message, sizeof(message), 0);
    cout << message.status << " state requested for task : "<< message.pid << endl;

    while(1){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        if(message.status == 's'){
            setState(READY);
            cout << "Process is in RAM and in ready to be executed\n";
            break;
        }
        usleep(1 * 1000 * 1000);
    }
}

