#include <ncurses.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "game.h"
#include "player.h"
#include "map.h"
#include "clock.h"
#include "object.h"
#include "friend.h"
#include "attacker.h"
#include "rock.h"
#include "asteroid.h"


using namespace std;

#define MOVE_SHOOTER 2

void GAME::setEnvironment()
	{
		clock.s 	=0;
		clock.ms 	=0;

		index_ch	=0;
		size_ch		=8;

		attacker_num	=0;
		friend_num		=0;
		asteroid_num	=0;
		rock_num			=0;

		characters = (OBJECT **) malloc( sizeof(OBJECT *) * size_ch );

		this-> setRocks();

		nodelay(win, true);
		werase(this->win);
	}
void GAME::setRocks()
	{
		int i;

		srand(time(NULL));

		for( i=0; i<map.rock_num; ++i )
			{
				characters[index_ch] = new ROCK();
				index_ch++;
				rock_num++;
			}
	}

void GAME::moveShooterLeft()
	{
		shooter.moveX(-MOVE_SHOOTER);
	}
void GAME::moveShooterRight()
	{
		shooter.moveX(MOVE_SHOOTER);
	}

void GAME::decNumberOfObjects( int friendliness)
	{
		switch( friendliness )
			{
				case -1:
					attacker_num--;
					break;
				case 0:
					asteroid_num--;
					break;
				case 1:
					friend_num--;
					break;
			}
	}
void GAME::incNumberOfObjects( int friendliness)
	{
		switch( friendliness )
			{
				case -1:
					attacker_num++;
					break;
				case 0:
					asteroid_num++;
					break;
				case 1:
					friend_num++;
					break;
			}
	}
int GAME::getDestroyed()
	{
		int i;
		int minBottom=0;
		int minIndex=-1;
		int middle=shooter.getMiddleX();

		for( i=0; i<index_ch; ++i )
		{
			if( characters[i]->isAlive() 
					&& characters[i]->isAttacked( middle )
					&& ((characters[i]->getBottom()) > minBottom) )
				{
					minBottom=  characters[i]->getBottom();
					minIndex=i;
				}
		}

		return minIndex;
	}
void GAME::shoot()
	{
		int i;
		int dest= getDestroyed();
		int height;
		int middle= shooter.getMiddleX();

		if(dest == -1)
			height=1;
		else
			height= characters[dest]->getBottom();

		if( dest != -1 && characters[dest]->isDestroyable() )
			{
				player.score += characters[dest]-> getPoints();
				characters[dest]->attack();

				decNumberOfObjects( characters[dest]->getFriendliness() );
			}

		struct timespec timein;

  	timein.tv_sec = 0;
  	timein.tv_nsec = 50000000;

		for( i=27; i>=height; i-- )
			{
				mvwhline(win,i, middle , '+', 1);
				nanosleep(&timein, NULL);
				wrefresh(win);
			}
	}

		GAME::GAME():lost(false){}

void GAME::creatWindow(int height, int width)
	{
		this->height 	= height;
		this->width		=	width;
		this->win  		=	newwin(height, width, 0, 0);
		box(this->win, 0 , 0);	
	}

void GAME::setPlayer(char  *name)
	{
		player.score = 0;
		std::string tmp_name( name );
		player.name = tmp_name;
	}

void GAME::setShooter()
	{
		shooter.setShape(28,1,39,3);
	}

bool GAME::isLost()
	{
		return lost;
	}

void GAME::input()
	{
	    int ch = getch();

	    if (-1 == ch) {
        return;
    	}

	    switch (ch) {
	    case 27:
	        // Escape
	        lost = true;
	        break;

	    case KEY_LEFT:
	    		if(shooter.getLeft() >= 2)
	        	moveShooterLeft();
	        break;

	    case KEY_RIGHT:
	    		if(shooter.getRight() <= 77)
	        	moveShooterRight();
	        break;
	    case KEY_UP:
	    		shoot();
	    		break;
	    }
	}

void GAME::draw()
	{
		werase(this->win);

		shooter.draw(win);

		int i;

		for( i=0; i<index_ch; ++i )
			if(characters[i]->isAlive())
				characters[i]->draw(win);

		box(this->win, 0 , 0);
		printScore();
		wrefresh(this->win);
	}

void GAME::ticktack()
	{
    clock.ms += 1;

    if (1000 == clock.ms) {
            clock.s++;
            clock.ms = 0;
        }
	}

void GAME::moveCharacters()
	{
		int i;

		if( clock.ms % 250 == 0 )
		{
			for( i=0; i<index_ch; ++i )
				if(characters[i]->isAlive() && characters[i]->isDestroyable())
					characters[i]->move();
		}
	}

void GAME::checkTouch()
	{
		int i;

		for( i=0; i<index_ch; ++i )
			{

				if( characters[i]->isAlive() && characters[i]->isTouch() )
					{
						decNumberOfObjects( characters[i]->getFriendliness() );

						if( characters[i]->getFriendliness() == -1 )
						{
							lost = true;
							return;
						}	

						characters[i]->destroy();
					}
			}
	}

void GAME::writeScore()
	{
		string saved_name;
		int saved_score;

		fstream fs;
		fs.open ("./examples/score", fstream::in);


		fs>>	saved_name >> saved_score;
		fs.close();

		if(saved_score < player.score)
		{
			fs.open ("./examples/score", fstream::out | fstream::trunc );
			fs<<player.name << " " << player.score;
			fs.close();
		}
	}

void GAME::incCharacterSize()
	{
		if( index_ch >= size_ch )
			{
				size_ch *= 2;
				characters = (OBJECT **) realloc( characters, sizeof(OBJECT *) * size_ch );
			}
	}

void GAME::addObject( OBJECT *newObj )
	{
		incCharacterSize();

		characters[index_ch] = newObj;

		incNumberOfObjects( characters[index_ch]->getFriendliness() );

		index_ch++;
	}


void GAME::addCharacter()
	{
		srand(time(NULL));

		if( clock.s % 3 == 0 && clock.ms == 0 && attacker_num <= map.attacker_num)
		{	
			addObject( new ATTACKER(  (int)( (rand() % map.attacker_lives )+1) ) );
		}

		if( clock.s % 4 == 0 && clock.ms == 0 && friend_num <= map.friend_num)
		{
			addObject( new FRIEND() );
		}

		if( clock.s % 7 == 0 && clock.ms == 0 && asteroid_num <= map.asteroid_num)
		{
			addObject( new ASTEROID() );
		}
	}

void GAME::deleteCharacters()
	{
		int i;
		for( i=0; i<index_ch; ++i )
			delete characters[i];
		delete characters;
	}

void GAME::printScore()
	{
		mvwprintw( this->win, 1, 2, "score:%d" , this->player.score );
	}

void GAME::readMap(string path)
{
	fstream fs;
	fs.open ( path.c_str() , fstream::in);

	fs>> map.speed>> map.attacker_num>> map.asteroid_num>> map.friend_num>> map.rock_num>> map.attacker_lives;
}

void GAME::showScore()
{
	werase(win);
	box(win, 0 , 0);
	mvwprintw( win, 13, 30, "Your score is: %d", player.score );
	mvwprintw( win, 15, 30, "(Press any key to leave.)");
	wrefresh( win );

	nodelay(stdscr, false);

	getch();

	nodelay(stdscr, true);
}