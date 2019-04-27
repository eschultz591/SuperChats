#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <iostream>

using namespace std;

class User{
    public: 
        User();
        User(string u_n, bool mod, bool ad, bool ban, bool ob, string cc): username(u_n), isMod(mod), isAdmin(ad), isBanned(ban), canOb(ob), current_chatroom(cc){};
        void checkUsername(string);
        void editUsername(string);
        string getUsername();
        bool getMod();
        bool getAdmin();
        bool getBanned();
        bool getOb();
        void setUsername(string);
        void setMod();
        void setAdmin();
        void setBanned();
        void setOb();
        void downgradeMod();
        void downgradeAdmin();
        void downgradeOb();
        string get_room();
        void set_room(string r);

        private: 
            string username;
            bool isMod;
            bool isAdmin;
            bool isBanned;
            bool canOb;
            string current_chatroom;

};

#endif