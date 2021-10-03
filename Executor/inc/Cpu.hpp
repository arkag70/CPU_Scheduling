#ifndef CPU_HPP
#define CPU_HPP

#include<bits/stdc++.h>
#include "Task.hpp"
using namespace std;

class Cpu{

private:
    float frequency;
    static bool comparator(Task *a, Task *b);   
    struct mesg_buffer{
        long mesg_type;
        char status;
        long pid;
    };
    mesg_buffer message_process;
    // mesg_buffer message_execute;

public:
    Cpu(float f);
    void load();
    void execute();
    void cleanup();
    void runMultithreading();
};
#endif