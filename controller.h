#include "view.h"

class Controller{
    public: 
        Controller(Server& serv, View& v): server(serv), view(v){};
        void setup(User*);
        
        void create_user_first_time(User*);
        void remove_user_from_server();
        void user_to_mod();
        void create_chatroom(string);
        void add_user_to_chatroom(User*, string);
        void remove_chatroom(string); 
        void create_lobby();
        void boot_users_to_lobby(Chatroom*);
        void boot_user_to_lobby(User*);
        void auto_add_user_to_lobby(User*);
        void add_message(string, User*); 
        string display_messages(User*);
        int check_Username(string);
        void edit_username();
        //to join chat validation
        int checkChatName(string, User*);

        //to create chatroom validation
        int validate_chatname(string);
        bool chatroom_full(string);
        bool check_if_user_is_banned(User*, string); 


        //these functions are not currently in use and may be deleted later
        /*void create_user();
        */

    private: 
        Server& server;
        View& view;
};