#include "server.h"

class View{
    public: 
        View(Server& serv) : server(serv){};
        string get_menu();
        void username_prompt();
        string view_current_users();
        string too_long_prompt();
        string user_already_exists();
        void no_user_prompt();
        void chatroom_name_prompt();
        void view_chatrooms();
        void chatroom_not_found_prompt();
        void invalid_entry();
        void message_prompt();
        void display_messages(Chatroom*);
        void maxed_users_prompt();
    private: 
        Server& server;
};