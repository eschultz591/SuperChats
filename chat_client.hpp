#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <cstring>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "chat_message.hpp"
//#include "chat_server.hpp"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

typedef std::deque<chat_message> chat_message_queue;
struct CR {bool isLobby; char s[24]; int crn; bool hasMod; char modN[24];vector<string> banned; int user_count = 0;;
 /*static const char* const banned[30];*/ /*vector< char *> banned;*/};
struct user{char s[24];};

class chat_client
{
public:
char currCR = '0';
char ucount1 = '0';
char ucount2 ='0';
char headT[4] ="000";
char name[24];
char CurrentChatroom[24];

vector<CR> ChatRooms;
vector<user> users;

  chat_client(io_context& io_context,
      const tcp::resolver::results_type& endpoints)
    : io_context_(io_context),
      socket_(io_context)
  {
    do_connect(endpoints);
  }

    void user_movement(char msgd[50])
    {

        stringstream before;
        stringstream after;

        before << msgd[6];
        after << msgd[7];

        int past_cr;
        int future_cr;
        after >> future_cr;
        before >> past_cr;


        //std::cout<< "past_cr str " <<msgd[7] <<"future_cr str"<<msgd[6];

        //std::cout<< "past_cr" <<past_cr <<"future_cr"<<future_cr;

        if(!ChatRooms[past_cr].isLobby)
        {ChatRooms[past_cr].user_count--;}

        if(!ChatRooms[future_cr].isLobby)
        {ChatRooms[future_cr].user_count++;}
    }

    void attempt_delete(char msgd[50])
    {
           std::cout << msgd;

        int x = 0;
        char i = msgd[8+x];
        char cr_name[24];
        int a = 0;
        while (i != ' ')
        {


        i = msgd[8+x];
        x++;
        }

        //x++;
        i = msgd[8+x];
        while (i != ' ')
        {
        cr_name[a] = i;

        a++;
        x++;
        i = msgd[8+x];

        }

        for (auto x : ChatRooms)
        {
            if(strcmp(x.s,cr_name) == 0 &&x.isLobby==false && x.user_count == 0)
            {
                std::cout << "will delete I promise";
            }
        }


    }

    void RemoveSpace(char * p)
    {
        if (NULL == p)
            return;

            int n = 0;

            for (int i = 0; i < strlen(p); i++)
            {
                if (p[i] != ' ')
                    p[n++] = p[i];
            }
            p[n] ='\0';
    }


   /* void ban_user()
    {
    }*/
    bool BannedFromChat(char msgd[50])
    {

   // char bannedU[24] ="frank";
   // char bannedFrom = '2';
        char cr = msgd[4];
         int cr1 = cr - '0';
        int x = 0;
        char i = msgd[8+x];
        char BN[24];
        //std::cout<<msgd;

        std::cout << "("<<ChatRooms[cr1].user_count<<")";
        while ( i != '\0')
            {
                BN[x] = msgd[8+x];
            x++;
             i = msgd[8+x];
            }
          //  std::cout << "here"<< BN<<"]";
            RemoveSpace(BN);
           // std::cout << bannedFrom <<"=" <<cr;

            int y=0;
            int z=0;

            if (ChatRooms.size() > 0)
            {
            /*for (x = 0; x < ChatRooms[cr1].banned.size(); x++)
            {
                std::cout << ChatRooms[cr1].s;
                 std::cout << ChatRooms[cr1].banned[x];

            }*/
            //string BName = BN;
            for(auto x : ChatRooms[cr1].banned)
            {
                //std::cout << "("<<x<<")"<<"=="<<BN;
                if(strcmp(x.c_str(), BN) == 0)
                {
                    //std::cout <<"BANNED";
                    return true;
                }
            }
            }

            /*if (bannedFrom == cr && strcmp(bannedU, BN) == 0)
            { return true;}*/
            //std::cout << "you are not banned";
            return false;


    }
    void ban_user(char msgd[50])
    {
        char cr = msgd[4];

        int cr1 = cr - '0';

        char name1[24] ="";
        char name2[24] ="";
        int x = 0;
        int a = 0;
        char i = msgd[8];
        string banned;
        //user BU;
        //ChatRooms[cr1].user BU;


        while ( i != ' ')
            {
                name1[x] = msgd[8+x];

    //  std::cout <<"\here:: " << CN <<"\n";

            x++;
             i = msgd[8+x];

            }
        //x++;

        //i = msgd[8+x];
        do
        {
            name2[a] = msgd[8+x];
            x++;
            a++;
            i = msgd[8+x];

        }while(i != ' ');
        if(strcmp(name1,ChatRooms[cr1].modN) == 0)
        {
            RemoveSpace(name2);
            //strcpy(BU.s, name2);

            std::cout << " you are the mod banning: "<< name2 <<"\n";
            banned = name2;
            ChatRooms[cr1].banned.push_back(banned);
            //ChatRooms[cr1].banned.push_back(BU);
            a = 0;
            /*while()
            for(a = 0; a < ChatRooms[cr1].banned.size(); a++)
            {
                if ( ChatRooms[cr1].banned.size() == 1)
                {
                    ChatRooms[cr1].banned[a] = name2;
                }
            }*/

            std::cout <<"this guy is banned" <<   ChatRooms[cr1].banned[0];
        }


        return;
    }
    void add_user(char msgd[600])
    {/*
int d = 0;
int x = 0;
        //char test[24];
        //strcpy(test,"test");
        user U;
        //strcpy(U.s,test);
        int b = 0;
        char i = msgd[x];
        char CN[24] = "";
    for (d =0; d< strlen(msgd); d++)
    {

        if (i ==' ')
        {x++;}
        if(x>4)
        {

          if(i ==':')
            {std::cout<<"===";
 strcpy(U.s, CN);
    users.push_back(U);
    // if (users.size() < 0)
      headT[0] ='0';}


        CN[d] = msgd[d];
        std::cout<<CN[d]<<"\n";
        }
        i = msgd[d];

    }*/


        int x = 0;
        //char test[24];
        //strcpy(test,"test");
        user U;
        //strcpy(U.s,test);

        char i = msgd[7+x];
        char CN[24] = "";
        while ( i != ' ')
            {
                CN[x] = msgd[7+x];

    //  std::cout <<"\here:: " << CN <<"\n";


            x++;
             i = msgd[7+x];
            }
        strcpy(U.s, CN);
    users.push_back(U);
    // if (users.size() < 0)
      headT[0] ='0';
    //for(auto x : users)
    //   {
    //        std::cout << "user created!"<<x.s <<"\n";
    //    }
    }

    void create_lobby()
    {

        if (ChatRooms.size() > 0 && ChatRooms[0].isLobby == true)
        {return;}
        CR Lobby;
        Lobby.isLobby = true;
        strcpy(Lobby.s, "Lobby");
        ChatRooms.push_back(Lobby);
        return;
    }

    char * CreateCR(char msgd[50])
    {int x = 0;
            CR CRT;
            strcpy(CRT.s,"");
            char CRN[24] = "";
            char CRN2[24] = "";

            char i = msgd[8+x];
            while ( i != ' ')
            {
                CRN[x] = msgd[8+x];

            x++;
             i = msgd[8+x];
            }
            strcpy(CRT.s, CRN);
            RemoveSpace(CRT.s);
            x++;
            int a =0;
            i = msgd[8+x];
            while ( i != ' ')
            {
                CRN2[a] = msgd[8+x];

            a++;
            x++;
             i = msgd[8+x];
            }
            strcpy(CRT.modN, CRN2);
            //strcpy(CRT.s, CRN);
            RemoveSpace(CRT.modN);
            CRT.hasMod = true;

                 /*       if (CRT.hasMod == false)
            {
            std::cout << "BEEP BEEP YOU ARE NOW MOD \n";
            CRT.hasMod = true;
            strcpy(CRT.modN, name );
            isMod = 'M';
            }*/
           // strcpy(CurrentChatroom, CRT.s);
            ChatRooms.push_back(CRT);
            /*int b = 0;
            for (auto x : ChatRooms)
            {
                if(strcmp(CRT.s,x.s) == 0)
                {
                //strcpy(currCR, b);
                currCR = '0' + b;
                //itoa(b, currCR, 10);
                return CRT.s;
                }
                b++;
            }*/std::cout << "chatroom created\n";

            return CRT.s;
    }

   void ChangeCR(char cr[24])
   {
   //strcat(cr," ");
  // RemoveSpace(cr);
   std::cout << "\n1)" << ChatRooms[0].s;
        std::cout << "\n2)" << ChatRooms[1].s;
        std::cout << "\n3)" << ChatRooms[2].s << "\n";

   for(int x = 0; x <ChatRooms.size(); x++){
          //  RemoveSpace(ChatRooms[x].s);
            std::cout << cr << "==" << ChatRooms[x].s <<"||";
        if (strcmp(cr, ChatRooms[x].s) ==0){
            currCR = x;
            std::cout <<"joining : " << ChatRooms[x].s;
            /*if (ChatRooms[x].hasMod == false)
            {
            std::cout << "BEEP BEEP YOU ARE NOW MOD \n";
            ChatRooms[x].hasMod = true;
            isMod = 'M';
            }*/
            std::cout << "("<<ChatRooms[x].modN<<")";
            return;
            }

   }
std::cout << "No chatroom with that name \n";
return;
}



  void write(const chat_message & msg)
  {

    post(io_context_,
        [this, msg]()
        {
          bool write_in_progress = !write_msgs_.empty();
          write_msgs_.push_back(msg);
          if (!write_in_progress)
          {
            do_write();
          }

        });


  }

  void close()
  {
    post(io_context_, [this]() { socket_.close(); });
  }

private:
  void do_connect(const tcp::resolver::results_type& endpoints)
  {
    async_connect(socket_, endpoints,
        [this](std::error_code ec, tcp::endpoint)
        {
          if (!ec)
          {
            do_read_header();
          }
        });
  }

  void do_read_header()
  {
    async_read(socket_,
        buffer(read_msg_.data(), chat_message::header_length),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {


                do_read_body();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_read_body()
  {
    async_read(socket_,
        buffer(read_msg_.body(), read_msg_.body_length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {

          if (!ec)
          {

            //std::cout << read_msg_.data();
            if (read_msg_.data()[5] == 'B')
              {
              ban_user(read_msg_.data());
              }
              if (read_msg_.data()[5] == 'D')
              {
              attempt_delete(read_msg_.data());
              }
              if (read_msg_.data()[5] == 'L')
              {
              create_lobby();
              }
            if (read_msg_.data()[5] == 'S')
            {
            char cr[24];
            //CurrentChatroom = CreateCR(read_msg_.data());
            CreateCR(read_msg_.data());
            //ChangeCR(CurrentChatroom);
            //std::cout << "test";
            }
            if (read_msg_.data()[4] == currCR && read_msg_.data()[5] != 'S' &&read_msg_.data()[5] != 'L' && !BannedFromChat(read_msg_.data())){
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";}

            if ( read_msg_.data()[5] == '1')
            {user_movement(read_msg_.data());}
            do_read_header();
              if ( read_msg_.data()[7] == 'A')
                        std::cout << ChatRooms[currCR].modN;
              if (read_msg_.data()[5] == 'C')
              {
              //std::cout << read_msg_.data();
                add_user(read_msg_.data());
              }

              //reset_header();
          }


          else
          {
            socket_.close();
          }
        });
  }

  void do_write()
  {
    async_write(socket_,
        buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this](std::error_code ec, std::size_t )
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            socket_.close();
          }
        });
  }



void reset_header()
{
    for(int b = 0; b <= 50; b++)
                {
                    headT[b] ='\0';
                }
}
















private:
  io_context& io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};
