#include "controller.h"

void Controller::setup(string username){
    User* user = create_user_first_time(username);
    bool lobby_already_created = false;

    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == "Lobby"){
            lobby_already_created = true;
            break;
        }
    }

    if(!lobby_already_created){
        Chatroom* lobby = create_lobby();
    }
    auto_add_user_to_lobby(user); 
    
}

void Controller::interface(){
    int cmd = 0;
 
    do{
        cout << view.get_menu();
        cin >> cmd;
        while(true){
            if(cin.fail()){
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                view.invalid_entry();
                view.get_menu();
                cin >> cmd;
            }
            if(!cin.fail()){
                break;
            }
        }
        
        execute_cmd(cmd);

    } while(cmd != 0);
}

void Controller::execute_cmd(int cmd){
    switch(cmd){
        case 0:
            break;
        case 1:
            create_user();
            break;
        case 2:
            remove_user_from_server();
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
            boot_user_to_lobby();
            break;
        case 10:
            add_message();
            break;
        case 11:
            display_messages();
            break;
        default: 
            view.invalid_entry();
            break;
    }
}

void Controller::create_user(){
    string username;
    view.username_prompt();
    cin >> username;
    while(check_Username(username) == false); 
    User* user = new User();
    user->setUsername(username);
    server.add_user(user);
    auto_add_user_to_lobby(user);
}

int Controller::check_Username(string u_n){
	//checking the length
	if((u_n.length()) > 5){		
		//cout << "Username is to long." << endl;
		return 2;
	}
	//checking if user already exist
	for(auto x: server.get_users()){
		if(x->getUsername() == u_n){
			cout << "Username already exist." << endl;
			return 3;
		}
	}
	return 1;
}

void Controller::edit_username() {
    string current_username, new_username;
    view.username_prompt();
    cin >> current_username;
    for (auto x : server.get_users()) {
        if(current_username == x->getUsername()) {
            cout << "New username: ";
            cin >> new_username;

            // validate new username
            /*if (x->checkUsername(new_username) == false)
                 throw runtime_error{"Invalid username.\n"};*/

            x->setUsername(new_username);
        }
    }
}


User* Controller::create_user_first_time(string username){
    //string username;
    //view.username_prompt();
    //cin >> username;
    
    User* user = new User();
    user->setUsername(username);

    //first user to log into server becomes admin
    int size = server.getUsers().size();
    if (size == 0){
        user->setAdmin();
    }
    
    server.add_user(user);
    return user;
}

void Controller::auto_add_user_to_lobby(User* user){
    string lobby = "Lobby";
    //user->set_room(lobby);

    for(auto&&x : server.get_chatrooms()){
        if (lobby == x.first->get_name()){
            x.first->add_user(user);
            user->set_room(lobby); 
            x.second++;
            break;
        }
    }
}

void Controller::add_user_to_chatroom(){
    string username, chatroom_name, users_current_chatroom;
    User* user;
    bool foundChat = false;
    bool foundUser = false;
    bool room_full = false;

    view.username_prompt();
    cin >> username;
     
    for(auto x : server.get_users()){
        if(x->getUsername() == username){
            users_current_chatroom = x->get_room();
            user = x;
            foundUser = true;
            break;
        }
    }

    if(!foundUser){
        view.no_user_prompt();
    }
    else{
        view.chatroom_name_prompt();
        cin >> chatroom_name;

        //this loop makes sure chatroom user wants to join has space
        for(auto&&x : server.get_chatrooms()){
            if(x.first->get_name() == chatroom_name){
                if(x.first->checkNumUsers() == true){
                    view.maxed_users_prompt();
                    room_full = true;
                }
                else{
                    x.first->add_user(user);
                    x.second++;
                }
                foundChat = true;
                break;
            }
        }

        //this loop removes user from current chatroom
        if(!room_full){
            for(auto&&x : server.get_chatrooms()){
                if(x.first->get_name() == users_current_chatroom){
                    x.first->remove_user(user->getUsername());
                    x.second--;
                    break;
                }
            }
        }
        
        if(!foundChat){
            view.chatroom_not_found_prompt();
        }
    }
}

void Controller::remove_user_from_server(){
    string username;
    view.username_prompt();
    cin >> username;
    int position = 0;
    bool foundUser = false;
    string user_current_room;

    
    for(auto x : server.get_users()){
        if (x->getUsername() == username){
            
            user_current_room = x->get_room();

            //this line removes user from current chatroom
            for(auto&&x : server.get_chatrooms()){
                if(x.first->get_name() == user_current_room){
                    x.first->remove_user(username);
                    x.second--;
                }
            }
            foundUser = true;
            
            delete x;
            break;
        }
        else{
            position++;
        }
        
    }
    if (foundUser){
        //this line removes user from global server
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
    if(server.checkNumChatrooms() == true){
        throw runtime_error("Chatroom limit reached.\n");
    }
    if (checkChatName(name) == true){
        throw runtime_error("Chatname already exists.\n");
    }
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name(name);
    server.add_chatroom(chatroom);
}

Chatroom* Controller::create_lobby(){
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name("Lobby");
    server.add_chatroom(chatroom);
    return chatroom;
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
            boot_users_to_lobby(x.first);
            server.remove_chatroom(x.first);
            delete x.first;
            
            break;
        }
    }
    if(!foundChat){
        view.chatroom_not_found_prompt();
    }
}

void Controller::boot_users_to_lobby(Chatroom* chatroom){
    for(auto x : chatroom->get_current_users()){
        auto_add_user_to_lobby(x);
    }
}
void Controller::boot_user_to_lobby(){
    string chatroom, user;
    view.chatroom_name_prompt();
    cin >> chatroom;
    view.username_prompt();
    cin >> user;
    bool chatroom_found = false;
    bool user_found = false;
    for(auto&&x : server.get_chatrooms()){
        if (x.first->get_name() == chatroom){
            
            //this loop removes user from his current chatroom
            for(auto&&y : x.first->get_current_users()){
                if(y->getUsername() == user){
                    x.first->remove_user(user);
                    x.second--;
                    auto_add_user_to_lobby(y);
                    user_found = true;
                    break;
                }
            }
            chatroom_found = true;
            break;
        }
    }

    if(!user_found){
        view.no_user_prompt();
    }
    if(!chatroom_found){
        view.chatroom_not_found_prompt();
    }
}

void Controller::add_message(){
    string text;
    string full_message;
    string what_room_are_we_in;
    bool foundChat = false;
    static int t = 1;
    view.message_prompt();
    cin.ignore();
    std::getline(cin, text);
    //cin >> text;

    view.chatroom_name_prompt();
    cin >> what_room_are_we_in;
    
    Message* m = new Message(text, t);
    full_message = m->to_string();
    delete m;

    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == what_room_are_we_in){
            x.first->add_message(full_message);
        }
    }
    t++;
}

void Controller::display_messages(){
    string chatroom_name;
    bool chatroom_found = false;
    view.chatroom_name_prompt();
    cin >> chatroom_name;
    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == chatroom_name){
            view.display_messages(x.first); 
            chatroom_found = true;
            break;
        }
    }
    if(!chatroom_found){
        view.chatroom_not_found_prompt();
    }
}

bool Controller::checkChatName(string chatroom) {
    for (auto x : server.get_chatrooms()) {
	    if (x.first->get_name() == chatroom)
	        return true;
	    else
	        return false;
	}
}  
