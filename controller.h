#include "view.h"
#include "chat_client.hpp"


typedef std::deque<chat_message> chat_message_queue;


class Controller{
    public:
        Controller(Server& serv, View& v): server(serv), view(v){};
        void interface();
        void execute_cmd(int);
        void create_user();
        void remove_user();
        void user_to_mod();
/* working here*/    string  create_chatroom();
        void add_user_to_chatroom();
        void remove_chatroom();

        void attempt_delete(chat_client & c);
        void reset_header(chat_client & c);

        void attempt_ban(chat_client & c, char nick[24]);

        void update_server(chat_client & c);
        void join(chat_client & c);
        void join_chatroom(chat_client& c);
        int test();
       //char* getNickname();
    private:
        Server& server;
        View& view;
        //chat_client& client;
};
