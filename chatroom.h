#include "user.h"
#include <vector>

class Chatroom{
    public: 
        Chatroom();
        Chatroom(string n, vector<User*> c_users) : name(n), current_users(c_users){};
        void set_name(string n);
        string get_name();
        vector<User*> get_current_users();
        int get_num_users();
        void increment_num_users();
        string to_string();
        void add_user(User*);
	bool checkNumUsers(); // (JB)
	bool checkChatName(); // (JB)

    private: 
        string name;
        vector<User*> current_users;
};
