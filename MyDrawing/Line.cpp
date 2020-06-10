#include "Line.h"
#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "ViewContext.h"


using namespace std;

Line::Line():Shape(){
	this->x0 = 0.0;
	this->y0 = 0.0;
	this->x1 = 0.0;
	this->y1 = 0.0;
	point1[0][0] = 0.0;
	point1[1][0] = 0.0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = 0.0;
	point2[1][0] = 0.0;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;
}

Line::Line(double x0, double y0, double x1, double y1, unsigned int color){
	this->x0 =x0;
	this->y0 =y0;
	this->x1 =x1;
	this->y1= y1;
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = x1;
	point2[1][0] = y1;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;
	this->color = color;
}


Line::Line(const Line& from):Shape(from){
	this->x0 =from.x0;
	this->y0 =from.y0;
	this->x1 =from.x1;
	this->y1 =from.y1;
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = x1;
	point2[1][0] = y1;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;
}

Line::~Line() {
	
}

Shape& Line::operator=(const Shape& shape){
	return *this;
}


void Line::draw(GraphicsContext* gc, const ViewContext& vc){
	//TODO
	gc->setColor(color);
	matrix p1 = vc.mtod * point1;
	matrix p2 = vc.mtod * point2;
	gc->drawLine(p1[0][0],p1[1][0],p2[0][0],p2[1][0]);
}

std::ostream& Line::out(std::ostream& os){
	os<<"Shape Line"<<endl;
	os<<" outerloop "<<endl;
	Shape::out(os);
	os<<" Vertex1 "<<x0<<" "<<y0<<endl;
	os<<" Vertex2 "<<x1<<" "<<y1<<endl;
	os<<" endloop"<<endl;
	return os;
}

void Line::in(std::istream& is){
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
	is>>word;
	if(word.compare("Vertex2")==0){
		is>>x1;
		is>>y1;
	}
	
	return ;
}

Shape * Line::clone() const{
	
	return new Line(*this);
}

