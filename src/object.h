#ifndef OBJECT_H
#define OBJECT_H

#include <ncurses.h>
#include "rect.h"

class OBJECT
{
protected:
	char sign; //!< used to draw a shape with
	bool destroyable;
	const int friendliness; //!< friendliness is used to determine if OBJECT is harmful to Player. for example attacker has -1, friend has 1, and asteroid 0
	int lives;
	RECT shape; //!< defines it's shape and coordinates

public:
			OBJECT();
			OBJECT(char sgn, bool des, int frnd, int lvs);
			virtual ~OBJECT();
	virtual int getLives();
	virtual char getSign();
	virtual void move(); //!< moves  shape by default by 1 unit
	virtual int getPoints();
	virtual void attack(); //!< decrements lives.
	virtual void destroy(); //!< sets lives to 0
	virtual bool isTouch(); //!< checks wether shape had passed bottom line.
	virtual int getMiddleX(); //!< returns x coordinates of the middle of the shape.
	virtual int getFriendliness(); //!< returns friendliness
	virtual bool isAttacked(int x); //!< returns true if shape lies on x coordinate
	virtual void setShape(int top,int height,int left, int width); //!< sets shape
	virtual int getLeft(); //!< returns left coordinates of shape
	virtual int getRight(); //!< returns right coordinates of shape
	virtual void moveX(int move_distance); //!< moves shape along X axis
	virtual void moveY(int move_distance); //!< moves shape along Y axis
	virtual bool isAlive();	//!< return true if lives!=0
	virtual bool isDestroyable();
	virtual int getBottom(); //!< returns bottom of shape
	virtual void draw(WINDOW *win); //!< draws shape to *win using sign
};

#endif // OBJECT_H

