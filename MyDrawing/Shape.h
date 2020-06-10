#ifndef __SHAPE_H_
#define __SHAPE_H_

#include "matrix.h"
#include "gcontext.h"
#include <iostream>
#include <string>
#include "ViewContext.h"

using namespace std;

class ViewContext; 
 
class Shape {
	
protected:
	Shape& operator=(const Shape& shape);
	
	unsigned int color;

public:
	//Initialize properties that reside in Shape.
	Shape();
	//copy constructor
	Shape(const Shape& from);	
	//Destructor
	virtual ~Shape();
	//draw "pure virtua" method
	virtual void draw(GraphicsContext* gc, const ViewContext& vc) = 0;
	//This method will be like the Matrix::out method
	virtual std::ostream& out(std::ostream& os);
	//this will be used to read shape properties from a text file
	virtual void in(std::istream& is);
	//clone
	virtual Shape * clone() const = 0;

};

#endif 
