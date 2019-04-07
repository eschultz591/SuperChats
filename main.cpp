#include "controller.h"

int main(){
    Server server;
    View view(server);
    Controller controller(server, view);
    controller.setup();
    controller.interface();
}