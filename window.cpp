#include "window.h"

Window::Window(){
    //start();
}
void Window::start(){
    //cbreak();
    initscr();
    raw();
    noecho();
    int height, width, start_y, start_x;
    height = 75;
    width = 275;
    start_y = start_x = 0;

    WINDOW* main_win = newwin(height,width,start_y,start_x);
    WINDOW* user_name_window = newwin(height/4, width/4, (height/8) +20 , (width/2)-(width/8));
    //WINDOW* welcome = newwin(height/4, width/4, (height/16) + 3, (width/2) -(width/8));
    refresh();
    box(main_win, 0 , 0);
    box(user_name_window, 0, 0);
    //box(welcome, 0, 0);
    move(height/4, width/4);
    mvwprintw(user_name_window, 1, 25, "ENTER USER NAME");
    mvwprintw(main_win, 20, (width/2)- (width/8) + 23, "WELCOME TO SUPER CHAT");
    //mvwprintw(welcome, 1, 1, "WELCOME TO SUPER CHAT");
    refresh();
    wrefresh(main_win);
    wrefresh(user_name_window);
    //wrefresh(welcome);
    getch();
    //delwin(main_win);
    endwin();
}

//demo.c #include <ncurses.h> #include <unistd.h> int main(int argc, char *argv[]) { int parent_x, parent_y; int score_size = 3; initscr(); noecho(); curs_set(FALSE); // get our maximum window dimensions getmaxyx(stdscr, parent_y, parent_x); // set up initial windows WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0); WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows mvwprintw(field, 0, 0, "Field"); mvwprintw(score, 0, 0, "Score"); // refresh each window wrefresh(field); wrefresh(score); sleep(5); // clean up delwin(field); delwin(score); endwin(); return 0; }