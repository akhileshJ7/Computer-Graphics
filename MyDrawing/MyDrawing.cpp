#include "MyDrawing.h"
#include "gcontext.h"
#include "drawbase.h"
#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include "Triangle.h"
#include "ViewContext.h"
#include <unistd.h>
#include <iostream>
// Constructor
using namespace std;

MyDrawing::MyDrawing()
{	
	line = false;
	esc = false;
	triangle = false;
	dragging = false;
	triBase =false;
	triTop = false;
	point = true;
	deviceMode = false;
	modelMode = true;
	displayMenu();
	cout<<"Color set to Green"<<endl;
	cout<<"Dawring Point"<<endl;
	cout<<"Model Mode On"<<endl;
	filename = "read.txt";
	color = GraphicsContext::GREEN;
	x0 = x1 = x2 = y0 = y1 = y2= 0;
	return;
}
void MyDrawing::paint(GraphicsContext* gc, const ViewContext& vc)
{	
	//draw all shapes in images
	im.draw(gc,vc);
	return;
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) 
{
	// mouse button pushed down
	// - clear context
	// - set origin of new line 
	// - set XOR mode for rubber-banding
	// - draw new line in XOR mode. Note, at this point, the line is
	// degenerate (0 length), but need to do it for consistency
	
	
	//check for triangle -deault line
	if(triangle){	
		//draw top	
		if(triTop){
			triBase = false;
		}else{
			//draw base
			triBase = true;
			x0 = x1 = x;
			y0 = y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0,y0,x1,y1);
		}
		dragging = true;
	}else{
		//draw line/point
		x0 = x1 = x;
		y0 = y1 = y;
		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawLine(x0,y0,x1,y1);
		if(point){
			dragging = false;
		}else if(line){
			dragging = true;
		}
	}
	return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
	
	if(dragging ==true && esc ==false)
	{	
		if(line){ 
			//mouse up for line
			
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
		
		
			// just in x and y here do not match x and y of last mouse move
			x1 = x;
			y1 = y;
			// go back to COPY mode
			gc->setMode(GraphicsContext::MODE_NORMAL);
			
			// new line drawn in copy mode
			gc->drawLine(x0,y0,x1,y1);
			
			// save shape clear flag
			dragging = false;
			//Check View Mode
			if(modelMode){
				Shape* l = new Line(x0,y0,x1,y1,color);
				im.add(l);
			    delete l;
			}else{
				matrix p1 = vc.convertToMatrix(x0,y0);
				matrix p2 = vc.convertToMatrix(x1,y1);
				matrix modelP1 = matrix(4,1);
				modelP1 = vc.dtom * p1;
				matrix modelP2 = matrix(4,1);
				modelP2 = vc.dtom * p2;
				
				Shape* l = new Line(modelP1[0][0],modelP1[1][0],modelP2[0][0],modelP2[1][0],color);
				im.add(l);
			    delete l;
			}
			
		}else if(triangle){
			//mouse up for triangle 
			if(triBase){
				//mouse up for base 
				
				// undraw old line
				gc->drawLine(x0,y0,x1,y1);
		
				// just in x and y here do not match x and y of last mouse move
				x1 = x;
				y1 = y;
				x2 = x;
				y2 = y; 
				
				//clear flag
				triBase = false;
				triTop = true;
			}else if(triTop){
				//mouse up for top 
				 
				// undraw old line
				gc->drawLine(x0,y0,x2,y2);
				gc->drawLine(x1,y1,x2,y2);
				
				// just in x and y here do not match x and y of last mouse move
				x2 = x;
				y2 = y;
			
				// go back to COPY mode
				gc->setMode(GraphicsContext::MODE_NORMAL);
		
				// new line drawn in copy mode
				gc->drawLine(x0,y0,x2,y2);
				gc->drawLine(x1,y1,x2,y2);
				gc->drawLine(x0,y0,x1,y1);
				
				//save shape and clear flag 

				triTop = false;
				dragging = false;
				
				//Check View Mode
				if(modelMode){
					Shape* t = new Triangle(x0,y0,x1,y1,x2,y2,color);
					im.add(t);
					delete t;
				}else{
					matrix p1 = vc.convertToMatrix(x0,y0);
					matrix p2 = vc.convertToMatrix(x1,y1);
					matrix p3 = vc.convertToMatrix(x2,y2);
					matrix modelP1 = matrix(4,1);
					modelP1 = vc.dtom * p1;
					matrix modelP2 = matrix(4,1);
					modelP2 = vc.dtom * p2;
					matrix modelP3 = matrix(4,1);
					modelP3 = vc.dtom * p3;
					
					Shape* t = new Triangle(modelP1[0][0],modelP1[1][0],modelP2[0][0],modelP2[1][0],modelP3[0][0],modelP3[1][0],color);
					im.add(t);
					delete t;	
				}
			}
		}
	}else if(esc== true && dragging == true){
		// esc button handler
		if(line){
			//esc for line 
			
			//undraw line
			gc->drawLine(x0,y0,x1,y1);
		}else if(triangle){
			//esc for triangle 
			if(triBase){
				//undraw line
				gc->drawLine(x0,y0,x1,y1);
			}
		}
		//clear flag and set normal mode
		gc->setMode(GraphicsContext::MODE_NORMAL);
		esc = false;
		dragging = false;
	}else if(esc == true && dragging == false){
		gc->setMode(GraphicsContext::MODE_NORMAL);
		esc = false;
	}
	if(point){
		//draw a point 
		
		// just in x and y here do not match x and y of last mouse move	
		// go back to COPY mode
		gc->setMode(GraphicsContext::MODE_NORMAL);
		
		// new line drawn in copy mode			
		gc->drawLine(x0,y0,x0,y0);
		
		// clear flag
		dragging = false;
		//Check View Mode
		if(modelMode){
			Shape* p = new Line(x0,y0,x0,y0,color);
			im.add(p);
		    delete p;
		}else{				
			matrix p1 = vc.convertToMatrix(x0,y0);
			matrix modelP1 = matrix(4,1);
			modelP1 = vc.dtom * p1;
			
			Shape* p = new Line(modelP1[0][0],modelP1[1][0],modelP1[0][0],modelP1[1][0],color);
			im.add(p);
		    delete p;
		}
	}
	return;
}
void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{	
	if(dragging ==true && esc ==false)
	{	// mouse move handler
		if(line){
			// mouse moved - "undraw" old line, then re-draw in new position
			// will already be in XOR mode if dragging
			// old line undrawn
			gc->drawLine(x0,y0,x1,y1);
		
			// update
			x1 = x;
			y1 = y;
			
			// new line drawn
			gc->drawLine(x0,y0,x1,y1);
		}else if(triangle){
			if(triBase){
				// undraw old line
				gc->drawLine(x0,y0,x1,y1);
		
				// update
				x1 = x;
				y1 = y;
			
				// new line drawn
				gc->drawLine(x0,y0,x1,y1);
			}else if(triTop){
				//undraw old line
				gc->drawLine(x0,y0,x2,y2);
				gc->drawLine(x1,y1,x2,y2);
				
				//update
				x2 = x;
				y2 = y;
				
				//new line drawn
				gc->drawLine(x0,y0,x2,y2);
				gc->drawLine(x1,y1,x2,y2);
			}
		}
	}
	if(esc == true && dragging == true){
		// mouse move while esc handler
		if(line){
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
			dragging = false;
			
		}else if(triangle){
			if(triBase){
				// undraw old line
				gc->drawLine(x0,y0,x1,y1);
				
			}else if(triTop){
				
				// undraw old line
				gc->drawLine(x0,y0,x1,y1);
				gc->drawLine(x1,y1,x2,y2);
				gc->drawLine(x2,y2,x0,y0);
				triTop = false;
				esc = false;
				
			}
			dragging = false;
		}
	}
	return;
}
void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode){
	//esc action while dragging
	if(keycode==65307){
		if(dragging){
			esc = true;
		}else{
			esc = false;
		}
	}
}
void MyDrawing::keyUp(GraphicsContext* gc, unsigned int keycode){
	// Key handler
	if(keycode == 101 || keycode == 69){
		// E action
		gc->clear();
		im.erase();
	}else if(keycode ==108 || keycode == 76){
		// L action
		cout<<"Dawring Line..."<<endl;
		line = true;
		triangle = false;
		point = false;
	}else if(keycode == 116 || keycode == 84){
		// T action
		cout<<"Dawring Triangle..."<<endl;
		triangle = true;
		line = false;
		point = false;
	}else if(keycode == 112 || keycode == 80){
		// P action
		cout<<"Dawring Point..."<<endl;
		point = true;
		triangle = false;
		line = false;
	}else if(keycode == 115 || keycode == 83){
		// S action
		saveImage();
	}else if(keycode == 102 || keycode == 70){
		// F action
		setFilename();
	}else if(keycode == 105 || keycode == 73){
		// I action
		importImage(gc);
	}else if(keycode == 111 || keycode == 79){
		// O action
		displayOptions();
	}else if(keycode == 49){
		// 1 action
		gc->setColor(GraphicsContext::BLUE);
		color = GraphicsContext::BLUE;
	}else if(keycode == 50){
		// 2 action
		gc->setColor(GraphicsContext::GREEN);
		color = GraphicsContext::GREEN;
	}else if(keycode == 51){
		// 3 action
		gc->setColor(GraphicsContext::RED);
		color = GraphicsContext::RED;
	}else if(keycode == 52){
		// 4 action
		gc->setColor(GraphicsContext::CYAN);
		color = GraphicsContext::CYAN;
	}else if(keycode == 53){
		// 5 action
		gc->setColor(GraphicsContext::MAGENTA);
		color = GraphicsContext::MAGENTA;
	}else if(keycode == 54){
		// 6 action
		gc->setColor(GraphicsContext::YELLOW);
		color = GraphicsContext::YELLOW;
	}else if(keycode == 55){
		// 7 action
		gc->setColor(GraphicsContext::GRAY);
		color = GraphicsContext::GRAY;
	}else if(keycode == 56){
		// 8 action
		gc->setColor(GraphicsContext::WHITE);
		color = GraphicsContext::WHITE;
	}else if(keycode == 57){
		// 9 action
		gc->setColor(GraphicsContext::BLACK);
		color = GraphicsContext::BLACK;
	}else if(keycode == 109 || keycode == 77){
		// M action
		cout<<"Model mode"<<endl;
		gc->clear();
		modelMode = true;
		deviceMode = false;
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.mtod= matrix::identity(4);
		im.draw(gc,vc);
	}else if(keycode == 100 || keycode == 68){
		//D action
		cout<<"Device Mode"<<endl;
		cout<<"Use arrows to rotate shapes around origin"<<endl;
		cout<<"Use Z to zoom shapes around origin"<<endl;
		gc->clear();
		deviceMode = true;
		modelMode = false;
		gc->setMode(GraphicsContext::MODE_NORMAL); 
		vc.modelToDevice(gc->getWindowWidth(),gc->getWindowHeight());
		vc.deviceToModel(gc->getWindowWidth(),gc->getWindowHeight());
		im.draw(gc,vc);
	}else if(keycode == 65363){
		//Right arrow action
		gc->clear();
		//Rotate
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.rotate(gc->getWindowWidth(),gc->getWindowHeight(),-90.0);
		im.draw(gc,vc);
	}else if(keycode == 65361){
		//Left arrow action
		gc->clear();
		//Rotate
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.rotate(gc->getWindowWidth(),gc->getWindowHeight(),90.0);
		im.draw(gc,vc);
	}else if(keycode == 65362){
		//Up arrow action
		gc->clear();
		//Rotate
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.rotate(gc->getWindowWidth(),gc->getWindowHeight(),180.0);
		im.draw(gc,vc);
	}else if(keycode == 65364){
		//Down arrow action
		gc->clear();
		//Rotate
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.rotate(gc->getWindowWidth(),gc->getWindowHeight(),-180.0);
		im.draw(gc,vc);
	}else if(keycode == 122 || keycode == 90){
		//Z action
		int x,y;
		cout<<"Enter Zoom X and Y..."<<endl;
		cin>>x;
		cin>>y;
		gc->clear();
		//Scale
		gc->setMode(GraphicsContext::MODE_NORMAL);
		vc.scale(gc->getWindowWidth(),gc->getWindowHeight(),x,y);
		im.draw(gc,vc);
	}
}

void MyDrawing::saveImage(){
	//SAVE image to file
	ofstream fileout(filename);
	im.out(fileout);
}

void MyDrawing::importImage(GraphicsContext* gc){
	//import image from file
	ifstream filein(filename);
	im.in(filein);
	paint(gc, vc);
}

void MyDrawing::displayOptions(){
	//display color options
	cout<<"Color Option:"<<endl;
	cout<<"Press 1 for Blue"<<endl;
	cout<<"Press 2 for Green"<<endl;
	cout<<"Press 3 for Red"<<endl;
	cout<<"Press 4 for Cyan"<<endl;
	cout<<"Press 5 for Magenta"<<endl;
	cout<<"Press 6 for Yellow"<<endl;
	cout<<"Press 7 for Gray"<<endl;
	cout<<"Press 8 for White"<<endl<<endl;
	cout<<"Press 9 for Black"<<endl;
}

void MyDrawing::displayMenu(){
	//display Menu
	cout<<"Drawing Menu"<<endl;
	cout<<"Press P to draw a Point"<<endl;
	cout<<"Press L to draw a Line"<<endl;
	cout<<"Press T to draw a Triangle"<<endl;
	cout<<"Press S to save image on a file"<<endl;
	cout<<"Press I to import image froma file"<<endl;
	cout<<"Press O to display color options"<<endl;
	cout<<"Press E to Erase the image"<<endl;
	cout<<"Press Esc to cancel while drawing"<<endl;
	cout<<"Press F to Enter Filename for Storing/Importing"<<endl;
	cout<<"Press D to Edit Shape in Device Mode "<<endl;
	cout<<"Press M to Switch Display to Model Mode "<<endl<<endl;
}

void MyDrawing::setFilename(){
	//set file name
	cout<<endl<<"Please Enter Filename"<<endl;
	cin>>filename;
}
