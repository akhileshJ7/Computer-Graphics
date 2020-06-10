#ifndef __Line_H_
#define __Line_H_


#include <iostream>
#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "ViewContext.h"

class ViewContext; 

class Line : public Shape{
protected:
	Shape& operator=(const Shape& shape);
public:
	Line();
	Line(const Line& from);
	Line(double x0, double y0, double x1, double y1, unsigned int color);
	virtual ~Line();
	virtual void draw(GraphicsContext* gc, const ViewContext& vc);
	virtual std::ostream& out(std::ostream& os);
	virtual void in(std::istream& is);
	virtual Shape * clone() const;
private:
	double x0;
	double y0;
	double x1;
	double y1;
	matrix point1 = matrix(4,1);
	matrix point2 = matrix(4,1);

};


#endif 
