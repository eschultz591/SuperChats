#include "window.h"

//global main window

int main_height;
int main_width;

void Window::start(){
    User* user = new User();
    //cbreak();
    initscr();
    raw();
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
    main_page(user,main_win);
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
    string choices[4] = {"Join Chat", "Create Chat", "Delete Chat", "Change Username"};


    WINDOW* chatroom_grid = newwin(grid_height, grid_width, 1, 1);
    WINDOW* lobby_grid = newwin(grid_height, grid_width, 1, main_width/2 + 2);
    WINDOW* menu_grid = newwin(grid_height/2, grid_width, grid_height + 1, 1);
    WINDOW* message_box = newwin(grid_height * .2, grid_width - 4, grid_height - grid_height* .2, grid_width + 8);
    WINDOW* output_box = newwin(grid_height/2, grid_width, grid_height + 1, main_width/2 + 2);
    WINDOW* input_box = newwin(grid_height * .2, grid_width - 4, grid_height + grid_height/2 + 1, grid_width + 8);
    refresh();
    box(chatroom_grid, 0, 0);
    box(lobby_grid, 0, 0);
    box(menu_grid, 0, 0);
    box(message_box, 0, 0);
    box(output_box, 0, 0);
    box(input_box, 0, 0);
    wattron(chatroom_grid, A_BLINK); 
    mvwprintw(chatroom_grid, 1, grid_width / 2, "CHATROOMS"); 
    wattroff(chatroom_grid,A_BLINK); 
    mvwprintw(lobby_grid, 1, grid_width/2, "LOBBY");
    mvwprintw(menu_grid, 1, grid_width/2, "MENU");
    mvwprintw(message_box, (grid_height* .2)/2, 1, user_colon.c_str());

    //wmove(menu_grid,1,1);
    //wmove(output_box, 1, 1);
    refresh();

    wrefresh(input_box);
    wrefresh(chatroom_grid);
    wrefresh(lobby_grid);
    wrefresh(menu_grid);
    wrefresh(message_box);
    wrefresh(output_box);
    refresh();
    /*wmove(menu_grid,2, 1);
    refresh();
    wrefresh(menu_grid);
    keypad(menu_grid, true);
    */
    int c;
    int i = 0;
    //prints list the first time
    for(i = 0; i < 4; i++){
        
        if(i == 0){
            wattron(menu_grid,A_REVERSE);
        }
        else
            wattroff(menu_grid,A_REVERSE);
        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
        
    }
    wrefresh(output_box);
    mvwprintw(input_box, 1, (grid_width - 4)/ 2 , "in the inputbox");
    wrefresh(input_box);
    int a = getch();

    if(a == 'a'){
        mvwprintw(output_box, 2, 1, "Enter chatroom name");
        wrefresh(output_box);

        wmove(input_box, 2, 1);
        wrefresh(input_box);
        getch();
    }
    //wgetch(output_box);
    i = 0;
    wrefresh(output_box);
    wrefresh(menu_grid);
    //getch();
    //27 is the escape key
    /*while (c = wgetch(menu_grid) != 27){
        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
        
            switch( c ) {
                case KEY_UP:
                    i--;
                    if(i == -1){
                        i = 4;
                    }
                    break;
                case KEY_DOWN:
                    i++;
                    if(i == 5){
                        i = 0;
                    }
                    break;
                case KEY_RIGHT: 
                    lobby_chat(input_box);
                    break;
            }
            // now highlight the next item in the list.
            wattron( menu_grid, A_REVERSE );
            mvwprintw(menu_grid, i+2, 1, choices[i].c_str());
            wrefresh(menu_grid);
            wattroff( menu_grid, A_REVERSE );
    }*/
}

void Window::lobby_chat(WINDOW* input_box){
    wmove(input_box, 1, 1);
    refresh();
    wrefresh(input_box);
    getch(); 
}