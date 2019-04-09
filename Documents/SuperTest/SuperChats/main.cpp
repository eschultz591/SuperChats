#include "controller.h"
//#include "chat_client.hpp"



int main(){
    Server server;
    View view(server);

    //chat_client client;

    Controller controller(server, view);
    controller.interface();
}
