#include "view.h"

class Controller{
    public: 
        Controller(Server& serv, View& v): server(serv), view(v){};
        void interface();
        void execute_cmd(int);
        void create_user();
        void remove_user();
        void user_to_mod();
        void create_chatroom();
        void add_user_to_chatroom();

    private: 
        Server& server;
        View& view;
};