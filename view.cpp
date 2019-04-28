#include "view.h"

string View::get_menu(){
    string menu = R"(
==========
SUPER CHAT
==========

1) Create User
2) Remove User from server (Admin priviledge)
3) Bump User to Mod Status
4) See Current Users
5) Create a chatroom
6) View Chatrooms
7) Add user to chat
8) Remove Chatroom
9) Remove User from a chatroom (Mod priviledge)
10) Add Message
11) View messages

)";

return menu;
}

string View::username_prompt(){
    return "Enter a username: ";
}

string View::view_current_users(){
    string header = R"(
XXXXXXXXXXXXX
Current Users
XXXXXXXXXXXXX

)";
    header += server.display_users2();
    cout << header;
    return header;
}

string View::view_chatrooms(){
    string header = R"(
XXXXXXXXX
CHATROOMS
XXXXXXXXX

)";
    header += server.display_chatrooms();
    return header;
}

string View::display_messages(Chatroom* chatroom){

    string header = R"(
XXXXXXXX
MESSAGES
XXXXXXXX

)";
    for(auto x : chatroom->get_messages()){
        header += x;
        header += "\n";
    }
    return header;
    
}

string View::no_user_prompt(){
    return "No user found.\n";
}

string View::chatroom_name_prompt(){
    return "Enter a chatroom name: ";
}

string View::chatroom_not_found_prompt(){
    return "Chatroom not found.\n";
}

string View::invalid_entry(){
    return "Invalid input. Please select a correct option.\n";
}

string View::message_prompt(){
    return "Enter message: ";
}

string View::maxed_users_prompt(){
    return "Maxed users reached. Try again later.\n";
}

string View::too_long_prompt(){
    return "Username can be no more than 50 characters.\n";
}

string View::user_already_exists(){
    return "Username already taken.";
}

string View::maxed_chatrooms_prompt(){
    return "Chatroom limit reached. Delete a chatroom to create a new one.\n";
}

string View::chatname_already_exists(){
    return "Chatname already exists.\n";
}

string View::no_privileges_prompt(){
    return "Must have moderator or admin privileges.\n";
}
