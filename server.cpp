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

map<Chatroom*, int> &Server::get_chatrooms(){
    return chatrooms;
} 

//erases chatroom from server, but doesn't deallocate Users MUST FIX
void Server::remove_chatroom(Chatroom* chatroom){
    users = chatroom->get_current_users();
    chatrooms.erase(chatroom);
    delete chatroom;
}

// (JB)
// validate number of users on the server
bool Server::checkNumUsers() {
    // server cannot exceed more than 50 users
    if (users.size() > 50)
	return true;
    else
	return false;
}

// (JB)
bool Server::checkNumChatrooms() {
    // server cannot exceed more than 10 chatrooms
    if (chatrooms.size() > 10)
	return true;
    else
	return false;
}

// (JB)
int Server::getNumUsers() {return user.size();}

// (JB)
int Server::getNumChatrooms() {return chatrooms.size();}

// (JB)
int Server::getNumModerators() {
    string num_mod;
    for (auto x : get_users()) {
	x->getUsername();
	if (isMod == true) {
	    num_mod++;
	}
    }
    return num_mod;
}
