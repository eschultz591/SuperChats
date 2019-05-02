#include "window.h"
#include <string>
#include <cstring>
//global main window

int main_height;
int main_width;

void Window::start(){
    User * user = new User();
    //cbreak();
    initscr();
    raw();
    //noecho();

    /*int main_height= 100;
    int main_width = 300;
    int start_y = 0, start_x = 0;
    
    */
    getmaxyx(stdscr,main_height,main_width);
    int start_y = 0, start_x = 0;


    //for the username window
    int user_height = main_height/4;
    int user_width = main_width/4;
    int user_y_start = main_height * .5;
    int user_x_start = main_width/2 - main_width/8;

    //for input window
    int input_height = user_width * .10;
    int input_width = user_width * .90;
    int input_y = user_y_start + user_height - input_height - 2;
    int input_x = user_x_start + 2;

    char username[80];
    int valid_username;

    WINDOW* main_win = newwin(main_height,main_width,start_y,start_x);
    WINDOW* user_name_window = newwin(user_height, user_width, user_y_start , user_x_start);
    WINDOW* input_window = newwin(input_height, input_width, input_y, input_x);
    refresh();

    box(main_win, 0 , 0);
    box(user_name_window, 0, 0);
    box(input_window, 0, 0);
    mvwprintw(user_name_window, 1, user_width/2-7, "ENTER USERNAME");
    mvwprintw(main_win, user_y_start- 5, (main_width/2)- 11, "WELCOME TO SUPER CHAT");
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
            wclear(user_name_window);
            wrefresh(user_name_window);
            box(user_name_window,0,0);
            mvwprintw(user_name_window, 1, user_width/2 - view.too_long_prompt().length()/2, view.too_long_prompt().c_str());
            box(user_name_window, 0, 0);
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

    user->setUsername(username);

    wclear(input_window);
    wrefresh(input_window);
    wclear(user_name_window);
    wrefresh(user_name_window);
    delwin(user_name_window);
    delwin(input_window);
    box(main_win, 0, 0);
    wrefresh(main_win);

    controller.setup(user);
    main_page(user, main_win);
    endwin();
}

void Window::main_page(User* user, WINDOW* main){

    //page set up
    wclear(main);
    wrefresh(main);
    box(main,0,0);
    wrefresh(main);

    int grid_height = main_height/2;
    int grid_width = main_width/2 - 4;
    char message[80], display[80], space[80] = {0};
    vector <string> message_list;
    string helper;
    string user_colon = user->getUsername() + ": ";
    string choices[5] = {"1 - Join Chat", "2 - Create Chat", "3 - Delete Chat", "4 - Change Username", "5 - Remove User from Superchat (Admin Priv.)"};

    WINDOW* chatroom_grid = newwin(grid_height, grid_width, 1, 1);
    WINDOW* lobby_grid = newwin(grid_height, grid_width, 1, main_width/2 + 2);


    //menu info just to make it easier for later
    int menu_height = grid_height/2+1;
    int menu_width = grid_width;
    int menu_x = grid_height + 1;
    int menu_y = 1;
    WINDOW* menu_grid = newwin(menu_height, menu_width, menu_x, menu_y);

    WINDOW* input_box = newwin(grid_height * .2+1, grid_width - 4, (grid_height - grid_height* .2) - 1, grid_width + 8);
    refresh();
    //wrefresh(main);
    box(chatroom_grid, 0, 0);
    box(lobby_grid, 0, 0);
    //box(menu_grid, 0, 0);
    box(input_box, 0, 0);
    wattron(chatroom_grid, A_BLINK); 
    mvwprintw(chatroom_grid, 1, grid_width / 2, "CHATROOMS"); 
    wattroff(chatroom_grid,A_BLINK); 
    mvwprintw(lobby_grid, 1, grid_width/2, "LOBBY");
    //mvwprintw(menu_grid, 1, grid_width/2, "MENU");
    mvwprintw(input_box, (grid_height* .2)/2, 1, user_colon.c_str());

    wmove(menu_grid,1,1);
    refresh();
    //wrefresh(main);    

    
    wrefresh(chatroom_grid);
    wrefresh(lobby_grid);
    wrefresh(menu_grid);
    wrefresh(input_box);
    refresh();
    wmove(menu_grid,2, 1);
    refresh();
    wrefresh(menu_grid);
    //keypad(menu_grid, true);
    int c;
    int highlight = 0;
    int selection;
    int menu_mode = 1, lobby_mode = 0, temp, esc_pressed = 0;

    //prints list the first time
/*    for(int i = 0; i < 4; i++){
        
        if(i == 0){
            wattron(menu_grid,A_REVERSE);
        }
        else
            wattroff(menu_grid,A_REVERSE);
        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
        
    }*/
    int i = 0;
    wrefresh(menu_grid);
    ostringstream output;
    noecho();
    //27 is the escape key 
    //While either chatroom mode or menu mode && esc key is not pressed
    while (lobby_mode || menu_mode)
    {
        int menu_printed = 0;

        while (lobby_mode){
            curs_set(true); 
            string display = view.view_chatrooms();
            mvwprintw(chatroom_grid, 2, 2, display.c_str());
            box(chatroom_grid, 0, 0);
            wrefresh(chatroom_grid);
            wmove(input_box, (grid_height*.2)/2, user->getUsername().size()+2);
            c = wgetch(input_box);
            echo();
            //if tab is pressed
            if(c == 9 ){
                //temp = menu_mode; 
                menu_mode = 1;
                lobby_mode = 0;
            }
            //if escape is pressed             
            if(c == 27 ){
                //turns off menu and chatroom mode, exiting the window
                lobby_mode = 0;
                menu_mode = 0;
            }
            if(c == 32){
                wgetstr(input_box, message);
                wclear(input_box);
                box(input_box, 0, 0);
                mvwprintw(input_box, (grid_height * .2) / 2, 1, user_colon.c_str());
                wrefresh(input_box);
                controller.add_message(message, user);
                string messages = controller.display_messages(user);
                mvwprintw(lobby_grid, 2, 2, messages.c_str());
                box(lobby_grid, 0, 0);
                box(input_box, 0, 0);
                wrefresh(lobby_grid);
                wrefresh(input_box);

                wmove(input_box, (grid_height*.2) / 2, user->getUsername().size()+2);
                wrefresh(input_box);
            } 


                wrefresh(input_box);
                wrefresh(lobby_grid);
                noecho();
        }
        while (menu_mode){
                string display = view.view_chatrooms();
                mvwprintw(chatroom_grid, 2, 2, display.c_str());
                box(chatroom_grid, 0, 0);
                wrefresh(chatroom_grid);
                noecho();
                if(!menu_printed)
                {
                    mvwprintw(menu_grid, 1, grid_width/2, "MENU");
                    box(menu_grid, 0, 0);
                    for(int i = 0; i < 5; i++){
                            wattroff(menu_grid,A_REVERSE);
                        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
                        } 
                   
                    }
                    int i = 0;
                    wrefresh(menu_grid);  
                     menu_printed = 1;   

                    
                
                wrefresh(chatroom_grid);
                curs_set(false);
                c = wgetch(menu_grid);
                //if tab is pressed
                if(c == 9){
                    //Turn off menu_mode and cha
                    //temp = menu_mode;
                    menu_mode = 0;
                    lobby_mode = 1;
                    werase(menu_grid);
                    wrefresh(menu_grid);
                } 
                //if escape is pressed
                else if(c == 27 ){
                    //turns off menu and chatroom mode, exiting the window
                    lobby_mode = 0;
                    menu_mode = 0;
                }
                //1 - Join Chatroom
                else if (c == 49){
                    wmove(menu_grid, menu_height -3, 1);
                    wclrtoeol(menu_grid);
                    wmove(menu_grid, menu_height -2, 1);
                    wclrtoeol(menu_grid);
                    box(menu_grid, 0, 0);
                    wrefresh(menu_grid);
                    int valid_chatname;
                    bool chatFull;
                    char chatname[80];
                    mvwprintw(menu_grid, menu_height - 2 , 2, view.chatroom_name_prompt().c_str());
                    wrefresh(menu_grid);
                    curs_set(true);
                    wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                    echo();


                    wgetstr(menu_grid, chatname);
                    do{
                        //this validates if the user entered the name of a chatroom that actually exists, and whether or not 10 or less people are in it.
                        valid_chatname = controller.checkChatName(chatname);
                        if(valid_chatname == 3){
                            mvwprintw(menu_grid, menu_height - 3, 2, view.chatroom_not_found_prompt().c_str());
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            echo();
                            wgetstr(menu_grid, chatname);
                        }
                        else if (valid_chatname == 2){
                            mvwprintw(menu_grid, menu_height - 3, 2, view.maxed_users_prompt().c_str());
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            echo();
                            wgetstr(menu_grid, chatname);
                        }
                        else{
                            controller.add_user_to_chatroom(user, chatname);
                            display = view.view_chatrooms();
                            mvwprintw(chatroom_grid, 2, 2, display.c_str());
                            box(chatroom_grid, 0, 0);
                            wrefresh(chatroom_grid);
                            wmove(menu_grid, menu_height -3, 1);
                            wclrtoeol(menu_grid);
                            wmove(menu_grid, menu_height -2, 1);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            chatroom_window(user, main);
                        }
                    }while(valid_chatname != 1);
                }
                //2 - Create Chatroom
                else if (c == 50){
                    wmove(menu_grid, menu_height -3, 1);
                    wclrtoeol(menu_grid);
                    wmove(menu_grid, menu_height -2, 1);
                    wclrtoeol(menu_grid);
                    box(menu_grid, 0, 0);
                    wrefresh(menu_grid);
                    int valid;
                    char chatname[80];
                    bool too_many = false;
                    mvwprintw(menu_grid, menu_height - 2 , 2, view.chatroom_name_prompt().c_str());
                    wrefresh(menu_grid);
                    curs_set(true);
                    wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                    echo();
                    
                    wgetstr(menu_grid, chatname);
                    do{
                        
                        //this validates whether the chatroom name already exists, or if 10 chatrooms has already been created.
                        valid = controller.validate_chatname(chatname);
                        if(valid == 2){
                            mvwprintw(menu_grid, menu_height - 3, 2, view.chatname_already_exists().c_str());
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            echo();
                            wgetstr(menu_grid, chatname);
                        }
                        else if (valid == 3){
                            mvwprintw(menu_grid, menu_height - 3, 2, view.maxed_chatrooms_prompt().c_str());
                            wmove(menu_grid, menu_height - 2, view.chatroom_name_prompt().size() + 2);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            valid = 1;
                        }
                        else{
                            controller.create_chatroom(chatname);
                            wmove(menu_grid, menu_height -3, 1);
                            wclrtoeol(menu_grid);
                            wmove(menu_grid, menu_height -2, 1);
                            wclrtoeol(menu_grid);
                            box(menu_grid, 0, 0);
                            wrefresh(menu_grid);
                            display = view.view_chatrooms();
                            mvwprintw(chatroom_grid, 2, 2, display.c_str());
                            box(chatroom_grid, 0, 0);
                            wrefresh(chatroom_grid);
                        }
                    }while(valid != 1);
                }
                //delete chat
                else if (c == 51){
                    bool user_status = user->getAdmin();
                    int chat_exists = controller.validate_chatname(user->get_room());

                    wmove(menu_grid, menu_height -3, 1);
                    wclrtoeol(menu_grid);
                    wmove(menu_grid, menu_height -2, 1);
                    wclrtoeol(menu_grid);
                    box(menu_grid, 0, 0);
                    wrefresh(menu_grid);



                    
                }

                else if (c == 52)
                {
                    char new_username[80];
                    int valid_username;
                    do{
                        wclrtoeol(menu_grid);
                        wrefresh(menu_grid);
                        wclear(menu_grid);
                        box(menu_grid, 0, 0);
                        mvwprintw(menu_grid, 1, grid_width/2-7, "ENTER USERNAME");
/*                        for(int i = 0; i < 5; i++){
                            wattroff(menu_grid,A_REVERSE);
                            mvwprintw(menu_grid, i + 2, 1, "                                              ");
                        } */
                        echo();
                        mvwprintw(menu_grid,2,1,view.username_prompt().c_str());
                        wmove(menu_grid, 2, view.username_prompt().size() + 2);
                        wgetstr(menu_grid, new_username);
                        valid_username = controller.check_Username(new_username);

                        if(valid_username == 2){
                            mvwprintw(menu_grid, 5, 1, view.too_long_prompt().c_str());
                            wrefresh(menu_grid);
                        }
                        if(valid_username == 3){
                            mvwprintw(menu_grid,5,1,view.user_already_exists().c_str());
                            wrefresh(menu_grid);
                        }

                    }while(valid_username != 1);
                    noecho();
                    user->setUsername(new_username);
                    werase(menu_grid);
                    wrefresh(menu_grid);
                    //Ensures menu prints again
                    menu_printed = 0;
                    //Resets name in Lobby (Names in chatroom should change everytime a chatroom is joined)
                    user_colon = user->getUsername() + ": ";
                    mvwprintw(input_box, (grid_height* .2)/2, 1, user_colon.c_str());
                    wrefresh(input_box);


                }
        }
    }
}

void Window::chatroom_window(User*user, WINDOW* main){
	

	//User* user, WINODW* main
	string username = user->getUsername();
	string currentUsername = username;
	string lobbyNameString = user->get_room();
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
	if(user->getMod() == true)
		currentUsername = username + "[MOD]";
	else
		currentUsername = username;
	char text[80];
	string textString;

	//window for sending messsages in lobby	
	WINDOW* sendMessageBox = newwin((yMax/17)*2, (xMax/3)*2, ((yMax/17)*15)+1, startx+2);
	WINDOW* messageBox = newwin((yMax/17)*15, (xMax/3)*2, 1, 2);
	WINDOW* currentUserBox = newwin((yMax/17)*14, (xMax/7)*2, 1, ((xMax/3)*2)+3);
	WINDOW* menuBox = newwin((yMax/10)*1.7, (xMax/7)*2, yMax-9, ((xMax/3)*2)+3);
	WINDOW* banUserBox = newwin(yMax/10*1.7, (xMax/7)*2, yMax-9, ((xMax/3)*2)+3);

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
		mvwprintw(currentUserBox, 2, 1, currentUsername.c_str());
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

                controller.add_user_to_chatroom(user, "Lobby");
                //controller.boot_user_to_lobby(user); 
    			main_page(user, main);

			}
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
	}while(modeSwitch != 27);

	getch();
	endwin();
}