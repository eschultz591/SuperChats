#include "message.h"

string Message::get_message(){
    return message;
}

void Message::set_message(string m){
    message = m;
}

int Message::get_time(){
    return time;
}

void Message::set_time(int t){
    time = t;
}
