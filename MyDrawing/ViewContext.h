#ifndef _VIEWCONTEXT_H
#define _VIEWCONTEXT_H


#include "drawbase.h"
#include <unistd.h>
#include <iostream>
#include "Image.h"
#include <string>
#include "matrix.h"
// forward reference
using namespace std;

class ViewContext {
	public:
	
		ViewContext(); 
		~ViewContext();
		// we will override just these 
		void modelToDevice(double deltaX, double deltaY);
		void deviceToModel(double deltaX, double deltaY);
		matrix convertToMatrix(double x, double y);
		void rotate(double deltaX, double deltaY, double angle);
		void scale(double deltaX, double deltaY, double x, double y);
		matrix coordinates = matrix(4,1);
		matrix mtod = matrix(4,4);
		matrix dtom = matrix(4,4);
		double angle;

};
#endif
