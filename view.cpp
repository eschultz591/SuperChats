#include "view.h"

string View::get_menu(){
    string menu = R"(
==========
SUPER CHAT
==========

1) Create User
2) Remove User
3) Bump User to Mod Status
4) Join ChatRoom
5) See Current Users

)";

return menu;
}

void View::username_prompt(){
    cout << "Enter a username: " << endl;
}

void View::view_current_users(){
    string header = R"(
XXXXXXXXXXXXX
Current Users
XXXXXXXXXXXXX

)";
    header += server.display_users2();
    cout << header;
}

void View::no_user_prompt(){
    cout << "No user found.\n";
}