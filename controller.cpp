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
        case 4:
            view.view_current_users();
            break;
        case 5:
            create_chatroom();
            break;
        case 6:
            view.view_chatrooms();
            break;
        case 7: 
            add_user_to_chatroom();
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

void Controller::add_user_to_chatroom(){
    string username, chatroom_name;
    User* user;
    bool foundChat = false;
    bool foundUser = false;

    view.username_prompt();
    cin >> username;
     
    for(auto x : server.get_users()){
        if(x->getUsername() == username){
            user = x;
            foundUser = true;
            break;
        }
    }

    if(!foundUser){
        cout << "No user found.\n" << endl;
    }
    else{
        view.chatroom_name_prompt();
        cin >> chatroom_name;

        for(auto x : server.get_chatrooms()){
            if(x.first->get_name() == chatroom_name){
                x.first->add_user(user);
                x.second++;
                foundChat = true;
                break;
            }
        }

        if(!foundChat){
            cout << "Chatroom not found.\n" << endl;
        }
    }


    
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

void Controller::create_chatroom(){
    string name;
    view.chatroom_name_prompt();
    cin >> name;
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name(name);
    server.add_chatroom(chatroom);
}