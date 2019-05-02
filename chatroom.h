#include "user.h"
#include <vector>
#include "message.h"

class Chatroom{
    public: 
        Chatroom();
        Chatroom(string n, vector<User*> c_users,vector<User*> b, vector<string> m) : name(n), current_users(c_users), banned_users(b), messages(m){};
        void set_name(string n);
        string get_name();
        vector<User*> get_current_users();
        int get_num_users();
        void increment_num_users();
        string to_string();
        void add_user(User*);
        void add_user_to_banned_list(User*);
        vector<User*> get_banned_users();
        friend string get_name_for_friend();
        void remove_user(string);
        void add_message(string);
        vector<string> get_messages();
        bool checkNumUsers();

    private: 
        string name;
        vector<User*> current_users;
        vector<User*> banned_users;
        vector<string> messages;
};