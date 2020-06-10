#ifndef __POINT_H_
#define __POINT_H_


#include <iostream>
#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "ViewContext.h"


class ViewContext; 

class Point : public Shape{
protected:
	Shape& operator=(const Shape& shape);
public:
	Point();
	Point(const Point& from);
	Point(double x0, double y0,unsigned int color);
	virtual ~Point();
	virtual void draw(GraphicsContext* gc, const ViewContext& vc);
	virtual std::ostream& out(std::ostream& os);
	virtual void in(std::istream& is);
	virtual Shape * clone() const;
private:
	double x0;
	double y0;
	matrix point1 = matrix(4,1);

};


#endif 
