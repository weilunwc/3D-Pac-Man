

class Button
{
private:
	int x, y;
	int dx1,dx2,dy1,dy2;
  char display[1024];
public:
  Button();
  Button(int,int);
	void Draw();
	void ReadState(int,int);
	void SetText(string);
	int state;

};
Button::Button(){
  x = 0;
  y = 0;
  state = 0;
  string buffer = " ";
  strcpy(display,buffer.c_str());
  dx1 = -20;
  dx2 = 50;
  dy1 = -20;
  dy2 =  10;
}
Button::Button(int x,int y){
  this->x = x;
  this->y = y;
  state = 0;
  string buffer = " ";
  strcpy(display,buffer.c_str());
  dx1 = -20;
  dx2 = 50;
  dy1 = -20;
  dy2 =  10;
}

void Button::ReadState(int mx,int my){
  state = 0;
  if(mx >= (200+x + dx1)  && mx <= (200+x + dx2)  && my >= (y + dy1)  && my <= (y + dy2)){
    state = 1;
  }
}

void Button::SetText(string text){
  strcpy(display,text.c_str());
}

void Button::Draw(void)
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  if(state == 0){
    glColor4f(0.5, 1.0, 0.5, 0.8);
  }
  else{
    glColor4f(0.8, 0.0, 0.8, 0.8);
  }
  glBegin(GL_QUADS);
  glVertex2i(200+x + dx1, y + dy2);
  glVertex2i(200+x + dx1, y + dy1);
  glVertex2i(200+x + dx2, y + dy1);
  glVertex2i(200+x + dx2, y + dy2);
  glEnd();
  glColor3ub(0, 0, 0);
  glRasterPos2i(200+x,y);
  YsGlDrawFontBitmap8x12(display);

}
