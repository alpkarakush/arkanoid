#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <string>
#include <fstream>
#include "player.h"
#include "clock.h"
#include "map.h"
#include "object.h"
#include "friend.h"
#include "attacker.h"
#include "rock.h"
#include "asteroid.h"

using namespace std;

#define MOVE_SHOOTER 2

class GAME
{
private:
	MAP map;
	PLAYER player;
	FRIEND shooter;
	CLOCK  clock;

	bool lost;

	int width;
	int height;

	int attacker_num;
	int asteroid_num;
	int rock_num;
	int friend_num;

	OBJECT **characters; ///< all object-like figures will be saved in this array of pointers
	int index_ch; ///< number of characters created
	int size_ch;	///< size of the characters

	void moveShooterLeft();
	void moveShooterRight();
	int getDestroyed(); //!< gets a character that was attacked by player by looking at all of them and checking wether they were attacked and chooses closest.
	void shoot(); //!< finds attacked character and decrements it's life, if it is an attacker, otherwise kills it.
	void decNumberOfObjects(  int friendliness); //!< decrements present number of specific type of characters, that are alive.
	void incNumberOfObjects(  int friendliness); //!< inrements present number of specific type of characters, that are alive.
	void incCharacterSize();	//!< increases array of pointers "characters" if index_ch is equal to size_ch.
	void setRocks();	//!< places randomly ROCKs to screen. Called in the begginning of play.

public:
	WINDOW *win; //!< used to create screen with ncurses library

			GAME();
	void addObject( OBJECT *newObj );
	void readMap(string path);
	void setEnvironment(); //!< prepares member variables and sets rocks to the screen.
	void creatWindow(int height, int width);
	void setPlayer(char  *name); //!< saves name of the Player to player variable.
	void setShooter(); //!< gives Player a ship.
	bool isLost(); //!< returns true of attacker reached bottom line.
	void input(); //!< reads keyboard for input.
	void draw(); //!< draws Player's ship and all characters, including rocks.
	void ticktack();	//!< increments clock.
	void moveCharacters(); //!< moves all charackters by their speed.
	void checkTouch(); //!< checks if any attacker passed through bottom line.
	void writeScore(); //!< saves current score to "score" file in /examples
	void addCharacter(); //!< adds attackers,friends,asteroids according to map
	void deleteCharacters(); //!< deletes all characters from memory
	void printScore(); //!< prints current score on screen
	void showScore(); //!< prints score of the player after game is finished.
};

#endif // GAME_H
