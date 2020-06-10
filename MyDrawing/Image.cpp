#include "Image.h"
#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include "Triangle.h"
#include "ViewContext.h"
#include <vector>

Image::Image() {
}

Image::Image(const Image& from){
	for(int i=0;i<from.shapes.size();i++){
		this->shapes.push_back(from.shapes[i]->clone());
	}
}

Image::~Image() {
	for(int i=0;i<this->shapes.size();i++){
		delete this->shapes[i];
	}
	shapes.clear();
}



Image& Image::operator=(const Image& rhs){
	if(this==&rhs){
		return *this;
	} 
	
	for(int i=0;i<this->shapes.size();i++){
		delete this->shapes[i];
	}
	this->shapes.clear();
	for(int i=0;i<rhs.shapes.size();i++){
		this->shapes.push_back(rhs.shapes[i]->clone());
	}
	
	return *this;
	 
}

void Image::add(Shape* shape){
	this->shapes.push_back(shape->clone());

}

std::ostream& Image::out(std::ostream& os){
	for(int i=0;i<this->shapes.size();i++){
		shapes[i]->out(os);
	}
	return os;
}

void Image::in(std::istream& is){
	while(!is.eof()){
		string word;
		is>>word;
		if(word.compare("Line")==0){
			is>>word;
			Shape* l1 = new Line();
			l1->in(is);
			this->shapes.push_back(l1->clone());
			delete l1;			
		}
		if(word.compare("Triangle")==0){
			is>>word;
			Shape* t1 = new Triangle();
			t1->in(is);
			this->shapes.push_back(t1->clone());
			delete t1;
		}
	}
	return ;
}

void Image::draw(GraphicsContext* gc, const ViewContext& vc){
	for(int i=0;i<this->shapes.size();i++){
		this->shapes[i]->draw(gc,vc);
	}
}

void Image::erase(){
	for(int i=0;i<this->shapes.size();i++){
		delete this->shapes[i];
	}
	this->shapes.clear();
}

