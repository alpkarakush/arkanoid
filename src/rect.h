#ifndef RECT_H
#define RECT_H

/** Used to save coordinates and shape of objects
*/
struct RECT {
	int top;
  int height;
  
  int left;
  int width;

  int bottom;
  int right;
  
  

    RECT(){}
    RECT(int top,int height,int left, int width):
    		top(top),
    		height(height),
    		left(left),
    		width(width)
    {
    	bottom= top + height ;
    	right= left + width ;
    }
};

#endif // RECT_H
