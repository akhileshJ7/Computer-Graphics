
#include "Triangle.h"
#include "Shape.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "ViewContext.h"


using namespace std;

Triangle::Triangle():Shape(){
	this->x0 = 0.0;
	this->y0 = 0.0;
	this->x1 = 0.0;
	this->y1 = 0.0;
	this->x2 = 0.0;
	this->y2 = 0.0;
	point1[0][0] = 0.0;
	point1[1][0] = 0.0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = 0.0;
	point2[1][0] = 0.0;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;
	
	point3[0][0] = 0.0;
	point3[1][0] = 0.0;
	point3[2][0] = 0.0;
	point3[3][0] = 1.0;
}

Triangle::Triangle(double x0, double y0, double x1, double y1, double x2, double y2, unsigned int color){
	this->x0 =x0;
	this->y0 =y0;
	this->x1 =x1;
	this->y1 =y1;
	this->x2 =x2;
	this->y2 =y2;
	this->color =color;
	
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = x1;
	point2[1][0] = y1;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;

	point3[0][0] = x2;
	point3[1][0] = y2;
	point3[2][0] = 0.0;
	point3[3][0] = 1.0;
	
}

Triangle::~Triangle() {
	
}

Shape& Triangle::operator=(const Shape& shape){
	return *this;
}


Triangle::Triangle(const Triangle& from):Shape(from){
	this->x0 =from.x0;
	this->y0 =from.y0;
	this->x1 =from.x1;
	this->y1 =from.y1;
	this->x2 =from.x2;
	this->y2 =from.y2;
	
	point1[0][0] = x0;
	point1[1][0] = y0;
	point1[2][0] = 0.0;
	point1[3][0] = 1.0;
	
	point2[0][0] = x1;
	point2[1][0] = y1;
	point2[2][0] = 0.0;
	point2[3][0] = 1.0;

	point3[0][0] = x2;
	point3[1][0] = y2;
	point3[2][0] = 0.0;
	point3[3][0] = 1.0;
}


void Triangle::draw(GraphicsContext* gc, const ViewContext& vc){
	gc->setColor(color);

	matrix p1 = vc.mtod * point1;
	matrix p2 = vc.mtod * point2;
	matrix p3 = vc.mtod * point3;

	//cout<<p2;
	//cout<<p3;
	gc->drawLine(p1[0][0],p1[1][0],p2[0][0],p2[1][0]);
	gc->drawLine(p3[0][0],p3[1][0],p2[0][0],p2[1][0]);
	gc->drawLine(p1[0][0],p1[1][0],p3[0][0],p3[1][0]);
	gc->drawLine(p1[0][0],p1[1][0],p1[0][0],p1[1][0]);
	gc->drawLine(p2[0][0],p2[1][0],p2[0][0],p2[1][0]);
	gc->drawLine(p3[0][0],p3[1][0],p3[0][0],p3[1][0]);

	//cout<<p2;
	//cout<<p3;
}

std::ostream& Triangle::out(std::ostream& os){
	os<<"Shape Triangle"<<endl;
	os<<" outerloop "<<endl;
	Shape::out(os);
	os<<" Vertex1 "<<x0<<" "<<y0<<endl;
	os<<" Vertex2 "<<x1<<" "<<y1<<endl;
	os<<" Vertex3 "<<x2<<" "<<y2<<endl;
	os<<" endloop"<<endl;
	return os;
}

void Triangle::in(std::istream& is){
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
	is>>word;
	if(word.compare("Vertex3")==0){
		is>>x2;
		is>>y2;
	}
	
	return ;
}

Shape * Triangle::clone() const{
	return new Triangle(*this);
}


