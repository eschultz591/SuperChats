#include "user.h"

User::User(){
    username = "XXX";
    isMod = false;
    isAdmin = false;
    isBanned = false;
    canOb = false;
}

string User::getUsername(){
    return username;
}

void User::setUsername(string u_n){
    username = u_n;
}

bool User::checkUsername(string u_n){

}

bool User::getMod(){
    return isMod;
}

void User::setMod(){
    isMod = true;
}

bool User::getAdmin(){
    return isAdmin;
}

void User::setAdmin(){
    isAdmin = true;
}

bool User::getBanned(){
    return isBanned;
}

void User::setBanned(){
    isBanned = true;
}

bool User::getOb(){
    return canOb;
}

void User::setOb(){
    canOb = true;
}

void User::downgradeAdmin(){
    isAdmin = false;
}

void User::downgradeMod(){
    isMod = false;
}

void User::downgradeOb(){
    canOb = false;
}

// (JB)
void User::banUser() {
    // if user is a moderator, they can ban a user
    if (isMod == true) {
	view.username_prompt9);
	cin >> username;
	bool foundUser = false;

	for (auto x : server.get_users()) {
	    if (x->getUsername() == username) {
	        foundUser = true;
                x.setBanned();
                break;
	    }
	}

	if (!foundUser) {
	    view.no_user_prompt();
	}
    }
    else {
	view.no_privileges_prompt();
    }
}
