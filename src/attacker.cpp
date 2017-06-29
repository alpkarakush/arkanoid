#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "object.h"
#include "attacker.h"

ATTACKER::ATTACKER():
		OBJECT('*', true, -1, 1),
		speed(1),
		points(1)
{
	skins[1]='*';
	skins[2]='#';
	skins[3]='=';

	int left= (rand() % 76 )+1;

	this->setShape( 1, 2, left, 3);
}
ATTACKER::ATTACKER(int live):
		OBJECT('*', true, -1, live),
		speed(1),
		points(1)
{
	skins[1]='*';
	skins[2]='#';
	skins[3]='=';

	int left= (rand() % 76 )+1;
	this->setShape( 1, 2, left, 3);
}
 ATTACKER::~ATTACKER(){}

 void ATTACKER::move()
{
	this->moveY(speed);
}
 int ATTACKER::getPoints()
{
	return points;
}

 void ATTACKER::draw(WINDOW *win)
{
	int i = shape.height;

  while (--i >= 0) {
      mvwhline(
          win,
          shape.top + i,
          shape.left,
          skins[lives],
          shape.width
      );
  }
}
