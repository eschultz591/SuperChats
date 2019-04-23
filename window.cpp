#include "window.h"

//global main window

int main_height;
int main_width;

void Window::start(){
    User* user = new User();
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
    string user_colon = user->getUsername() + ": ";
    string choices[4] = {"1 - Join Chat", "2 - Create Chat", "3 - Delete Chat", "4 - Change Username"};

    WINDOW* chatroom_grid = newwin(grid_height, grid_width, 1, 1);
    WINDOW* lobby_grid = newwin(grid_height, grid_width, 1, main_width/2 + 2);
    WINDOW* menu_grid = newwin(grid_height/2+1, grid_width, grid_height + 1, 1);
    WINDOW* input_box = newwin(grid_height * .2, grid_width - 4, grid_height - grid_height* .2, grid_width + 8);
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
    int menu_mode = 1, chatroom_mode = 0, temp, esc_pressed = 0;

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
    noecho();
    curs_set(false);
    //27 is the escape key 
    //While either chatroom mode or menu mode && esc key is not pressed
    while (chatroom_mode || menu_mode)
    {
        int menu_printed = 0;

        while (chatroom_mode){
            c = wgetch(menu_grid);
            //if tab is pressed
            if(c == 9 ){
                //temp = menu_mode; 
                menu_mode = 1;
                chatroom_mode = 0;
                
            }
            //if escape is pressed             
            if(c == 27 ){
                //turns off menu and chatroom mode, exiting the window
                chatroom_mode = 0;
                menu_mode = 0;
            }
        }
        while (menu_mode){
                if(!menu_printed)
                {
                    mvwprintw(menu_grid, 1, grid_width/2, "MENU");
                    box(menu_grid, 0, 0);
                    for(int i = 0; i < 4; i++){
                            wattroff(menu_grid,A_REVERSE);
                        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
                   
                    }
                    int i = 0;
                    wrefresh(menu_grid);  
                     menu_printed = 1;   

                    
                }
                c = wgetch(menu_grid);
                //if tab is pressed
                if(c == 9){
                    //Turn off menu_mode and cha
                    //temp = menu_mode;
                    menu_mode = 0;
                    chatroom_mode = 1;
                    werase(menu_grid);
                    wrefresh(menu_grid);
                } 
                //if escape is pressed
                if(c == 27 ){
                    //turns off menu and chatroom mode, exiting the window
                    chatroom_mode = 0;
                    menu_mode = 0;
                }
                //1 - Join Chatroom
                //2 - Create Chatroom
                //3 - Delete Chatroom
                //4 - Change Username  
                switch( c ) {
                    //Join Chatroom
                    case 1:
                     //           chatroom_mode = 0;
                    //menu_mode = 0;
                                //Controller.add_user_to_chatroom()
                                break;
                    //Create Chatroom
                    case 2:
                    //chatroom_mode = 0;
                    //menu_mode = 0;     
                                //Controller.create_chatroom()

                                break;
                    //Delete Chatroom
                    case 3:
                    //chatroom_mode = 0;
                    //menu_mode = 0;
                                break;
                    //Change Username
                    case 4:
                    //chatroom_mode = 0;
                   // menu_mode = 0;
                                //string new_Username;
                                //Controller.edit_username(username,)
                                break;                                        
                    default:
                                break;
                                }

                // now highlight the next item in the list.
    /*            wattron( menu_grid, A_REVERSE );
                wrefresh(menu_grid);
                mvwprintw(menu_grid, i+2, 1, choices[i].c_str());
                wattroff( menu_grid, A_REVERSE );
                wrefresh(menu_grid);*/
        }


    //getch();
}
}