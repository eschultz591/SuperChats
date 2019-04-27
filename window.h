#include "controller.h"
#include <ncurses.h>

class Window{

    public: 
        Window(Controller& con, Server& serv, View& v) : controller(con), server(serv), view(v){};
        void start();
        void main_page(string user_input, WINDOW*);
	void chatroom_window(/*string lobby_name, string username, WINDOW* main_window*/);
        void test_controller();
    private: 
        Controller& controller;
        Server& server;
        View& view;
}; 
