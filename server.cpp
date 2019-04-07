#include "server.h"

vector <User*> Server::getUsers(){
    return users;
}

void Server::add_user(User* user){
    users.push_back(user);
}

void Server::add_chatroom(Chatroom* chatroom){
    chatrooms.insert(pair<Chatroom*,int>(chatroom,0));
}

string Server::display_chatrooms(){
    ostringstream output;
    for (auto x: chatrooms){
        output << (*(x.first)).to_string() << ", Num Users: " << x.second <<endl;
    }
    return output.str();
}
string Server::display_users(){
    ostringstream output;
    for (auto x : users){
        output << "Username: " << x->getUsername() << endl;
    }
    return output.str();
}

//for testing
string Server::display_users2(){
    ostringstream output;
    for (auto x : users){
        output << "Username: " << x->getUsername() << ", Moderator: " << x->getMod()<< ", Admin: " << x->getAdmin() << ", Can Obfuscate: " << x->getOb() << ", Current Chatroom: " << x->get_room() << endl;
    }
    return output.str();
}

void Server::remove_user(int position){
    users.erase(users.begin() + position);
} 

vector<User*> Server::get_users(){
    return users;
}

map<Chatroom*, int> &Server::get_chatrooms(){
    return chatrooms;
} 

//erases chatroom from server, but doesn't deallocate Users MUST FIX
void Server::remove_chatroom(Chatroom* chatroom){
    users = chatroom->get_current_users();
    chatrooms.erase(chatroom);
    delete chatroom;
} 