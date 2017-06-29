#include <stdlib.h>
#include <ctime>
#include "object.h"
#include "asteroid.h"
#include <ncurses.h>
	ASTEROID::ASTEROID():
			OBJECT('V', true, 0, 1),
			speed(1),
			points(0)
	{
		int left= (rand() % 76 )+1;

		this->setShape( 1, 2, left, 3);
	}
	 ASTEROID::~ASTEROID(){}
 void ASTEROID::move()
{
	this->moveY(speed);
}
 int ASTEROID::getPoints()
{
	return points;
}
