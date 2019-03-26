#include "server.h"

vector <User*> Server::getUsers(){
    return users;
}

void Server::add_user(User* user){
    users.push_back(user);
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
        output << "Username: " << x->getUsername() << ", Moderator: " << x->getMod()<< ", Admin: " << x->getAdmin() << ", Can Obfuscate: " << x->getOb() << endl;
    }
    return output.str();
}

void Server::remove_user(int position){
    users.erase(users.begin() + position);
} 

vector<User*> Server::get_users(){
    return users;
}