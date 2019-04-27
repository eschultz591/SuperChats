#include "window.h"

int main(){
    Server server;
    View view(server);
    Controller controller(server, view);
    //controller.setup();
    //controller.interface();


    Window window(controller,server,view);
    //window.start();
    window.chatroom_window();
    

}
