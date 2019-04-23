

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
struct CR {char s[24]; int crn;};
class chat_client
{
public:
//char CRN[26];
char currCR = '0';
char headT[4] ="000";
char name[24];
vector<CR> ChatRooms;
/*
char * header_;


void header_set(char * h)
{
    strcpy(header_,h);
}

*/
    /*chat_client()
    {
    io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1234");
    socket_(io_context)
    {
        do_connect(endpoints);
    }
    }*/
  chat_client(io_context& io_context,
      const tcp::resolver::results_type& endpoints)
    : io_context_(io_context),
      socket_(io_context)
  {
    do_connect(endpoints);
  }


   /*chat_client("127.0.0.1", "9000"): io_context_(io_context), socket_(io_context)
   {
    do_connect(endpoints);
   }*/
    void CreateCR(char msgd[30])
    {int x = 0;
        std::cout << "(" << msgd << ")\n\n";
            CR CRT;
            strcpy(CRT.s,"");
            char CRN[24] = "";
            //memset(CRN,'0',26);
            char i = msgd[8+x];
            while ( i != ' ')
            {
                CRN[x] = msgd[8+x];
               // std::cout << " here1 " << CRN[x];
               // CRT.s[x] = read_msg_.data()[7+x];
                              //  std::cout << "HERE" << CRT.s[x];
                                          std::cout <<"\here:: " << CRN <<"\n";

                i = msgd[8+x];
            x++;
            }
            strcpy(CRT.s, CRN);
          //  memset(CRN,'\0',26);
            std::cout <<"\here:: " << CRN <<"\n";

            ChatRooms.push_back(CRT);
            return;
    }

   void ChangeCR(char cr[24])
   {
   strcat(cr," ");
   std::cout << "\n1)" << ChatRooms[0].s;
        std::cout << "\n2)" << ChatRooms[1].s;
        std::cout << "\n3)" << ChatRooms[2].s << "\n";

   for(int x = 0; x <ChatRooms.size(); x++){
          int  y = 0;

            std::cout << cr << "==" << ChatRooms[x].s ;
      //  std::cout << "HERER" << ChatRooms[x+1].s <<"\n";
        if (strcmp(cr, ChatRooms[x].s) ==0){
            currCR = x;
            std::cout <<"joining : " << ChatRooms[x].s;
            return;
            }
    y++;
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


        //std::cout << msg.data();
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
            //if (read_msg_.data()[5] == currCR){/*do_read_body();*/ std::cout<<"heeere"<<currCR;} //std::cout << read_msg_.data()[6];
                //else{
                //std::cout << "not gonna read";
                //return;
                //}
            //if (read_msg_.head[1] == '1')
            //{std::cout << "ERRORERROR"; do_read_body();}

          //  std::cout.write(read_msg_.data(),read_msg_.header_length);

            //std::cout.write(read_msg_.data(), chat_message::header_length);
            //{
                //do_read_body();

                do_read_body();
            //}
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
            //if (read_msg_.data()[5] == currCR){std::cout << "|||||| in cr |||||";}
            //std::cout << read_msg_.data();
            if (read_msg_.data()[6] == currCR){
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";}
            if (read_msg_.data()[5] == 'S')
            { std::cout << "chatroom created";
            CreateCR(read_msg_.data());
            std::cout << "test";
            /*int x = 0;
            CR CRT;
            strcpy(CRT.s,"");
            char CRN[26] = "";
            //memset(CRN,'0',26);
            char i = read_msg_.data()[7+x];
            while ( i != ' ')
            {
                CRN[x] = read_msg_.data()[7+x];
               // std::cout << " here1 " << CRN[x];
               // CRT.s[x] = read_msg_.data()[7+x];
                              //  std::cout << "HERE" << CRT.s[x];
                i = read_msg_.data()[7+x];
            x++;
            }
            strcpy(CRT.s, CRN);
          //  memset(CRN,'\0',26);
            std::cout <<"\nhere" << CRN <<"\n";

            ChatRooms.push_back(CRT);*/
            }
             //headT[1] = currCR;
            do_read_header();
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
        [this](std::error_code ec, std::size_t /*length*/)
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



















private:
  io_context& io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

/*
PASTE HERE
*/
