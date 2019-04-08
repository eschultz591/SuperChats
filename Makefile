CXXFLAGS = -std=c++11

all: executable

executable: main.o view.o server.o controller.o user.o chatroom.o
	$(CXX) $(CXXFLAGS) main.o view.o server.o controller.o user.o chatroom.o
	./a.out

main.o: main.cpp controller.h
	$(CXX) $(CXXFLAGS) -c main.cpp

controller.o: controller.cpp controller.h view.h
	$(CXX) $(CXXFLAGS) -c controller.cpp

view.o: view.cpp view.h server.h
	$(CXX) $(CXXFLAGS) -c view.cpp

server.o: server.cpp server.h user.h chatroom.h
	$(CXX) $(CXXFLAGS) -c server.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c user.cpp

chatroom.o: chatroom.cpp chatroom.h user.h
	$(CXX) $(CXXFLAGS) -c chatroom.cpp

clean:
	rm -rf *.o

