#include "controller.h"
#include <ncurses.h>

class Window{

    public: 
        Window();
        void start();
    private: 
        Controller* con;
        Server* server;
        View* view;
};