#include "window.h"


//global main window
void Window::start(){
    //cbreak();
    initscr();
    raw();
    //noecho();

    int main_height= 100;
    int main_width = 300;
    int start_y = 0, start_x = 0;

    //for the username window
    int user_height = main_height/4;
    int user_width = main_width/4;
    int user_y_start = main_height/8 + 20;
    int user_x_start = main_width/2 - main_width/8;

    //for input window
    int input_height = user_height/5;
    int input_width = user_width * .95;
    int input_y = 51;
    int input_x = 115;

    char username[80];
    int valid_username;

    WINDOW* main_win = newwin(main_height,main_width,start_y,start_x);
    WINDOW* user_name_window = newwin(user_height, user_width, user_y_start , user_x_start);
    WINDOW* input_window = newwin(input_height, input_width, input_y, input_x);
    refresh();
    box(main_win, 0 , 0);
    box(user_name_window, 0, 0);
    box(input_window, 0, 0);
    mvwprintw(user_name_window, 1, 25, "ENTER USERNAME");
    mvwprintw(main_win, 20, (main_width/2)- (main_width/8) + 23, "WELCOME TO SUPER CHAT");
    refresh();

    wrefresh(main_win);
    wrefresh(user_name_window);
    wrefresh(input_window);

    do{
        wmove(input_window, 1, 1);
        wrefresh(input_window);
        //getch();
        wgetstr(input_window, username);
        valid_username = controller.check_Username(username);

        if(valid_username == 2){
            mvwprintw(user_name_window, 1, 25, view.too_long_prompt().c_str());
            wrefresh(user_name_window);
            wclear(input_window);
            box(input_window,0,0);
            wmove(input_window,1,1);
            wrefresh(input_window);
        }
        if(valid_username == 3){
            mvwprintw(user_name_window,1,25,view.user_already_exists().c_str());
            wrefresh(user_name_window);
        }

    }while(valid_username != 1);

    wclear(input_window);
    wrefresh(input_window);
    wclear(user_name_window);
    wrefresh(user_name_window);
    delwin(user_name_window);
    delwin(input_window);
    box(main_win, 0, 0);
    wrefresh(main_win);

    main_page(username, main_win);
    endwin();
}

void Window::main_page(string username, WINDOW* main){
     controller.setup(username);
     wclear(main);
     wrefresh(main);
     box(main,0,0);
     wrefresh(main); 
     //test_controller();
     getch();
}

void Window::test_controller(){
    string current_users = view.view_current_users();
    WINDOW* main_win = newwin(100,300,0,0);
    refresh();
    box(main_win, 0 , 0);
    wrefresh(main_win);
    mvwprintw(main_win, 1,1,current_users.c_str());
    wrefresh(main_win);
    getch();
}

void Window::chatroom_window(/*string lobby_name, string username, WINDOW* chat_window*/){
	

	//User* user, WINODW* main
	string username = "Stephanie";
	string lobbyNameString = "MIKEISLAME";
	string currentUserString = "CURRENT USERS";
	string menuString = "MENU";
	//Begin NCurses
	initscr();
	raw();


	int starty, startx;
	starty = startx = 0;
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	box(stdscr, 0, 0);
	refresh();

	//setting up what will be in sendMessageBox
	string userMessageName = username + ": ";
	char text[80];
	string textString;


	//window for sending messsages in lobby	
	WINDOW* sendMessageBox = newwin((yMax/10), (xMax/3)*2, yMax-6, startx+2);
	WINDOW* messageBox = newwin((yMax/17)*16, (xMax/3)*2, 1, 2);
	WINDOW* currentUserBox = newwin((yMax/17)*15, (xMax/7)*2, 1, xMax-31);
	WINDOW* menuBox = newwin((yMax/10)*1.7, (xMax/7)*2, yMax-9, xMax-31);
	WINDOW* banUserBox = newwin(yMax/10*1.7, (xMax/7)*2, yMax-9, xMax-31);

	box(sendMessageBox, 0, 0);	
	box(messageBox, 0, 0);
	box(currentUserBox, 0, 0);
	box(menuBox, 0, 0);
	
	getmaxyx(currentUserBox, yMax, xMax);
	mvwprintw(currentUserBox, 1, (xMax/2)-(currentUserString.size()/2), currentUserString.c_str());
	getmaxyx(messageBox, yMax, xMax);
	mvwprintw(messageBox, 1, (xMax/2)-(lobbyNameString.size()/2), lobbyNameString.c_str());
	getmaxyx(menuBox, yMax, xMax);
	mvwprintw(menuBox, 1, (xMax/2)-(menuString.size()/2), menuString.c_str());
	mvwprintw(menuBox, 3, 1, "1 - Ban User");
	mvwprintw(menuBox, 4, 1, "0 - Exit Chatroom");
	mvwprintw(menuBox, 5, 1, "[TAB] - Message/Menu Mode");	
	mvwprintw(sendMessageBox, 2, 2, userMessageName.c_str());
	
	// settiing up the windows for display
	wrefresh(sendMessageBox);
	wrefresh(messageBox);
	wrefresh(currentUserBox);
	wrefresh(menuBox);	

	int i = 2, menuMode = 0, chatMode = 1, modeSwitch;
	do{
		mvwprintw(currentUserBox, 2, 1, username.c_str());
		wrefresh(currentUserBox);
		curs_set(false);
		while(chatMode){
			//curs_set(false);
			noecho();
			modeSwitch = wgetch(menuBox);
			while(modeSwitch != 9){

				echo();
				box(sendMessageBox, 0, 0);
				mvwprintw(sendMessageBox, 2, 2, userMessageName.c_str());
				wmove(sendMessageBox, userMessageName.size(), 2);
				curs_set(true);	
				wgetstr(sendMessageBox, text);
				textString = text;
				modeSwitch = textString.front();
				wclear(sendMessageBox);
				box(sendMessageBox, 0, 0);
				wrefresh(sendMessageBox); //refresh to view blank screen
				if(textString.front() != 9){
					mvwprintw(messageBox, i, 1, userMessageName.c_str());
					mvwprintw(messageBox, i, userMessageName.size()+1, text); //print what is being written in the messages window
					wmove(messageBox, i++, 1);}
				wrefresh(messageBox);
			}
			if(modeSwitch == 9){
				chatMode = 0;
				menuMode = 1;
				werase(sendMessageBox);
				wrefresh(sendMessageBox);
				
			}
			if(modeSwitch == 27){
				chatMode = 0;
				menuMode = 0;
			}
		}
		while(menuMode){
			curs_set(false);
			noecho();
			getmaxyx(menuBox, yMax, xMax);
			mvwprintw(menuBox, 1, (xMax/2)-(menuString.size()/2), menuString.c_str());
			mvwprintw(menuBox, 3, 1, "1 - Ban User");
			mvwprintw(menuBox, 4, 1, "0 - Exit Chatroom");
		       	mvwprintw(menuBox, 5, 1, "[TAB] - Message/Menu Mode");	
			box(menuBox, 0, 0);
			wrefresh(menuBox);
			modeSwitch = wgetch(menuBox);
			//when tab is pressed
			if(modeSwitch == 9){
				chatMode = 1;
				menuMode = 0;
				werase(menuBox);
				wrefresh(menuBox);
				box(sendMessageBox, 0, 0);
				mvwprintw(sendMessageBox, 2, 2, userMessageName.c_str());
				wmove(sendMessageBox, userMessageName.size(), 2);
				wrefresh(sendMessageBox);
			}
			if(modeSwitch == 27){
				chatMode = 0;
				menuMode = 0;
			}
			//ban user
			if(modeSwitch == 49){
				werase(menuBox);
				box(banUserBox, 0, 0);
				wrefresh(menuBox);
				wrefresh(banUserBox);

			}
			if(modeSwitch == 48){
				//exit chatroom
			}
		}
		

		//This is working properly
		//Just trying to fix other things

		

		/*mvwprintw(currentUserBox, 2, 1, username.c_str());
		wrefresh(currentUserBox);
		mvwprintw(sendMessageBox, 2, 2, userMessageName.c_str());
		wmove(sendMessageBox, userMessageName.size(), 2);	
		box(sendMessageBox, 0, 0);
		wgetstr(sendMessageBox, text);
		wclear(sendMessageBox);
		wrefresh(sendMessageBox); //refresh to view blank screen
		mvwprintw(messageBox, i, 1, userMessageName.c_str());
		mvwprintw(messageBox, i, userMessageName.size()+1, text); //print what is being written in the messages window
		wmove(messageBox, i++, 1);
		wrefresh(messageBox);
		*/
		
	}while(true);

	getch();
	endwin();
}

//demo.c #include <ncurses.h> #include <unistd.h> int main(int argc, char *argv[]) { int parent_x, parent_y; int score_size = 8; initscr(); noecho(); curs_set(FALSE); // get our maximum window dimensions getmaxyx(stdscr, parent_y, parent_x); // set up initial windows WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0); WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows mvwprintw(field, 0, 0, "Field"); mvwprintw(score, 0, 0, "Score"); // refresh each window wrefresh(field); wrefresh(score); sleep(5); // clean up delwin(field); delwin(score); endwin(); return 0; }
