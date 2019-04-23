

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
  enum { header_length = 8 + 24};
  enum { max_body_length = 512 + header_length};
  char head[26];
  chat_message()
    : body_length_(0)
  {
  }

/*const char* header() const
  {
    return header_length;
  }*/


    void set_header(char heads[header_length])
    {
        //strcpy(head,"");
       //std::sprintf(head,"%s", heads);
        strcpy(head,heads);
           //std::sprintf(header, "%c%c", head,head1);

    }


  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  std::size_t length() const
  {
    return header_length + body_length_;
  }

  const char* body() const
  {
    return data_ + header_length;
  }

  char* body()
  {
    return data_ + header_length;
  }

  std::size_t body_length() const
  {
    return body_length_;
  }

  void body_length(std::size_t new_length)
  {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

  bool decode_header()
  {
    char header[header_length + 1] = "";
    std::strncat(header, data_, header_length);
    body_length_ = std::atoi(header);
   // body_length_ = 4;
   // body_length_ = 50;
    if (body_length_ > max_body_length)
    {
      body_length_ = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {

    char header[header_length + 1];
    //char head[header_length + 1] = "";
    //strcpy(head, header);
    //strcpy(head, header);
    //std::sprintf(header, "%c%c", head,head1);
    std::sprintf(header, "%-4d%-26s", static_cast<int>(body_length_), /*strlen(head),*/ head);
   // std::sprintf(header, "%4d",static_cast<int>(body_length_));
  //  strcat(header,head);
    std::memcpy(data_, header, header_length);
    //strcpy(data_, header);
  }

private:
  char data_[header_length + max_body_length];
  std::size_t body_length_;
};

#endif // CHAT_MESSAGE_HPP
