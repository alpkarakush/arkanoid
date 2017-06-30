#ifndef FRIEND_H
#define FRIEND_H
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "object.h"

/** FRIEND class is derived from OBJECT.
		It represents falling friendly ships,
		which should not be attacked, otherwise player gets negative points.
		It can freely pass through bottom.
*/
class FRIEND: public OBJECT
{
protected:
	int speed; //!< defines how fast it moves down
	int points; //!< how much points does it cost
public:
			FRIEND();

			virtual ~FRIEND();
	virtual void move();
	virtual int getPoints();
};
#endif // FRIEND_H
