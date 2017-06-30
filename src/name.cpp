#include <ncurses.h>
#include <string.h>
#include <fstream>
#include "name.h"
#include "player.h"
#include "play.h"

using namespace std;

/** The name should not contain any spaces
	 * this function checks if string contains any spaces
	 */
bool check_name( char *name )
{
	if(strlen(name) == 0)
		return false;

	int i=0;
	while(name[i]!='\0')
	{
		if(name[i]==' ')
			return false;
		i++;
	}
	return true;
}

void draw_name_menu(GAME &game)
{
	werase(game.win);
	box(game.win, 0 , 0);
	mvwprintw( game.win, 13, 30, "Type yourname:" );
	wrefresh( game.win );
}

void get_name( GAME &game)
{
	char name[20];

	echo();
	draw_name_menu(game);
	wgetstr( game.win , name);

	// checking for spaces in the name

	while(true)
	{
		if( !check_name( name ) )
		{
			draw_name_menu(game);

			mvwprintw( game.win, 15, 30, "Name should not contain spaces or be empty!!!" );
			wmove( game.win, 13, 44 );
			wrefresh( game.win );
			wgetstr( game.win , name );
		}
		else
		{
		 break;
		}
	}

	noecho();

	game.setPlayer(name);
}

void draw_map_menu(GAME &game)
{
	werase(game.win);
	box(game.win, 0 , 0);

	mvwprintw( game.win, 13, 30, "Level 1 (Press 1)" );
	mvwprintw( game.win, 15, 30, "Level 2 (Press 2)" );
	mvwprintw( game.win, 17, 30, "Level 3 (Press 3)" );
	mvwprintw( game.win, 19, 30, "Level 4 (Press 4)" );
	
	wrefresh( game.win );
}

void choose_map(GAME &game)
{
	draw_map_menu(game);

	nodelay(stdscr, false);

	char ch=getch();

		switch(ch)
			{
				case '1':
					game.readMap("./examples/map1");
					break;
				case '2':
					game.readMap("./examples/map2");
					break;
				case '3':
					game.readMap("./examples/map3");
					break;
				case '4':
					game.readMap("./examples/map4");
					break;
			}

	nodelay(stdscr, true);
}

void name_menu()
{

	GAME game;
	game.creatWindow(30,80);

	// getting name of a player
	get_name(game);
	choose_map(game);
	play(game);

	delwin(game.win);
}


