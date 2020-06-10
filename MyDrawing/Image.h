#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <iostream>
#include "Shape.h"
#include "ViewContext.h"
#include <vector>

class ViewContext;

class Shape;

class Image {
public:
	//default construct
	Image();
	//copy constructor
	Image(const Image& image);
	//destructor
	~Image();
	//Assigns an image to contain the same shapes as another image
	Image& operator=(const Image& from);
	//Add a new shape (via a pointer) to the container
	void add(Shape* shape);
	/*Ask all shAsk all the shapes to draw themselves by iterating 
	 * through the image's collection of shapes, and invoking each
	 * shape's draw() method via the pointer
	 */ 
	void draw(GraphicsContext* gc, const ViewContext& vc);
	//Output all the shapes to an ostream
	std::ostream& out(std::ostream& os);
	//Read a set of shapes from an istream
	void in(std::istream& is);
	//Remove shapes from image and return any dynamic memory they occupy.
	void erase();

private:
	std::vector<Shape*> shapes;

};

#endif
