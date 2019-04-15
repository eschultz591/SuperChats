#include "window.h"

//global main window

int main_height;
int main_width;

void Window::start(){
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

    int grid_height = main_height/2;
    int grid_width = main_width/2 - 4;
    string user_colon = username + ": ";
    string choices[4] = {"Join Chat", "Create Chat", "Delete Chat", "Change Username"};


    WINDOW* chatroom_grid = newwin(grid_height, grid_width, 1, 1);
    WINDOW* lobby_grid = newwin(grid_height, grid_width, 1, main_width/2 + 2);
    WINDOW* menu_grid = newwin(grid_height/2, grid_width, grid_height + 1, 1);
    WINDOW* input_box = newwin(grid_height * .2, grid_width - 4, grid_height - grid_height* .2, grid_width + 8);
    refresh();
    box(chatroom_grid, 0, 0);
    box(lobby_grid, 0, 0);
    box(menu_grid, 0, 0);
    box(input_box, 0, 0);
    wattron(chatroom_grid, A_BLINK); 
    mvwprintw(chatroom_grid, 1, grid_width / 2, "CHATROOMS"); 
    wattroff(chatroom_grid,A_BLINK); 
    mvwprintw(lobby_grid, 1, grid_width/2, "LOBBY");
    mvwprintw(menu_grid, 1, grid_width/2, "MENU");
    mvwprintw(input_box, (grid_height* .2)/2, 1, user_colon.c_str());

    wmove(menu_grid,1,1);
    refresh();

    
    wrefresh(chatroom_grid);
    wrefresh(lobby_grid);
    wrefresh(menu_grid);
    wrefresh(input_box);
    refresh();
    wmove(menu_grid,2, 1);
    refresh();
    wrefresh(menu_grid);
    keypad(menu_grid, true);
    int c;
    int highlight = 0;
    int selection;

    for(int i = 0; i < 4; i++){
        
        if(i == 0){
            wattron(menu_grid,A_REVERSE);
        }
        else
            wattroff(menu_grid,A_REVERSE);
        mvwprintw(menu_grid, i + 2, 1, choices[i].c_str());
        
    }
    wrefresh(menu_grid);

    getch();
}


//demo.c #include <ncurses.h> #include <unistd.h> int main(int argc, char *argv[]) { int parent_x, parent_y; int score_size = 3; initscr(); noecho(); curs_set(FALSE); // get our maximum window dimensions getmaxyx(stdscr, parent_y, parent_x); // set up initial windows WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0); WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows mvwprintw(field, 0, 0, "Field"); mvwprintw(score, 0, 0, "Score"); // refresh each window wrefresh(field); wrefresh(score); sleep(5); // clean up delwin(field); delwin(score); endwin(); return 0; }

 /*switch (c)
        {
            case KEY_DOWN:
                highlight++;
                if(highlight > 4){
                    highlight = 4;
                }
                break;
            case KEY_UP: 
                highlight--;
                if(highlight < 0){
                    highlight = 0;
                }
                break;
            case 27:
                wclear(menu_grid);
                wclear(lobby_grid);
                wclear(chatroom_grid);
                wclear(main);
                wrefresh(menu_grid);
                wrefresh(lobby_grid);
                wrefresh(chatroom_grid);
                wrefresh(main);
                box(main, 0, 0);
                wrefresh(main);
                mvwprintw(main, main_height/2, main_width/2 - 13, "Thanks for using Superchat");
                wrefresh(main);
                getch();
                break;
            default:
                break;
        }*/