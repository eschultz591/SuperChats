#include "user.h"
#include "chatroom.h"
#include <vector>
#include <sstream>
#include <map>

class Server{
    public: 
        vector<User*> getUsers();
        void add_user(User*);
        string display_users();
        string display_users2();
        void remove_user(int);
        vector<User*> get_users();
        void add_chatroom(Chatroom*);
        string display_chatrooms();
        map<Chatroom*, int> get_chatrooms();
    private: 
        vector<User*> users;
        map<Chatroom*, int> chatrooms; 

};