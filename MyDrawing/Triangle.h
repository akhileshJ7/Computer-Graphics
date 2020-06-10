#ifndef __TRIANGLE_H_
#define __TRIANGLE_H_

#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "ViewContext.h"

class ViewContext; 

class Triangle : public Shape {
protected:
	Shape& operator=(const Shape& shape);
public:
	Triangle();
	Triangle(const Triangle& from);
	Triangle(double x0, double y0, double x1, double y1, double x2, double y2, unsigned int color);
	virtual ~Triangle();
	virtual void draw(GraphicsContext* gc, const ViewContext& vc);
	virtual std::ostream& out(std::ostream& os);
	virtual void in(std::istream& is);
	virtual Shape * clone() const;
private:
	double x0;
	double y0; 
	double x1; 
	double y1;
	double x2;
	double y2;
	matrix point1 = matrix(4,1);
	matrix point2 = matrix(4,1);
	matrix point3 = matrix(4,1);
};

#endif 
