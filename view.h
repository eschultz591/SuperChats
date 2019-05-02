#include "server.h"

class View{
    public: 
        View(Server& serv) : server(serv){};
        string get_menu();
        string username_prompt();
        string view_current_users();
        string too_long_prompt();
        string user_already_exists();
        string no_user_prompt();
        string chatroom_name_prompt();
        string view_chatrooms();
        string chatroom_not_found_prompt();
        string invalid_entry();
        string message_prompt();
        string display_messages(Chatroom*);
        string maxed_users_prompt();
        string maxed_chatrooms_prompt();
        string chatname_already_exists();
        string no_privileges_prompt();
        string banned_prompt();
        string already_in_lobby();
    private: 
        Server& server;
};