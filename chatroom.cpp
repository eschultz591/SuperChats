#include "chatroom.h"

Chatroom::Chatroom(){
    name = "None";
    current_users.empty();
    messages.empty();
    //current_num_users = 0;
}

void Chatroom::set_name(string n){
    name = n;
}

string Chatroom::get_name(){
    return name;
    }

vector<User*> Chatroom::get_current_users(){
    return current_users;
}

string Chatroom::to_string(){
    auto iter = current_users.begin();
    string s = "Chatroom Name: " + name + ", Users: ";

    for(; iter != current_users.end(); iter++){
        s += (*iter)->getUsername() + " ";
    }
    return s;
}
/*int Chatroom::get_num_users(){
    return current_num_users;
}

void Chatroom::increment_num_users(){
    current_num_users++;
}*/

void Chatroom::add_user(User* user){
    current_users.push_back(user);
}

void Chatroom::remove_user(string username){
    int position = 0;
    bool found_user = false;

    for(auto x : current_users){
        if (username == x->getUsername()){
            found_user = true;
            break;
        }
        else{
            position++;
        }
    }

    if(found_user){
        current_users.erase(current_users.begin() + position);
    }
    else{
        cout << "User not in chatroom.\n";
    }
}

void Chatroom::add_message(string message){
    messages.push_back(message);
}

vector<string> Chatroom::get_messages(){
    return messages;
}

bool Chatroom::checkNumUsers() {
    if (current_users.size() > 10)
	return true;
    else
	return false;
}

// (JB)
// validate chatroom name
