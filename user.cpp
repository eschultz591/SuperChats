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

void User::checkUsername(string u_n){

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