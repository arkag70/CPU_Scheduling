#include "Task.hpp"

int main(int argc, char *argv[]){
    
    /* ./task numeric 10 56 110 - numeric for counting numbers, 10 is the priority 56-110 is the range  */
    
    if(argc < 5){
        cout << "Error in argument list\n";
    }
    else{
        string type = string(argv[1]);
        int priority = (int)strtol(argv[2], NULL, 10);
        pair<int, int> range_n;
        pair<char, char> range_a;
        if(type == "numeric"){
            range_n.first = (int)strtol(argv[3], NULL, 10);
            range_n.second = (int)strtol(argv[4], NULL, 10);
            Task *t = new countNumbers(priority, range_n);
        }
        else if(type == "alpha"){
            range_a.first = string(argv[3])[0];
            range_a.second = string(argv[4])[0];
            Task *t = new countAlphabets(priority, range_a);
        }
        else{
            cout << "Error type : " << type << endl;
        }
    }

    return 0;
}