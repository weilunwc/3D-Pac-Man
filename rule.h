
class Rule{
public:
    YsRawPngDecoder bgImg;
    Rule(void);
    void PacManMotion(int x, int y,int gx, int gy, int pixSize, int lpt );
	void Draw(int);
    void FillBackground(void)const;
};

Rule::Rule(void){
    bgImg.Decode("Rule_bgd.png");
    bgImg.Flip();
}

void Rule::FillBackground(void)const{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,600);
    glVertex2i(0,600);
    glEnd();
}

void Rule::Draw(int lpt) {
    // background
    FillBackground();
    glRasterPos2i(200+0, 599);
    glDrawPixels(bgImg.wid,bgImg.hei,GL_RGBA,GL_UNSIGNED_BYTE,bgImg.rgba);
    // words
  glColor3ub(255, 255, 255);
  glRasterPos2i(200+300, 50);
  YsGlDrawFontBitmap16x20("Instructions");

    glRasterPos2i(200+50, 100);
    YsGlDrawFontBitmap12x16("Ghosts");
    glRasterPos2i(200+50, 140);
    YsGlDrawFontBitmap8x12("W : Move Up");
    glRasterPos2i(200+50, 180);
    YsGlDrawFontBitmap8x12("S : Move Down");
    glRasterPos2i(200+50, 220);
    YsGlDrawFontBitmap8x12("A : Move Left");
    glRasterPos2i(200+50, 260);
    YsGlDrawFontBitmap8x12("D : Move Right");
    glRasterPos2i(200+50, 300);
    YsGlDrawFontBitmap8x12("1 or M : Switch Ghosts");// to be determined
    glRasterPos2i(200+50, 320);
    YsGlDrawFontBitmap8x12("");

    glRasterPos2i(200+40, 340);
    YsGlDrawFontBitmap8x12("GOAL : Eat PAC-MAN with");
    glRasterPos2i(200+50, 360);
    YsGlDrawFontBitmap8x12("\t\t the minimum amount of");
    glRasterPos2i(200+50, 380);
    YsGlDrawFontBitmap8x12("\t\t time while avoiding");
    glRasterPos2i(200+50, 400);
    YsGlDrawFontBitmap8x12("\t\t super \'PAC-MAN\'");

    glRasterPos2i(200+650, 100);
    YsGlDrawFontBitmap12x16("Pac-Man");
    glRasterPos2i(200+640, 140);
    YsGlDrawFontBitmap8x12("UP : Move Up");
    glRasterPos2i(200+618, 180);
    YsGlDrawFontBitmap8x12("DOWN : Move Down");
    glRasterPos2i(200+620, 220);
    YsGlDrawFontBitmap8x12("LEFT : Move Left");
    glRasterPos2i(200+610, 260);
    YsGlDrawFontBitmap8x12("RIGHT : Move Right");
    glRasterPos2i(200+600, 300);
    YsGlDrawFontBitmap8x12("");

    glRasterPos2i(200+560, 320);
    YsGlDrawFontBitmap8x12("GOAL : Eat as many pells");
    glRasterPos2i(200+570, 340);
    YsGlDrawFontBitmap8x12("\t\tas possible within 60s ");
    glRasterPos2i(200+570, 360);
    YsGlDrawFontBitmap8x12("\t\twhile avoiding being");
    glRasterPos2i(200+570, 380);
    YsGlDrawFontBitmap8x12("\t\teaten by any ghosts");



    glRasterPos2i(200+200, 460);
    YsGlDrawFontBitmap8x12("Each player has 3 lives and maximum 60s each life.");
  glRasterPos2i(200+200, 490);
  YsGlDrawFontBitmap8x12("Pac-Man can eat ghosts after eating the superpells");
  glRasterPos2i(200+150, 520);
  YsGlDrawFontBitmap8x12("If ghosts are all eliminated or pells are all consumed, Pac - Man wins.");
    glRasterPos2i(200+200, 550);
    YsGlDrawFontBitmap8x12("If PAC-MAN is eaten by any ghost. Ghosts win.");


    // graphics
    PacManMotion(200+500,100, 200+200, 100,4,lpt);



}



void Rule::PacManMotion(int x, int y,int gx, int gy,int pixSize, int lpt){
    //printf("Draw Pacman\n");
    int dx, dy,  i ,j;
    int x1, y1, x2, y2;
    char curChar; char *pattern1;
    int hei = 27; // hei and wid are har coded
    int wid = 27; // can be changed to scale the bitmap
    char open[] =
    {
        ".....44444................."
        "...444444444..............."
        "..44444444444.............."
        "..440044444444............."
        ".44400444444..............."
        ".444444444................."
        ".4444444....11.....11....11"
        ".444444.....11.....11....11"
        ".44444444.................."
        ".4444444444................"
        "..444444444444............."
        "..44444444444.............."
        "...444444444..............."
        ".....44444................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
    };
    char close[] = {
        ".....44444................."
        "...444444444..............."
        "..44404444444.............."
        "..44000444444.............."
        ".4400400444444............."
        ".4444444444444............."
        ".4444444444444.....11....11"
        ".4444444444444.....11....11"
        ".4444444444444............."
        ".4444444444444............."
        "..44444444444.............."
        "..44444444444.............."
        "...444444444..............."
        ".....44444................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."
        "..........................."

    };

    char *pattern2;
    int ghei = 14, gwid = 14;
    char ghost1[] =
    {
        ".....1111....."
        "...11111111..."
        "..1111111111.."
        ".111111111111."
        ".112211112211."
        ".123321123321."
        "11233211233211"
        "11221111122111"
        "11111111111111"
        "11111111111111"
        "11111111111111"
        "11111111111111"
        "11.111..111.11"
        "1...11..11...1"
    };
    char ghost2[] =
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //printf("Rule loop count = %d\n", lpt);
    if(lpt%50 >= 25){
        // open
        pattern1 = open;
        pattern2 = ghost1;
    }else{
        // close
        pattern1 = close;
        pattern2 = ghost2;
    };

    // pacman
    for (dy = 0; dy < hei; dy++) {
        for (dx = 0; dx < wid; dx++) {
            // to the right
            curChar = pattern1[dx + dy*hei];
            //printf("one char = %c\n", curChar);
            if (curChar == '4') {
                glColor3f(1.0, 1.0, 0.0); // yellow
            }
            else if(curChar == '0') { // eye color - black
                glColor3f(0.0, 0.0, 0.0);
            }else if(curChar == '1') {
                glColor3f(1.0, 1.0, 1.0);
            }else{
                glColor4ub(255, 102, 255,0);// transparent background
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

    x1 = 0; y1 = 0;

    // ghost
    for (dy = 0; dy < ghei; dy++) {
        for (dx = 0; dx < gwid; dx++) {
            // to the right
            curChar = pattern2[dx + dy*ghei];
            //printf("one char = %c\n", curChar);
            if (curChar == '1') {
                glColor3f(1.0, 0.5, 1.0);
            }
            else if(curChar == '3') { // eye color - black
                glColor3f(0.0, 0.0, 0.0);
            }else if(curChar == '2') {
                glColor3f(1.0, 1.0, 1.0);
            }else{
                glColor4ub(255, 102, 255,0);// transparent background
            }
            x1 = gx + dx * pixSize;
            y1 = gy + dy * pixSize;
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



