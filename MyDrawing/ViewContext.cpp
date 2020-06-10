
#include "ViewContext.h"
#include "matrix.h"
#include <unistd.h>
#include <math.h>       


// Constructor
using namespace std;

ViewContext::ViewContext(){
	 
}

ViewContext::~ViewContext(){
}

void ViewContext::rotate(double deltaX, double deltaY, double angle){
	
	double PI = 3.14159265;

	//Shift to origin
	matrix translate = matrix(4,4);
	translate[0][0] = 1;
	translate[1][1] = 1;
	translate[2][2] = 1;
	translate[3][3] = 1;
	translate[0][3] = -deltaX/2;
	translate[1][3] = -deltaY/2; 
	
	//Rotate
	matrix rotateMat = matrix(4,4);
	rotateMat[0][0] = cos(angle*PI/180.0);
	rotateMat[0][1] = sin(angle*PI/180.0);
	rotateMat[1][0] = -1*sin(angle*PI/180.0);
	rotateMat[1][1] = cos(angle*PI/180.0);
	rotateMat[2][2] = 1;
	rotateMat[3][3] = 1; 
	
	//Rotate Back
	matrix rotateMatRev = matrix(4,4);
	rotateMatRev[0][0] = cos(angle*PI/180.0);
	rotateMatRev[0][1] = -1*sin(angle*PI/180.0);
	rotateMatRev[1][0] = sin(angle*PI/180.0);
	rotateMatRev[1][1] = cos(angle*PI/180.0);
	rotateMatRev[2][2] = 1;
	rotateMatRev[3][3] = 1; 
	
	rotateMatRev = rotateMatRev * translate;
	rotateMat = rotateMat * translate;
	
	//Shift Back
	translate[0][3] = deltaX/2;
	translate[1][3] = deltaY/2;

	dtom = dtom * translate * rotateMatRev;
	mtod =  translate *rotateMat* mtod;
	
}



void ViewContext::scale(double deltaX, double deltaY, double x, double y){
	
	//Shift to origin
	matrix translate = matrix(4,4);
	translate[0][0] = 1;
	translate[1][1] = 1;
	translate[2][2] = 1;
	translate[3][3] = 1;
	translate[0][3] = -deltaX/2;
	translate[1][3] = -deltaY/2; 
	
	//Scale
	matrix scaleMat = matrix(4,4);
	scaleMat[0][0] = x;
	scaleMat[1][1] = y;
	scaleMat[2][2] = 1;
	scaleMat[3][3] = 1; 
	
	//Scale Back
	matrix scaleMatRev = matrix(4,4);
	scaleMatRev[0][0] = 1/x;
	scaleMatRev[1][1] = 1/y;
	scaleMatRev[2][2] = 1;
	scaleMatRev[3][3] = 1; 
	
	//Shift Back
	scaleMatRev = scaleMatRev * translate;
	scaleMat = scaleMat * translate;
	
	translate[0][3] = deltaX/2;
	translate[1][3] = deltaY/2;
	
	dtom = dtom * translate * scaleMatRev;
	mtod = translate * scaleMat * mtod;
	
}


void ViewContext::modelToDevice(double deltaX, double deltaY){
	
	//Inverse Grid
	matrix flip = matrix(4,4);
	flip[0][0] = 1;
	flip[1][1] = -1;
	flip[2][2] = 1;
	flip[3][3] = 1; 
	
	//Shift to center
	matrix translate = matrix(4,4);
	translate[0][0] = 1;
	translate[1][1] = 1;
	translate[2][2] = 1;
	translate[3][3] = 1;
	translate[0][3] = deltaX/2;
	translate[1][3] = deltaY/2; 

	mtod = translate * flip;
}

void ViewContext::deviceToModel(double deltaX, double deltaY){
	
	//Inverse Grid
	matrix flip = matrix(4,4);
	flip[0][0] = 1;
	flip[1][1] = -1;
	flip[2][2] = 1;
	flip[3][3] = 1; 
	
	//Shift center back 
	matrix translate = matrix(4,4);
	translate[0][0] = 1;
	translate[1][1] = 1;
	translate[2][2] = 1;
	translate[3][3] = 1;
	translate[0][3] = -deltaX/2;
	translate[1][3] = -deltaY/2; 

	dtom = flip * translate;
}




matrix ViewContext::convertToMatrix(double x, double y){
	coordinates[0][0] = x;
	coordinates[1][0] = y;
	coordinates[2][0] = 0;
	coordinates[3][0] = 1;
	
	return coordinates;
}
