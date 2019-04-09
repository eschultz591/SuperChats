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
        case 8:
            remove_chatroom();
            break;
	case 9:
	    edit_username(); // (JB)
	    break;
    }
}

void Controller::create_user(){
    string username;
    view.username_prompt();
    cin >> username;
    // validate username (JB)
    if (user.checkUsername(username) == true)
	throw runtime_error{"Invalid username.\n"};
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

        for(auto&& x : server.get_chatrooms()){
            if (x.first->get_name() == chatroom_name) {
		if (chatroom.checkNumUsers() == true) // (JB)
		    view.maxed_users_prompt();
		else {
                    x.first->add_user(user);
                    server.get_chatrooms().at(x.first) += 1;
                    foundChat = true;
		}
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
            delete x;
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
    // validate chatroom name (JB)
    if (chatroom.checkChatName(name) == true)
	throw runtime_error{"Chatroom name already exists."};
    // validate for number of chatrooms (JB)
    if (server.checkNumChatrooms() == true)
	throw runtime_error{"Chatroom limit reached. Delete a chatroom to create a new one."};
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name(name);
    server.add_chatroom(chatroom);
}


//Deletes users from chatroom, removes chatroom from server, then deletes chatroom object
void Controller::remove_chatroom(){
    string chatroom_name;
    int position = 0;
    bool foundChat = false;
    view.chatroom_name_prompt();
    cin >> chatroom_name;

    for(auto x : server.get_chatrooms()){
        if (x.first->get_name() == chatroom_name){
            foundChat = true;
            server.remove_chatroom(x.first);
            break;
        }
    }
    if(!foundChat){
        cout << "Chatroom not found.\n" << endl;
    }
}

// (JB)
void Controller::edit_username() {
    string current_username, new_username;
    view.username_prompt();
    cin >> current_username;
    for (auto x : server.get_users()) {
        if(current_username == x->getUsername()) {
            cout << "New username: ";
            cin >> new_username;

            // validate new username
            if (User.checkUsername(new_username) == false)
                 throw runtime_error{"Invalid username.\n"};

            x->setUsername(new_username);
        }
    }
}
