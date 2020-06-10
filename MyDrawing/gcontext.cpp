/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	
#include "x11context.h"

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	/*//get dx and dy for slope 
	int dx = std::abs(x1-x0);
	int dy = std::abs(y1-y0);
	int xAddr,yAddr;
	//check X Quardrant
	if(x1<x0){
		xAddr = -1;
	}else{
		xAddr = 1;
	}
	// Check Y Quadrant
	if(y1<y0){
		yAddr = -1;
	}else{
		yAddr = 1;
	}
	//Initial case 
	int xi = x0;
	int yi = y0;
	//make sure we actually have a line
	if(dx!=0 || dy !=0){
		// Check if Slope<1 and apply Line algorithm for all Quadrants 
		if(dx>dy){
			//set pixel for initial 
			setPixel(xi,yi);
			int d = 2*dy -dx;
			// loop from starting point to end point 
			for(int i =0; i<dx;i++)
			{	
				//check distance of each pixels from the point on the line
				if(d>=0)
				{
					yi += yAddr;
					d += 2*dy-2*dx;
				}else
				{
					d += 2*dy;
				}
			xi=xi+xAddr;
			setPixel(xi,yi);
			}
		}//ends slope<1
		else
		{
			//set pixel for initial 
			setPixel(xi,yi);
			int d = 2*dx -dy; 
			// loop from starting point to end point 
			for(int i=0;i<dy;i++)
			{
				//check distance of each pixels from the point on the line
				if(d>=0)
				{
					xi += xAddr;
					d += 2*dx-2*dy;
				}
				else
				{
					d += 2*dx;
				}
				yi += yAddr;
				setPixel(xi,yi);
			}
		}// end of else |slope| >= 1
	}//end of if it is a real line (dx!=0 || dy !=0)
	*/
	
	//x11context::draw_line(x0, y0, x1, y1);
	
	return;
}



/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	/*
	// start at 0 degrees
	int xi = 0;
	int yi = radius;
	// implement Circle algortithm 
	int d = 1-radius;
	// loop through 1/8th part of a cicrle
	for(xi=0 ;xi<=yi;xi++){ 
		//plotting equivalent pixels on all quadrants 
		setPixel(x0+xi, y0+yi); 
		setPixel(x0+yi, y0+xi); 
		setPixel(x0+xi, y0-yi); 
		setPixel(x0-yi, y0+xi); 
		setPixel(x0-xi, y0-yi); 
		setPixel(x0-yi, y0-xi); 
		setPixel(x0+yi, y0-xi); 
		setPixel(x0-xi, y0+yi); 
		
		// check if d is inside the cirlce or outside the cirlce
		if(d<0){
			d += 2*xi +3;
		}else{
			yi -= 1;
			d += (2*xi)-(2*yi)+5;
		}
	} 
	*/
	
	return;	
}


void GraphicsContext::endLoop()
{
	run = false;
}

