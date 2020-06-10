#include "Point.h"
#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "ViewContext.h"


using namespace std;

Point::Point():Shape(){
	this->x0 = 0.0;
	this->y0 = 0.0;
	point1[0][0] = 0.0;
	point1[1][0] = 0.0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
}

Point::Point(double x0, double y0, unsigned int color){
	this->x0 =x0;
	this->y0 =y0;
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	this->color = color;
}


Point::Point(const Point& from):Shape(from){
	this->x0 =from.x0;
	this->y0 =from.y0;
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
}

Point::~Point() {
	
}

Shape& Point::operator=(const Shape& shape){
	return *this;
}


void Point::draw(GraphicsContext* gc,const ViewContext& vc){
	//TODO
	gc->setColor(color);
	matrix p1 = vc.mtod * point1;
	gc->drawLine(p1[0][0],p1[1][0],p1[0][0],p1[1][0]);
}

std::ostream& Point::out(std::ostream& os){
	os<<"Shape Point"<<endl;
	os<<" outerloop "<<endl;
	Shape::out(os);
	os<<" Vertex1 "<<x0<<" "<<y0<<endl;
	os<<" endloop"<<endl;
	return os;
}

void Point::in(std::istream& is){
	string word;
	is>>word;
	if(word.compare("Color")==0){
		Shape::in(is);
	}
	is>>word;
	if(word.compare("Vertex1")==0){
		is>>x0;
		is>>y0;
	}
	
	return ;
}

Shape * Point::clone() const{
	
	return new Point(*this);
}

