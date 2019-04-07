#include <iostream>
#include <stdio.h>
using namespace std;

class Message{
    public:
        Message();
        Message(string m, int t): message(m), time(t){};
        string get_message();
        void set_message(string m);
        int get_time();
        void set_time(int t);

    private: 
        int time;
        string message;
};