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
//demo.c #include <ncurses.h> #include <unistd.h> int main(int argc, char *argv[]) { int parent_x, parent_y; int score_size = 3; initscr(); noecho(); curs_set(FALSE); // get our maximum window dimensions getmaxyx(stdscr, parent_y, parent_x); // set up initial windows WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0); WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows mvwprintw(field, 0, 0, "Field"); mvwprintw(score, 0, 0, "Score"); // refresh each window wrefresh(field); wrefresh(score); sleep(5); // clean up delwin(field); delwin(score); endwin(); return 0; }