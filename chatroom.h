#include "user.h"
#include <vector>
#include "message.h"

class Chatroom{
    public: 
        Chatroom();
        Chatroom(string n, vector<User*> c_users, vector<string> m) : name(n), current_users(c_users), messages(m){};
        void set_name(string n);
        string get_name();
        vector<User*> get_current_users();
        int get_num_users();
        void increment_num_users();
        string to_string();
        void add_user(User*);
        friend string get_name_for_friend();
        void remove_user(string);
        void add_message(string);
        vector<string> get_messages();
        

    private: 
        string name;
        vector<User*> current_users;
        vector<string> messages;

    string get_name_for_friend(){
        return name;
    }
};