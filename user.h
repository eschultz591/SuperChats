#include <stdio.h>
#include <iostream>

using namespace std;

class User{
    public: 
        User();
        User(string u_n, bool mod, bool ad, bool ban, bool ob): username(u_n), isMod(mod), isAdmin(ad), isBanned(ban), canOb(ob){};
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

        private: 
            string username;
            bool isMod;
            bool isAdmin;
            bool isBanned;
            bool canOb;

};