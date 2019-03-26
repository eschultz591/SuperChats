#include "controller.h"

void Controller::interface(){
    int cmd = 0;
    do{
        cout << view.get_menu();
        cin >> cmd;
        execute_cmd(cmd);

    } while(cmd != 0);
}

void Controller::execute_cmd(int cmd){
    switch(cmd){
        case 1:
            create_user();
            break;
        case 2:
            remove_user();
            break;
        case 3:
            user_to_mod();
            break;
        case 5:
            view.view_current_users();
            break;
    }
}

void Controller::create_user(){
    string username;
    view.username_prompt();
    cin >> username;
    User* user = new User();
    user->setUsername(username);
    server.add_user(user);
}

void Controller::remove_user(){
    string username;
    view.username_prompt();
    cin >> username;
    int position = 0;
    bool foundUser = false;
    
    for(auto x : server.get_users()){
        if (x->getUsername() == username){
            foundUser = true;
            break;
        }
        else{
            position++;
        }
        
    }
    if (foundUser){
            server.remove_user(position);
    }
    else{
        view.no_user_prompt();
    }

}

void Controller::user_to_mod(){
    string username;
    view.username_prompt();
    cin >> username;
    bool foundUser = false;
    
    for(auto x : server.get_users()){
        if (x->getUsername() == username){
            foundUser = true;
            x->setMod();
            break;
        }
        
    }
    if (!foundUser){
        view.no_user_prompt();
    }

}
