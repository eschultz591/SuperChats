#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <stdio.h>
using namespace std;

class Message{
    public:
        Message();
        Message(string m): message(m){};
        string get_message();
        void set_message(string m);

    private: 
        string message;
};

#endif