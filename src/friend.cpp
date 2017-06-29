#include <stdlib.h>
#include <ctime>
#include "object.h"
#include "friend.h"
#include <ncurses.h>

	FRIEND::FRIEND():
			OBJECT('+', true, 1, 1),
			speed(1),
			points(-2)
	{
		int left= (rand() % 76 )+1;
		this->setShape( 1, 2, left, 3);
	}
 FRIEND::~FRIEND(){}
 void FRIEND::move()
{
	this->moveY(speed);
}
 int FRIEND::getPoints()
{
	return points;
}