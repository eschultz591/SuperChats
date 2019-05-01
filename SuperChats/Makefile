CXXFLAGS = -std=c++11

all: executable

executable: main.o view.o server.o controller.o user.o chatroom.o message.o window.o
	$(CXX) $(CXXFLAGS) main.o view.o server.o controller.o user.o chatroom.o message.o window.o -lncurses -lboost_system -lpthread -lboost_serialization
	./a.out

main.o: main.cpp controller.h chat_client.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -lboost_system -lpthread -lboost_serialization

controller.o: controller.cpp controller.h view.h chat_client.hpp
	$(CXX) $(CXXFLAGS) -c controller.cpp -lboost_system -lpthread -lboost_serialization

view.o: view.cpp view.h server.h
	$(CXX) $(CXXFLAGS) -c view.cpp

server.o: server.cpp server.h user.h chatroom.h
	$(CXX) $(CXXFLAGS) -c server.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c user.cpp

chatroom.o: chatroom.cpp chatroom.h user.h message.h
	$(CXX) $(CXXFLAGS) -c chatroom.cpp

message.o: message.h message.cpp
	$(CXX) $(CXXFLAGS) -c message.cpp

window.o: window.cpp window.h controller.h chat_client.hpp
	$(CXX) $(CXXFLAGS) -c window.cpp -lboost_system -lpthread -lboost_serialization


clean:
	rm -rf *.o

