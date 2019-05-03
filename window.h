#include "controller.h"
#include <ncurses.h>

class Window{

    public: 
        Window(Controller& con, Server& serv, View& v) : controller(con), server(serv), view(v){};
        void start();
        void main_page(User*, WINDOW*);
        void chatroom_window(User*, WINDOW*);

    private: 
        Controller& controller;
        Server& server;
        View& view;
}; 