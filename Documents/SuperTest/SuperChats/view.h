#include "server.h"

class View{
    public: 
        View(Server& serv) : server(serv){};
        string get_menu();
        void username_prompt();
        void view_current_users();
        void no_user_prompt();
        void chatroom_name_prompt();
        void view_chatrooms();
    private: 
        Server& server;
};