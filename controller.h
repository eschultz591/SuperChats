#include "view.h"

class Controller{
    public: 
        Controller(Server& serv, View& v): server(serv), view(v){};
        void interface();
        void setup(User* user);
        void execute_cmd(int cmd);
        void create_user();
        void create_user_first_time(User* user);
        void remove_user_from_server(string username);
        void user_to_mod(User* user);
        void create_chatroom(string name);
        void add_user_to_chatroom(User* user, string chatroom_name);
        void remove_chatroom(string chatroom_name);
        void create_lobby();
        void boot_users_to_lobby(Chatroom* chatroom);
        void boot_user_to_lobby(string user, string chatroom);
        void auto_add_user_to_lobby(User* user);
        void add_message(); 
        void display_messages(string chatroom);
        int check_Username(string u_n);
        void edit_username(User* user, string new_username);
        bool checkChatName(string chatroom);

    private: 
        Server& server;
        View& view;
};
