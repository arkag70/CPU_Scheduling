#include "Cpu.hpp"
#include <thread>
#include <unistd.h>

Cpu::Cpu(float f): frequency{f}{

    runMultithreading();
}

bool Cpu::comparator(Task *a, Task *b){
    return !(*a < *b);
}

void Cpu::runMultithreading(){
    thread wait4process(&Cpu::load, this);
    
    execute();
    wait4process.join();
    // executeProcess.join();
}

void Cpu::load(){
    int msgid;
    int key = 16;

    msgid = msgget(key, 0666 | IPC_CREAT);
    // msgid_e = msgget(key_e, 0666 | IPC_CREAT);
    
    cout << __func__ << " : Waiting for requests from processes...\n";

    while(1){
        msgrcv(msgid, &message_process, sizeof(message_process), 1, 0);
        if(message_process.status == 'r'){
            
            // send acknowledgement to process Task
            message_process.mesg_type = 1;
            message_process.status = 's';
            msgsnd(msgid, &message_process, sizeof(message_process), 0);
            cout << __func__<< " : new process " << message_process.pid << " requesting to be loaded into RAM!\n";
            
            // copy the PID and status to start execution in another thread
            message_process.mesg_type = 2;
            message_process.status = 'l';
            msgsnd(msgid, &message_process, sizeof(message_process), 0);
            cout << __func__ << " : Process " << message_process.pid << " will be executed now\n";
        }
        usleep(frequency * 1000 * 1000);
    }
}

void Cpu::execute(){
    
    int msgid;
    int key = 16;
    msgid = msgget(key, 0666 | IPC_CREAT);

    // wait to receive from load thread the information of the process (ID) to be executed
    while(1){
        cout << __func__ << " : Waiting for process to be executed\n";
        msgrcv(msgid, &message_process, sizeof(message_process), 2, 0);
        if(message_process.status == 'l'){
            cout << __func__ << " : executing process " << message_process.pid << endl;
            message_process.status = 'L';
        }
        usleep(frequency * 1000 * 1000);
    }
}

void Cpu::cleanup(){
    // for(auto task : tasks){
    //     if(task->getState() == TERMINATED){
    //         cout << "Cleaning task : " << task->getName() << endl;
    //         delete task;
    //     }
    // }
}