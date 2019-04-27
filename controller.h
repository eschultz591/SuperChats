#include "view.h"

class Controller{
    public: 
        Controller(Server& serv, View& v): server(serv), view(v){};
        void interface();
        void setup(string);
        void execute_cmd(int);
        void create_user();
        User* create_user_first_time(string);
        void remove_user_from_server();
        void user_to_mod();
        void create_chatroom();
        void add_user_to_chatroom();
        void remove_chatroom();
        Chatroom* create_lobby();
        void boot_users_to_lobby(Chatroom*);
        void boot_user_to_lobby();
        void auto_add_user_to_lobby(User*);
        void add_message();
        void display_messages();
        int check_Username(string);
        void edit_username();
        bool checkChatName(string);

    private: 
        Server& server;
        View& view;
};
