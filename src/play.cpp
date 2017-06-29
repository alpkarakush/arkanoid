#include <ncurses.h>
#include <time.h>
#include "play.h"
#include "game.h"
#include "player.h"
#include "rect.h"


void play(GAME game)
{
	struct timespec timein;

  timein.tv_sec = 0;
  timein.tv_nsec = 1000000;

  game.setEnvironment();
	game.setShooter();

	while( !game.isLost() )
	{
		nanosleep(&timein, NULL);
    game.ticktack();
		
		game.input();
		game.addCharacter();
		game.moveCharacters();
		game.draw();
		game.checkTouch();
	}
	
	game.showScore();

	game.writeScore();
	game.deleteCharacters();
}
