#include "user.h"
#include <vector>
#include <sstream>

class Server{
    public: 
        vector<User*> getUsers();
        void add_user(User*);
        string display_users();
        string display_users2();
        void remove_user(int);
        vector<User*> get_users();
    private: 
        vector<User*> users;
};