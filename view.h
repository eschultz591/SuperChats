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
	void no_privileges_prompt(); // (JB)
        void maxed_users_prompt(); // (JB)
    private: 
        Server& server;
};
