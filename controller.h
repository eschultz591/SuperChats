#include "view.h"

class Controller{
    public: 
        Controller(Server& serv, View& v): server(serv), view(v){};
        void interface();
        void setup(User*);
        void execute_cmd(int);
        void create_user();
        void create_user_first_time(User*);
        void remove_user_from_server(string);
        void user_to_mod(User*);
        void create_chatroom(string);
        void add_user_to_chatroom(User*, string);
        void remove_chatroom(string);
        void create_lobby();
        void boot_users_to_lobby(Chatroom*);
        void boot_user_to_lobby(string, string);
        void auto_add_user_to_lobby(User*);
        void add_message(); 
        void display_messages(Chatroom*);
        int check_Username(string);
        void edit_username(User*, string);
        bool checkChatName(string);

    private: 
        Server& server;
        View& view;
};
