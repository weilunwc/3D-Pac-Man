#include "yspng.h"
#include "yspngenc.h"
#include <stdio.h>

class PlayImage{
protected:
    YsRawPngDecoder img;
public:
    PlayImage(void);
    void Draw(void);
};

PlayImage::PlayImage(void){
    img.Decode("PlayBackground.png");
    img.Flip();
}


void PlayImage::Draw(void){
    // fill background
    glColor3ub(3, 8, 20);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,600);
    glVertex2i(0,600);
    glEnd();
    
    glRasterPos2i(175,599);
    glDrawPixels(img.wid,img.hei,GL_RGBA,GL_UNSIGNED_BYTE,img.rgba);

}
