#include <stdlib.h>
#include <ctime>
#include "object.h"
#include "rock.h"
#include <ncurses.h>
ROCK::ROCK():
		OBJECT(97, false, 0, 1)
{
	
	int left= (rand() % 76 )+1;

	int top= 	(rand() % 20 )+1;

	this->setShape( top, 2, left, 4);
}
ROCK::~ROCK(){}
