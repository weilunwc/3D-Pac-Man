/*
 xiaorui update:
 */

#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "yspngenc.h"

const int hei = 600;
const int wid = 800;

class Menu {
public:
	int highlight_x, highlight_y;
	int yMin,yMax;
    YsRawPngDecoder bgImg;
	Menu();
	int ReadInput(int);
	void DrawMenu(int);
	void HighlightDraw();
    void DrawPacMan(int xdir, int ydir, double x, double y)const;
    void DrawGhost(int xdir, int ydir, int color, int gx, int gy, bool eatable)const;
    void FillBackground(void) const;

};

Menu::Menu(void) {
	highlight_x = 200+315;
	highlight_y = 360;
	yMin = 360;
	yMax = 460;
    bgImg.Decode("menu.png");
    bgImg.Flip();
}

int Menu::ReadInput(int input){
  int state = 0;
  switch(input){
    case FSKEY_UP:
      highlight_y -= 50;
      if(highlight_y < yMin){
        highlight_y = yMax;
      }
      break;
    case FSKEY_DOWN:
      highlight_y += 50;
      if(highlight_y > yMax){
        highlight_y = yMin;
      }
      break;
    case FSKEY_ENTER:
      switch(highlight_y){
        case 360:
              printf("\tStart  \n");
          return 1;
        case 410:
          printf("\tInstruction  \n");
          return 2;
        case 460:
              printf("\tExit  \n");
          return 3;
      }
      break;
  }
  return state;
}

void Menu::DrawGhost(int xdir, int ydir, int color, int gx, int gy, bool eatable) const {
    // I'm not entirely sure how color is going to be represented, but
    // I'm going to be using a color flag for now
    int x, y, c, x1, y1, x2, y2, i, j;
    char curChar;
    int hei = 14; // hei and wid are hard coded
    int wid = 14;
    int pixSize = 4; // can be changed to scale the bitmap
    if (!eatable) {
        char pattern[] =
        {
            ".....1111....."
            "...11111111..."
            "..1111111111.."
            ".111111111111."
            ".111111111111."
            ".111111111111."
            "11111111111111"
            "11111111111111"
            "11111111111111"
            "11111111111111"
            "11111111111111"
            "11111111111111"
            "11.111..111.11"
            "1...11..11...1"
        };
        // First, we draw the main ghost body
        for (y = 0; y < hei; y++) {
            for (x = 0; x < wid; x++) {
                i = x;
                j = y;
                curChar = pattern[i + j*hei];
                if (color == 1 && curChar == '1') { // red
                    glColor3f(1.0, 0.0, 0.0);
                }
                else if (color == 2 && curChar == '1') { // cyan
                    glColor3f(0.0, 1.0, 1.0);
                }
                else if (color == 3 && curChar == '1') { // pink
                    glColor3ub(255, 192, 203);
                }
                else if (color == 4 && curChar == '1') { //
                    glColor3ub(255, 165, 0);
                }
                else { // background color
                    glColor4f(0.0, 0.0, 0.0,0);
                }
                x1 = gx + x * pixSize;
                y1 = gy + y * pixSize;
                x2 = x1 + pixSize;
                y2 = y1 + pixSize;
                glBegin(GL_TRIANGLE_FAN);
                glVertex2i(x1, y1);
                glVertex2i(x2, y1);
                glVertex2i(x2, y2);
                glVertex2i(x1, y2);
                glEnd();
            }
        }
        // after drawing the body, we draw the eyes, which chance with direction
        char eyesL[] =
        {
            ".............."
            ".............."
            ".............."
            "..22....22...."
            ".2222..2222..."
            ".3322..3322..."
            ".3322..3322..."
            "..22....22...."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
        };
        char eyesR[] =
        {
            ".............."
            ".............."
            ".............."
            "....22....22.."
            "...2222..2222."
            "...2233..2233."
            "...2233..2233."
            "....22....22.."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
        };
        char eyesU[] =
        {
            ".............."
            "...33....33..."
            "..2332..2332.."
            "..2222..2222.."
            "..2222..2222.."
            "...22....22..."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
        };
        char eyesD[] =
        {
            ".............."
            ".............."
            ".............."
            ".............."
            "...22....22..."
            "..2222..2222.."
            "..2222..2222.."
            "..2332..2332.."
            "...33....33..."
            ".............."
            ".............."
            ".............."
            ".............."
            ".............."
        };
        char *pat;
        pat = eyesR; // make right default
        if (xdir == 1) pat = eyesR; // right
        else if (xdir == -1) pat = eyesL; // left
        if (ydir == 1) pat = eyesU; // up
        else if (ydir == -1) pat = eyesD; // down
        // draw the eyes
        for (y = 0; y < hei; y++) {
            for (x = 0; x < wid; x++) {
                i = x;
                j = y;
                curChar = pat[i + j*hei];
                if (curChar == '2') { // white
                    glColor3f(1.0, 1.0, 1.0);
                    
                }
                else if (curChar == '3') { // blue
                    glColor3f(0.0, 0.0, 1.0);
                }
                if (curChar != '.') {
                    x1 = gx + x * pixSize;
                    y1 = gy + y * pixSize;
                    x2 = x1 + pixSize;
                    y2 = y1 + pixSize;
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2i(x1, y1);
                    glVertex2i(x2, y1);
                    glVertex2i(x2, y2);
                    glVertex2i(x1, y2);
                    glEnd();
                }
            }
        }
    }
    else {// draw eatable ghost (:
        char pattern[] =
        {
            ".....1111....."
            "...11111111..."
            "..1111111111.."
            ".111111111111."
            ".111111111111."
            ".111221122111."
            "11112211221111"
            "11111111111111"
            "11221122112211"
            "12112211221121"
            "11111111111111"
            "11111111111111"
            "11.111..111.11"
            "1...11..11...1"
        };
        for (y = 0; y < hei; y++) {
            for (x = 0; x < wid; x++) {
                i = x;
                j = y;
                curChar = pattern[i + j*hei];
                if (curChar == '1') { // blue
                    glColor3f(0.0, 0.0, 1.0);
                    
                }
                else if (curChar == '2') { // white
                    glColor3f(1.0, 1.0, 1.0);
                }
                else glColor4f(0.0, 0.0, 0.0,0);
                x1 = gx + x * pixSize;
                y1 = gy + y * pixSize;
                x2 = x1 + pixSize;
                y2 = y1 + pixSize;
                glBegin(GL_TRIANGLE_FAN);
                glVertex2i(x1, y1);
                glVertex2i(x2, y1);
                glVertex2i(x2, y2);
                glVertex2i(x1, y2);
                glEnd();
            }
        }
    }
}

void Menu::FillBackground(void)const{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,hei);
    glVertex2i(0,hei);
    glEnd();
    
//    glBegin(GL_QUADS);
//    glVertex2i(,(hei - bgImg.hei)-20);
//    glVertex2i(wid,(hei - bgImg.hei)-20);
//    glVertex2i(wid,hei);
//    glVertex2i(0,hei);
//    glEnd();
}

void Menu::DrawPacMan(int xdir, int ydir, double x, double y) const {
    int dx, dy,  i ,j;
    double x1, y1, x2, y2;
    char curChar;
    int hei = 15; // hei and wid are har coded
    int wid = 15;
    int pixSize = 4; // can be changed to scale the bitmap
    char pattern[] =
    {
        ".....44444....."
        "...444444444..."
        "..44444444444.."
        "..44004444444.."
        ".4440044444444."
        ".4444444444...."
        ".4444444......."
        ".444444........"
        ".44444444......"
        ".4444444444...."
        "..444444444444."
        "..44444444444.."
        "...444444444..."
        ".....44444....."
    };
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (dy = 0; dy < hei; dy++) {
        for (dx = 0; dx < wid; dx++) {
            i = dx;
            j = dy;
            // check direction. right is default
            if (xdir == -1) { // moving to the left
                i = (wid - 1) - dx;
            }
            else if (ydir == 1) { // moving up
                i = (hei - 1) - dy;
                j = (wid - 1) - dx;
            }
            else if (ydir == -1) { // moving down
                i = dy;
                j = (hei - 1) - dx;
            }
            
            curChar = pattern[i + j*hei];
            if (curChar == '4') {
                glColor3f(1.0, 1.0, 0.0); // yellow
                
            }
            else if(curChar == '0') { // eye color - black
                glColor3f(0.0, 0.0, 0.0);
            }else{
                glColor4ub(255, 102, 255, 0 );
                //glColor3f( 1.0, 1.0, 1.0 );// background
            }
            x1 = x + dx * pixSize;
            y1 = y + dy * pixSize;
            x2 = x1 + pixSize;
            y2 = y1 + pixSize;
            glBegin(GL_QUADS);
            glVertex2d(x1, y1);
            glVertex2d(x2, y1);
            glVertex2d(x2, y2);
            glVertex2d(x1, y2);
            glEnd();
        }
    }
}

void Menu::DrawMenu(int cycTime) {
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
    FillBackground();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glRasterPos2i(200+0,500);
    //printf("bgImg.rgba = %d\n",bgImg.rgba );
    glDrawPixels(bgImg.wid,bgImg.hei,GL_RGBA,GL_UNSIGNED_BYTE,bgImg.rgba);
    
    HighlightDraw();
    glColor3ub(200,255, 255);
    //glRasterPos2i(275, 200);
    //YsGlDrawFontBitmap32x48("PAC-MAN");
    glRasterPos2i(200+380, 350);
    YsGlDrawFontBitmap16x20("START");
    glRasterPos2i(200+325, 400);
    YsGlDrawFontBitmap16x20("INSTRUCTION");
    glRasterPos2i(200+390, 450);
    YsGlDrawFontBitmap16x20("EXIT");
		//FsSwapBuffers();
    
    // Character movement
    int xdir, ydir, margin = 60 ;
    double x,y, disp =(cycTime*5)%(2*wid + 2*hei - 180);
    
    //printf("disp = %d\n", disp);
    if(0<= disp && disp < wid-margin){
        xdir = 1; ydir = 0; // right
        x = disp, y = 0;
    }else if((wid-margin) <= disp && disp < (wid-margin + hei - margin)){
        xdir = 0; ydir = -1;
        x = wid-margin;
        //printf("x = %d going down  dispalcement = %d \n",x,disp);
        y = disp - wid+margin;
        
    }else if( (wid-margin + hei - margin)<= disp && disp < (wid-margin + hei - margin + wid - margin)){
        xdir = -1; ydir = 0;
        x = (wid-margin + hei - margin + wid - disp), y = hei - margin;
    }else{
        xdir = 0; ydir = 1;
        x = 0; y = hei - (disp - (wid-margin + hei - margin + wid - margin) );
    }
    DrawPacMan(xdir, ydir,200+x,y);
    DrawPacMan(-xdir, - ydir,200+wid-margin - x, hei - margin - y);
    DrawGhost(ydir,-xdir,2,200+wid - margin - y/6*8,x/8*6,false);
    DrawGhost(-ydir,xdir,3,200+y/6*8,hei - margin-x/8*6,false);
    

}

void Menu::HighlightDraw(void) {

	glColor4f(0,0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glVertex2i(highlight_x, highlight_y);
	glVertex2i(highlight_x+200, highlight_y);
	glVertex2i(highlight_x+200, highlight_y-40);
	glVertex2i(highlight_x, highlight_y-40);
	glEnd();

}
