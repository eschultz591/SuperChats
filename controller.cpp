#include "controller.h"


void Controller::interface(){
    int cmd = 0;

        cout << view.get_menu();
        cout <<"";

    test();
}

int Controller::test()
{
		cout <<"the now ide is working";

    char l;
	char chat_name[24];
	char target[25];
    char time_buffer[32];
    time_t t_;
    bool joined = false;
    strftime(time_buffer, 32, "%c", localtime(&t_));
    char nick[24];
    string temp1;
    int chatroomNumber = 0;
    char head[50] ="000";
    cout << "Welcome to SuperChat!\n\nPlease enter a nick to begin: \n";
    cin >> nick;

    io_context io_context;


    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1234");

    chat_client c(io_context, endpoints);
    reset_header(c);
    strcpy(c.name,nick);
    c.headT[0] = c.currCR;
    c.headT[1] = '0';
    c.headT[2] = c.ucount1;
    c.headT[3] = c.ucount2;
    strcat(c.headT, c.name);

    //strcat(c.headT, nick );
    //strcat(head, nick);


    string name;

    std::thread t([&io_context](){ io_context.run(); });
    char formatted_message[chat_message::max_body_length + chat_message::header_length + 1];

    char line[chat_message::max_body_length +chat_message::header_length + 1];
    std::cout << "Welcome to the main lobby! \n\n" << std::endl;
     update_server(c);



    //join(c);
   // strcpy(c.headT,"");

     c.headT[1] = 'L';

    while (std::cin.getline(line, chat_message::max_body_length + 1))
    {
                     update_server(c);


                //strcpy(c.name, "");


/* if (joined == false)
        {  c.headT[1] ='C';
        //strcat(c.headT, c.name );
            joined = true;
        }*/


        /*if(c.headT[1] == 'C')
        {

      chat_message msg2;
      msg2.body_length(std::strlen(formatted_message));
      std::memcpy(msg2.body(), formatted_message, msg2.body_length());

    msg2.set_header(c.headT);
    msg2.encode_header();
        //cout << c.headT << "";

      c.write(msg2);
        cout << msg2.data();

       strcpy(c.headT,"");
      temp1 ="";
        c.headT[0] = c.currCR;

                c.headT[1] = '0';
                c.headT[2] = c.currCR;
                c.headT[3] = c.isMod;



        }*/
      if (line[0] == '#')
      {
        switch (line[1])
        {

            case '1':
            reset_header(c);
            attempt_ban(c, nick);
            break;
        case '2':
            attempt_delete(c);
            break;
        case '3':
           c.headT[1] ='C';
            strcat(c.headT, nick );
            //user_to_mod();
            break;
        case '4':
            view.view_current_users();
            break;
        case '5':
            name;

        reset_header(c);


        view.chatroom_name_prompt();
        cin >> name;
           temp1 = name; //= create_chatroom();
           //c.headT[3 + sizeof(nick)]

           strcat(c.headT, temp1.c_str() );
            strcat(c.headT, " ");
            strcat (c.headT, nick);
           c.headT[1] = 'S';
            temp1 = "";
            break;
        case '6':
            view.view_chatrooms();
            break;
        case '7':
            add_user_to_chatroom();
            break;
        case '8':
            join_chatroom(c);
            //remove_chatroom();
            break;


        case '9':

            cout << c.users.size();
            update_server(c);


        for(auto x : c.ChatRooms)
       {
            std::cout << "user created!"<<x.s <<"mod: "<<x.modN<<"\n";

        }



            /* char chatroom_name[24];
    view.chatroom_name_prompt();
    cin >> chatroom_name;
            c.ChangeCR(chatroom_name);
            c.isMod = 'A';*/
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
    //strcat(c.headT, c.name );
    msg.set_header(c.headT);
    msg.encode_header();
        //cout << c.headT << "";

      c.write(msg);

     strcpy(c.headT,"");
                temp1 ="";
                name = "";

             reset_header(c);
                         strcat (c.headT, nick);

                      //reset_header(c);

        //update_server(c);




       /* strcpy(c.headT,"");
      temp1 ="";
        c.headT[0] = c.currCR;
                c.headT[1] = '0';
                c.headT[2] = c.currCR;
                c.headT[3] = c.isMod;
*/
         update_server(c);

    }

    c.close();
    t.join();

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






void Controller::join_chatroom(chat_client & c){



    stringstream ts;
    string str;
    char cr;
    string chatroom_name;
    int position = 0;
    bool foundChat = false;
    view.chatroom_name_prompt();
    cin >> chatroom_name;
    int b = 0;
    int cur_cr;


     for(auto&& x : server.get_chatrooms()){
            if(x.first->get_name() == chatroom_name){


               /* stringstream strValue;
                strValue << c.currCR;


                strValue >> cur_cr;

                //cur_cr = int(c.currCR);
                  cout <<"curcr = " << cur_cr;
                c.ChatRooms[cur_cr].user_count--;*/

                //x.first->add_user(user);

                c.headT[2] = c.currCR;
                c.headT[1] ='1';
                server.get_chatrooms().at(x.first) += 1;
                cr = '0' + b;
                c.currCR = cr;
                 c.headT[3] = cr;
                foundChat = true;
                //c.ChatRooms[b].user_count++;
                  std::cout<< "mod :" <<c.ChatRooms[b].modN <<"]";
                return;
    }b++;}


    cout<< "no chatroom with that name :(";
    return;


    /*int y = 0;
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

            char z = '0' + y;
               c.currCR = z;
            cout << "L EQUALS" << z << "===";
            c.headT[1] = z;
            }

 if(!foundChat){
        cout << "Chatroom not found.\n" << endl;
    }
y++;
}*/
}



void Controller::update_server(chat_client & c)
{
        if(c.ChatRooms.size() ==0)
        {return;}
      int z;
      int y;
      int b;
      cout << "HERE0  " << c.ChatRooms.size() << " "<<server.get_num_cr()<<"\n";
    if (c.ChatRooms.size() > server.get_num_cr())
    {
        cout << "HERE1  " << c.ChatRooms.size() << " "<<server.get_num_cr()<<"\n";
        z = c.ChatRooms.size() - server.get_num_cr();


        y = server.get_num_cr();

        for (y ; y < c.ChatRooms.size(); y++)
        {
            char name[24];
            strcpy(name, c.ChatRooms[y].s);
            Chatroom* chatroom = new Chatroom();
            chatroom->set_name(name);
            server.add_chatroom(chatroom);
        }
        }
     if (c.ChatRooms.size() < server.get_num_cr())
     {
        cout << "HERE2 " << c.ChatRooms.size() << " "<<server.get_num_cr()<<"\n";
        z = 0;
        y = 0;
        b = 0;
        char CR[24];
        bool goodCR = false;

            //for (b = 0; b < server.get_num_cr(); b++)
             for(auto&& x : server.get_chatrooms())
             {
                goodCR = false;
                for (z = 0; z < c.ChatRooms.size(); z++)
                {
                    cout << "server =" << x.first->get_name().c_str() <<"] client =" <<c.ChatRooms[z].s << "]\n";
                    if(strcmp(x.first->get_name().c_str(),c.ChatRooms[z].s) == 0)
                    {
                        strcpy(CR, x.first->get_name().c_str());
                        goodCR = true;
                    }
                }
                if (goodCR == false)
                {
                    cout <<"this cr is bad: " << CR<<" deleting it\n";
                    server.remove_chatroom(x.first);
                    break;
                }
            }


     }




  if (c.users.size() > server.get_num_usr())
    {
        y = server.get_num_usr();

          for (y ; y < c.users.size(); y++)
        {
            char name[24];
            strcpy(name, c.users[y].s);
            User* user = new User();
            user->setUsername(name);
            server.add_user(user);
        }

    }




}

void Controller::reset_header(chat_client & c)
{
    for(int b = 0; b <= 50; b++)
                {
                    c.headT[b] ='\0';
                }
                c.headT[0] = c.currCR;
                c.headT[1] = '0';
                c.ucount1 = '0';
                c.ucount2 = '0';
                c.headT[2] = c.ucount1;
                c.headT[3] = c.ucount2;
                strcat(c.headT,c.name);
        return;

}

void Controller::attempt_ban(chat_client & c,char nick[24])
{
        string bannie;
    view.username_prompt();
        cin >> bannie;
           strcat(c.headT, nick);
           strcat(c.headT, " ");
           strcat(c.headT, bannie.c_str());

           c.headT[1] = 'B';

}

void Controller::attempt_delete(chat_client & c)
{
    string name;
    view.chatroom_name_prompt();
    cin >> name;
    strcat(c.headT, " ");
    strcat(c.headT, name.c_str());
    strcat(c.headT, " ");

    c.headT[1] = 'D';
}
/*
void Controller::join(chat_client & c)
{
      char formatted_message[48+8+512 + 1];

      chat_message msg2;

      msg2.body_length(std::strlen(formatted_message));
      std::memcpy(msg2.body(), formatted_message, msg2.body_length());

    msg2.set_header(c.headT);
    msg2.encode_header();
        //cout << c.headT << "";

      c.write(msg2);



    strcpy(c.headT,"");

        c.headT[0] = c.currCR;
                 c.headT[1] = '0';
                 c.headT[2] = c.currCR;
                 c.headT[3] = c.isMod;



}
*/


