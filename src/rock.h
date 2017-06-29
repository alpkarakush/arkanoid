#ifndef ROCK_H
#define ROCK_H
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "object.h"

/** Rock is set up in the begginning of the game and is undestroyable.
*/
class ROCK: public OBJECT
{
public:

			ROCK();
			virtual ~ROCK();
};

#endif // ROCK_H
