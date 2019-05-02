#include "controller.h"

void Controller::setup(User* user){
    create_user_first_time(user);
    bool lobby_already_created = false;

    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == "Lobby"){
            lobby_already_created = true;
            break;
        }
    }

    if(!lobby_already_created){
        create_lobby();
    }
    auto_add_user_to_lobby(user); 
    
}


int Controller::check_Username(string u_n){
	//checking the length
	if((u_n.length()) > 15){		
		//cout << "Username is to long." << endl;
		return 2;
	}
	//checking if user already exist
	for(auto x: server.get_users()){
		if(x->getUsername() == u_n){
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
            x->setUsername(new_username);
            break;
        }
    }
}


void Controller::create_user_first_time(User* user){

    //first user to log into server becomes admin
    int size = server.getUsers().size();
    if (size == 0){
        user->setAdmin();
    }
    
    server.add_user(user);
}

void Controller::auto_add_user_to_lobby(User* user){
    string lobby = "Lobby";


    for(auto&&x : server.get_chatrooms()){
        if (lobby == x.first->get_name()){
            x.first->add_user(user);
            user->set_room(lobby); 
            x.second++;
            break;
        }
    }
}

void Controller::add_user_to_chatroom(User* user, string chatname){
    
    //first remove user from current room
    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == user->get_room()){
            x.first->remove_user(user->getUsername());
                x.second--;
                break;
        }
    }

        //this loop adds user to new room
        for(auto&&x : server.get_chatrooms()){
            if(x.first->get_name() == chatname){
                    x.first->add_user(user);
                    x.second++;
                    user->set_room(chatname);
                    break;
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

void Controller::create_chatroom(string chatname){
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name(chatname);
    server.add_chatroom(chatroom);
}

void Controller::create_lobby(){
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name("Lobby");
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
void Controller::boot_user_to_lobby(User* user){
    
    for(auto&&x : server.get_chatrooms()){
        if (x.first->get_name() == user->get_room()){
            
            //this loop removes user from his current chatroom
            for(auto&&y : x.first->get_current_users()){
                if(y->getUsername() == user->getUsername()){
                    x.first->remove_user(user->getUsername());
                    x.second--;
                    auto_add_user_to_lobby(y);
                    break;
                }
            }
            break;
        }
    }
}

void Controller::add_message(string text, User* user){

    Message* m = new Message(text);
    string message_as_string = m->get_message();
    delete m;

    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == user->get_room()){
            x.first->add_message(message_as_string);
            break;
        }
    }
}

string Controller::display_messages(User* user){

    string messages;

    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == user->get_room()){
            messages = view.display_messages(x.first); 
            break;
        }
    }
    return messages;
}

int Controller::checkChatName(string chatroom) {
    int valid;
    bool found_chat = false;
    for (auto x : server.get_chatrooms()) {
	    if (x.first->get_name() == chatroom){

	        if(x.second >= 10){
                valid = 2;
            }
            else{
                valid = 1;
            }
            found_chat = true;
            break;
        }
	}
        if (!found_chat){
            valid = 3;
        }
    return valid;
}  

int Controller::validate_chatname(string chatname){
    int valid = 1;
    //will return 1 if no chatroom by that name exists. if chatroom name does not exist (GOOD! USER CAN CREATE CHAT)

    for (auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == chatname){
            valid = 2;
            break;
        }
    }
    if(server.get_chatrooms().size() >= 10){
        valid = 3;
    }
    return valid;
}

bool Controller::chatroom_full(string chatname){
    bool isFull;
    for(auto&&x : server.get_chatrooms()){
        if (x.first->get_name() == chatname){
            if(x.second >= 10){
                isFull = true;
                break;
            }
        }
    }
    return isFull;
}
/*void Controller::create_user(){
    string username;
    view.username_prompt();
    cin >> username;
    while(check_Username(username) == false); 
    User* user = new User();
    user->setUsername(username);
    server.add_user(user);
    auto_add_user_to_lobby(user);
}*/
