#include <ncurses.h>
#include "rect.h"
#include "object.h"


	OBJECT::OBJECT():
			friendliness(0)
		{}
	OBJECT::OBJECT(char sgn ='-', bool des =true , int frnd =0 , int lvs =1 ):
				sign(sgn),
				destroyable(des),
				friendliness(frnd),
				lives(lvs)
		{}
	
	 OBJECT::~OBJECT(){}
 int OBJECT::getLives()
{
	return lives;
}
 char OBJECT::getSign()
{
	return sign;
}
 void OBJECT::move()
{
	this->moveY(1);
}


 int OBJECT::getPoints()
{
	return 1;
}

 void OBJECT::attack()
{
	if( lives > 0 )
		lives--;
}
 void OBJECT::destroy()
{
	lives=0;
}

 bool OBJECT::isTouch()
{
	return ( shape.bottom >= 28 );
}

 int OBJECT::getMiddleX()
{
return shape.left + (shape.width/2);
}

 int OBJECT::getFriendliness()
{
	return friendliness;
}

 bool OBJECT::isAttacked(int x)
{
	if(shape.left <= x && x <= shape.right)
		return true;
	else
		return false;
}

 void OBJECT::setShape(int top,int height,int left, int width)
{
	shape.top = top;
	shape.height = height;
	shape.left = left;
	shape.width = width;

	shape.bottom= top + height ;
	shape.right= left + width ;
}
 int OBJECT::getLeft()
{
	return shape.left;
}
 int OBJECT::getRight()
{
	return shape.right;
}
 void OBJECT::moveX(int move_distance)
{
	shape.left 	+= move_distance;
	shape.right += move_distance;
}
 void OBJECT::moveY(int move_distance)
{
	shape.top 	+= move_distance;
	shape.bottom += move_distance;
}



 bool OBJECT::isAlive()
{
	return lives != 0 ;
}
 bool OBJECT::isDestroyable()
{
	return destroyable;
}
 int OBJECT::getBottom()
{
	return shape.bottom;
}

 void OBJECT::draw(WINDOW *win)
{
	int i = shape.height;

  while (--i >= 0) {
      mvwhline(
          win,
          shape.top + i,
          shape.left,
          this->sign,
          shape.width
      );
  }
}

