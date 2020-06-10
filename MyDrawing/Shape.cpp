#include "Shape.h"
#include "matrix.h"
#include "gcontext.h"
#include <string>
#include "Line.h"
#include "Triangle.h"
#include "ViewContext.h"


using namespace std;

Shape::Shape() {
	this->color = 0xFF0000;
}


Shape::~Shape() {
	
}

Shape::Shape(const Shape& from){
	this->color = from.color;
}
Shape& Shape::operator=(const Shape& rhs){
	if(this==&rhs){
		return *this;
	}
	this->color = rhs.color;
	return *this;
}

std::ostream& Shape::out(std::ostream& os){
	os<<" Color "<<color<<std::endl;
	return os;
}

void Shape::in(std::istream& is){
	is>>color;
	return ;
}


	
