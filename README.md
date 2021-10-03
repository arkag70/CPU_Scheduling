# OSPriority
Simulating the task execution done by CPU (c++)

Task is a process that is requesting execution. When a task is created, it's state is NEW. When it is received and acknowledged by the Executor
its state changes to READY and it is added to a queue (in shared memory).

Executor is the CPU, that runs one of its threads looking for new Tasks (processes) who want to be executed and brings them into RAM (conceptually).
The second thread, (which is the main thread itself) obtains the taskID (process id) and reads the queue where tasks are queued.
Communication between two threads of one or many processes is through message queues.

When a task is requesting execution, the state is NEW. 
When it is brought into RAM, the state changes to READY. And it is listed in the queue (in shared memory).
When a task execution begins, the state of the task changes from READY to RUNNING and is updated in the shared memory.
Current design supports Non-preemted task execution.
