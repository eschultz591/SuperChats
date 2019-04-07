#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <stdio.h>
using namespace std;

class Message{
    public:
        Message();
        Message(string m, int t): message(m), _time(t){};
        string get_message();
        void set_message(string m);
        int get_time();
        void set_time(int t);
        string to_string();

    private: 
        int _time;
        string message;
};

#endif