#ifndef ASTEROID_H
#define ASTEROID_H
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "object.h"

/** Class Asteroid is derived from OBJECT.
		It represents falling asteroids, which have 0 points
		and can freely pass through bottom of the screen.
*/
class ASTEROID: public OBJECT
{
protected:
	int speed; //!< defines how fast it moves down
	int points; //!< how much points does it cost

public:
			ASTEROID();
			virtual ~ASTEROID();
	virtual void move();
	virtual int getPoints();
};

#endif // ASTEROID_H
