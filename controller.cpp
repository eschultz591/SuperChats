#include "controller.h"


void Controller::interface(){
    int cmd = 0;

   // do{
        cout << view.get_menu();
       // cin >> cmd;
        cout <<"";
        //execute_cmd(cmd);

  //  } while(cmd != 0);
    test();
}
/*
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
            //char n[25];
           // n= getNickname();
            test();
            break;
    }
}
*/
/*
char* Controller::getNickname(char name[25])
{
    char* nick[];
     cout << "Welcome to SuperChat!\n\nPlease enter a nick to begin: ";
    //cin.getline (nick, 25);
    cin.getline (nick,25);
    return nick;

}*/
int Controller::test()
{
   // cout << "HERHEHREHREHHERHREH";

   // int Run(/*int argc, char* argv[]*/)
//{
  /*try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }*/
    char l;
	char chat_name[24];
	char target[25];
    char time_buffer[32];
    time_t t_;
    strftime(time_buffer, 32, "%c", localtime(&t_));
    char nick[24];
    string temp1;
    int chatroomNumber = 0;
    char head[4] ="123";
    cout << "Welcome to SuperChat!\n\nPlease enter a nick to begin: \n";
    cin >> nick;
    //cin.getline (nick, 25);

    io_context io_context;

    //tcp::resolver resolver(io_context);
   // auto endpoints = resolver.resolve(argv[1], argv[2]);
    /*TEST TCP VERSION*/
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1234");

    chat_client c(io_context, endpoints);
    strcpy(c.name,nick);
    //memcpy(c.headT, nick, 30);
    //strcat(c.headT, nick);
    std::thread t([&io_context](){ io_context.run(); });
    char formatted_message[chat_message::max_body_length + chat_message::header_length + 1];
    // create a date and time string, copy into formatted_message, concatenate nick, then concatenate msg
    char line[chat_message::max_body_length +chat_message::header_length + 1];
    std::cout << "Welcome to the main lobby! \n\n" << std::endl;
    while (std::cin.getline(line, chat_message::max_body_length + 1))
    {


      if (line[0] == '#')
      {
        switch (line[1])
        {

            case '1':
                //strcpy(head, "123");
                //c.currCR ='2';
                strcpy(head,"223");
                c.headT[0] ='2';
            //create_user();
            break;
        case '2':
            c.currCR ='1';
            c.headT[0] = '1';
            //remove_user();
            break;
        case '3':
            user_to_mod();
            break;
        case '4':
            view.view_current_users();
            break;
        case '5':
            //char temp[24];
           temp1 = create_chatroom();

           strcat(c.headT, temp1.c_str() );
           c.headT[1] = 'S';

            break;
        case '6':
            view.view_chatrooms();
            break;
        case '7':
            add_user_to_chatroom();
            break;
        case '8':
            //cout << "HERE" <<c.ChatRooms[0].s;
            remove_chatroom();
            break;


        case '9':
    /*    view.chatroom_name_prompt();
    cin >> chat_name;
            c.ChangeCR(chat_name);*/
             /*l = join_chatroom(c);
            c.currCR = l;
            cout << "L EQUALS" << l << "   ===";
            c.headT[1] = l;*/
             char chatroom_name[24];

    view.chatroom_name_prompt();
    cin >> chatroom_name;
            c.ChangeCR(chatroom_name);
            break;

        }

      }


      t_ = time(NULL);
     strftime(time_buffer, 32, "%c", localtime(&t_));
     sprintf(formatted_message, "%s %s: ", time_buffer, nick);
      std::strcat(formatted_message, line);
      chat_message msg;
      msg.body_length(std::strlen(formatted_message));
      std::memcpy(msg.body(), formatted_message, msg.body_length());
     // std::memcpy(msg.header, head, msg.header_length);
      //strcpy(head, "123");
        //c.header_set(head);
        //strcpy(head, "789");
        //strcpy(msg.header, "789");
    msg.set_header(c.headT);
    msg.encode_header();
    //std::cout << "/n";
   // std::cout.write(msg.data(),msg.header_length);
  //  std::cout << "/n";
      c.write(msg);
strcpy(c.name,"");
            strcpy(c.headT,"");
      temp1 ="";
        c.headT[0] = c.currCR;
                c.headT[1] = c.currCR;
                c.headT[2] = c.currCR;
                c.headT[3] = c.currCR;

      //update formatted_message with date and time
      //c.headT[1] = c.currCR;

    }

    c.close();
    t.join();
   // return 0;
  //}
 /* catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
*/
    return 0;
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

        for(auto&& x : server.get_chatrooms()){
            if(x.first->get_name() == chatroom_name){
                x.first->add_user(user);
                server.get_chatrooms().at(x.first) += 1;
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
/*working here*/
string Controller::create_chatroom(){
    string name;
    view.chatroom_name_prompt();
    cin >> name;
    Chatroom* chatroom = new Chatroom();
    chatroom->set_name(name);
    server.add_chatroom(chatroom);

    return name;
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






char Controller::join_chatroom(chat_client & c){
    int y = 0;
    stringstream ts;
    std::string str;
 string chatroom_name;
    int position = 0;
    bool foundChat = false;
    view.chatroom_name_prompt();
    cin >> chatroom_name;
    //c.ChatRooms
    for(auto x : server.get_chatrooms()){
        if (x.first->get_name() == chatroom_name){
            foundChat = true;
            //ts << y;
            //str = ts.str();
          //  const char* cs = str.c_str();
            //strcpy(c->headT, str.c_str());
            //c->currCR = (char)y;
            //strcpy(c->currCR ,str.c_str());
            //char z = itoa(y);
            char z = '0' + y;
               c.currCR = z;
            cout << "L EQUALS" << z << "   ===";
            c.headT[1] = z;
           //return z;
            }

 if(!foundChat){
        cout << "Chatroom not found.\n" << endl;
    }
y++;
}
}

