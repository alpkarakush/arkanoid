#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include "name.h"

using namespace std;

#define HEIGHT 30
#define	WIDTH 80
#define	STARTY 0
#define	STARTX 0

static inline bool check_screen()
{
    return LINES >= 30 && COLS >= 80;
}

static inline void init()
{
    // Don't show cursor
    curs_set(0);

    // Read arrow keys
    keypad(stdscr, true);

    // Read chars directly but allow interrupts
    cbreak();

    // Don't echo typed characters
    noecho();

    // Don't wait for characters, error if nothing typed
    nodelay(stdscr, true);
}

static inline void show_best(WINDOW *menu_win)
{
	werase(menu_win);
	box(menu_win, 0 , 0);

	fstream fs;
	fs.open ("./examples/score", fstream::in);

	string saved_name;
	int saved_score;

	fs>>	saved_name >>	saved_score	;


	mvwprintw(menu_win,13,30,"Best score: %s : %d", saved_name.c_str(), saved_score);
	mvwprintw(menu_win,17,30,"Press any key to go back.");
	wrefresh(menu_win);

	nodelay(stdscr, false);
	getch();
	nodelay(stdscr, true);
}

static inline void draw_menu(WINDOW *menu_win)
{
	werase(menu_win);
	box(menu_win, 0 , 0);
		
	mvwprintw(menu_win,13,30,"run (ENTER)");
	mvwprintw(menu_win,15,30,"score (SPACE)");
	mvwprintw(menu_win,17,30,"exit (ESC)");
	wrefresh(menu_win);
}

static inline void menu()
{
	int ch;
	WINDOW *menu_win;

	menu_win = newwin(HEIGHT, WIDTH, STARTY, STARTX);

	draw_menu( menu_win );

	while((ch = getch()) != 27)
	{
		switch(ch)
		{
			case '\n':
				name_menu();
				break;
			case ' ':
				show_best(menu_win);
				break;
		}
		draw_menu( menu_win );
	}

	delwin(menu_win);
}

int main(int argc, char *argv[])
{	
	int err=0;

	initscr();			/* Start curses mode 		*/
	
	if (!check_screen()) {
        std::cout<<"Terminal should be at least 30x80"<<std::endl;
        err = 1;
    } else {
    		//std::cout<<"working"<<std::endl;
        init();
        menu();
    }

	endwin();
	
	return err;
}
