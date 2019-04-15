#include <ncurses.h>

int main(){
    initscr();
    mvprintw(6,10, "hello world");
    refresh();
    getch();
    endwin();
}