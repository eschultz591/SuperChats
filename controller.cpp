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
                if(x.second == 0){
                    user->setMod();
                }
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
void Controller::remove_chatroom(string chatroom){

    for(auto x : server.get_chatrooms()){
        if (x.first->get_name() == chatroom){
            boot_users_to_lobby(x.first);
            server.remove_chatroom(x.first);
            //delete x.first; line was throwing a memory leak
            break;
        }
    }
}

//for clearing an entire chatroom, called when admin deletes room
void Controller::boot_users_to_lobby(Chatroom* chatroom){

    //if the chatroom is not empty, pass boot every user
    if(!chatroom->get_current_users().empty()){
        for(auto x : chatroom->get_current_users()){
            boot_user_to_lobby(x);
        }
    }
    
}

//for booting a single user, called when moderator boots
void Controller::boot_user_to_lobby(User* user){
    
    for(auto&&x : server.get_chatrooms()){
        if (x.first->get_name() == user->get_room()){
            
            //this loop removes user from his current chatroom
            for(auto y : x.first->get_current_users()){
                if(y->getUsername() == user->getUsername()){

                    //removes user from current room
                    x.first->remove_user(user->getUsername());
                    x.second--;

                    //then adds user to lobby
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

//this checks if the chat exists and if there is space to join (10 or less people)
//FOR JOINING CHATROOMS
int Controller::checkChatName(string chatroom, User* user) {
    int valid;
    bool found_chat = false;
    bool isBanned;

    isBanned = check_if_user_is_banned(user, chatroom);

    if(isBanned){
        valid = 4;
    }
    else if(chatroom == "Lobby"){
        valid = 5;
    }
    else{
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
    }
    return valid;
}  


//FOR CREATING CHAT ROOMS.
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

bool Controller::check_if_user_is_banned(User* user, string chatname){
    //find the right chatroom
    for(auto&&x : server.get_chatrooms()){
        if(x.first->get_name() == chatname){
            //go through that chatroom's banned user list
            for(auto y : x.first->get_banned_users()){
                //if user is on list, return true
                if (y->getUsername() == user->getUsername()){
                    return true;
                }
            }
        }
    }
    // if user is not banned, return false.
    return false;
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
