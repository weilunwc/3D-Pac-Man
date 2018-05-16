/*
 * Button.h - build an button object which has text on it and 
 * 						pressing on it returns true
 */ 

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using namespace std;

class Button{
public:
	Button();
	Button(int,int);
	void Draw();
	bool ReadState();
	void SetText(string);


private:
	/* block position and bounding box parameters*/
	int x, y;
	int dx1,dx2,dy1,dy2;

	bool state; // if mouse if on top of button 
	/* text */
	char display[1024];
};

Button::Button(){

	state = 0;
	string buffer = " ";
	strcpy(display, buffer.c_str());

	x = 0;
	y = 0;
	dx1 = -20;
	dx2 =  50;
	dy1 = -20;
	dy2 =  10;
}

Button::Button(int x,int y){

	state = 0;
	string buffer = " ";
	strcpy(display, buffer.c_str());

	this->x = x;
	this->y = y;
	dx1 = -20;
	dx2 =  50;
	dy1 = -20;
	dy2 =  10;
}

/* ReadState - checks mouse interaction with button */
bool Button::ReadState(){
	FsPollDevice();
	int lb, mb, rb, mx, my;
	FsGetMouseEvent(lb, mb, rb, mx, my);

	/* Check if mouse is above the button to determine color */
	if(mx >= (200 + x + dx1)  && mx <= (200 + x + dx2)  
			&& my >= (y + dy1)  && my <= (y + dy2)){
		state = 1;
	}
	else{
		state = 0;
	}

	/* Clicked on button */
	if(state && (lb || rb)){
		return true;
	}
	return false;
}

/* Assign a text on top of the button */
void Button::SetText(string text){
	strcpy(display,text.c_str());
}

/* draw - generate the gui display */
void Button::Draw(void){
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	if(state == 0){
		glColor4f(0.5, 1.0, 0.5, 0.8);
	}
	else{
		glColor4f(0.8, 0.0, 0.8, 0.8);
	}
	glBegin(GL_QUADS);
	glVertex2i(200 + x + dx1, y + dy2);
	glVertex2i(200 + x + dx1, y + dy1);
	glVertex2i(200 + x + dx2, y + dy1);
	glVertex2i(200 + x + dx2, y + dy2);
	glEnd();
	// text 
	glColor3ub(0, 0, 0);
	glRasterPos2i(200 + x, y);
	YsGlDrawFontBitmap8x12(display);

}

#endif
