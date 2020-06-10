#ifndef MYDRAWING_H
#define MYDRAWING_H
#include "drawbase.h"
#include <unistd.h>
#include <iostream>
#include "Image.h"
#include <string>
#include "ViewContext.h"
// forward reference
using namespace std;
class GraphicsContext;
class MyDrawing : public DrawingBase
{
	public:
		MyDrawing(); 
		// we will override just these 
		virtual void paint(GraphicsContext* gc, const ViewContext& vc);
		virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
		virtual void keyUp(GraphicsContext* gc, unsigned int keycode);
		virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y);
		virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y);
		virtual void mouseMove(GraphicsContext* gc, int x, int y);
		void saveImage();
		void importImage(GraphicsContext* gc);
		void displayMenu(); 
		void displayOptions();
		void setFilename();
	private: 
		// We will only support one "remembered" line 
		// In an actual implementation, we would also have one of our "image" 
		// objects here to store all of our drawn shapes.
		ViewContext vc;
		Image im;
		int x0; 
		int y0;
		int x1; 
		int y1;
		int x2;
		int y2;
		bool line;
		bool point;
		bool triangle;
		bool triBase;
		bool triTop;
		bool esc;
		bool deviceMode;
		bool modelMode;
		string filename;
		unsigned int color;
		bool dragging; // flag to know if we are dragging
};
#endif
