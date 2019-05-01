#define NCURSES_NOMACROS
#include "controller.h"
#include <ncurses.h>
#include "chat_client.hpp"












class Window{

    public:
        Window(Controller& con, Server& serv, View& v) : controller(con), server(serv), view(v){};
        void start();
        void main_page(User*, WINDOW*);
        void chatroom_window(User*, chat_client & c, WINDOW*);





       // void execute_cmd(int);
       // void create_user();
       // void remove_user();
       // void user_to_mod();
/* working here*/    string  create_chatroom();
        //void add_user_to_chatroom();
        //void remove_chatroom();

        void attempt_delete(chat_client & c);
        void reset_header(chat_client & c);


        void attempt_ban(chat_client & c, char nick[24]);

        string change_nickname(chat_client & c);
        void update_server(chat_client & c);
        void join(chat_client & c);
        void join_chatroom(chat_client& c);

        //void whisper_message(chat_client & c);
        //int test();








    private:
        Controller& controller;
        Server& server;
        View& view;
};
