
#include "x11context.h"
#include <unistd.h>
#include <iostream>
#include "MyDrawing.h"

#include "ViewContext.h"

using namespace std;

int main(void)
{	
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);
	//set default color
	gc->setColor(GraphicsContext::GREEN);
	// make a drawing
	MyDrawing md;
	
	// start event loop - this function will return when X is clicked
	// on window
	gc->runLoop(&md);
	
	delete gc;
	
	return 0;
}
