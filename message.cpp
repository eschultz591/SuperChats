#include "message.h"

string Message::get_message(){
    return message;
}

void Message::set_message(string m){
    message = m;
}

int Message::get_time(){
    return _time;
}

void Message::set_time(int t){
    _time = t;
}

string Message::to_string(){
    return "Time: " + std::to_string(_time) + ", Message: " + message + "\n";
}  