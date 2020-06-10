#ifndef DRAWBASE_H
#define DRAWBASE_H

#include "ViewContext.h"

// forward reference
class GraphicsContext;

class ViewContext;

class DrawingBase
{
	public:
		// prevent warnings
		virtual ~DrawingBase(){}
		virtual void paint(GraphicsContext* gc, const ViewContext& vc){}
		virtual void keyDown(GraphicsContext* gc, unsigned int keycode){}
		virtual void keyUp(GraphicsContext* gc, unsigned int keycode){}
		virtual void mouseButtonDown(GraphicsContext* gc, 
								unsigned int button, int x, int y){}
		virtual void mouseButtonUp(GraphicsContext* gc,
								unsigned int button, int x, int y){}
		virtual void mouseMove(GraphicsContext* gc, int x, int y){}
		
};
#endif
