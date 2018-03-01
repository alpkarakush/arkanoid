#ifndef ATTACKER_H
#define ATTACKER_H


#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "object.h"

/** ATTACKER is a class derived from OBJECT.
		It represents a falling attacker, which has several lifes
		according to level. ATTACKER changes it sking according to it's life number *#=.
*/

class ATTACKER: public OBJECT
{
protected:
	int speed; //!< defines how fast it moves down
	int points; //!< how much points does it cost
	char skins[5]; //!< saves different skins according to lives member.
public:

			ATTACKER();
			ATTACKER(int live);
			virtual ~ATTACKER();
	virtual void move();
	virtual int getPoints();
	virtual void draw(WINDOW *win);
};

#endif // ATTACKER_H