/*
 *	score.h - defines the display of the scoring page after a full game is over
 */

#ifndef SCORE_H
#define SCORE_H

#include "yspng.h"
#include "yspngenc.h"
#include <string.h>
#include "fssimplewindow.h"
#include "button.h"

typedef struct DataStruct{
	int pells;
	int livesLeft;
	int time;
	int ghost_eaten;
	int pacman_eaten;
	int cherry;
	int score;
}Data;

extern const string nullString;

void IntToChar(int input,string header,string footer,char* charArray){
	stringstream ss;
	ss << input;
	string output;
	output = ss.str();
	if(header != nullString){
		output = header + output;
	}
	if(footer != nullString){
		output = output + footer;
	}
	strcpy(charArray,output.c_str());
}

class Score{
public:
	YsRawPngDecoder png;
	Data data[2];
	Score();
	void Draw();
	void ResetScore();
	void SetPlayer1(int,int,int,int,int);
	void SetPlayer2(int,int,int,int,int);
	void SetGhost(int,int);
	void SetPacman(int,int,int,int);
	void FillBackground(void)const;
	bool ReadRematch();
	bool ReadMenu();

private:
	Button menu, rematch;
};

Score::Score() : menu(700, 550), rematch(700, 500){
	png.Decode("graphs/pacman.png");
	png.Flip();
	ResetScore();

	rematch.SetText("Again");
	menu.SetText("Menu");
}

void Score::FillBackground(void)const{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(0,0);
	glVertex2i(1600,0);
	glVertex2i(1600,600);
	glVertex2i(0,600);
	glEnd();
}

void Score::SetGhost(int player,int pacman_eaten){
	data[player].pacman_eaten = pacman_eaten;
}


void Score::SetPacman(int player,int ghost_eaten,int pells,int cherry){
	data[player].pells = pells;
	data[player].ghost_eaten = ghost_eaten;
	data[player].cherry = cherry;
}


void Score::SetPlayer1(int pells1,int livesLeft1,int ghost_eaten1,int pac_eaten1,int timeLeft)
{
	data[0].pells = pells1;
	data[0].livesLeft = livesLeft1;
	data[0].ghost_eaten = ghost_eaten1;
	data[0].pacman_eaten = pac_eaten1;
	data[0].score = data[0].pells*20 + data[0].livesLeft*20 + data[0].ghost_eaten*50 + data[0].pacman_eaten*50 + timeLeft;
}

void Score::SetPlayer2(int pells2,int livesLeft2,int ghost_eaten2,int pac_eaten2, int timeLeft){
	data[1].pells = pells2;
	data[1].livesLeft = livesLeft2;
	data[1].ghost_eaten = ghost_eaten2;
	data[1].pacman_eaten = pac_eaten2;
	data[1].score = data[1].pells*20 + data[1].livesLeft*25 + data[1].ghost_eaten*50 + data[1].pacman_eaten*50 + timeLeft;

}


void Score::ResetScore(){
	for(int i = 0;i < 2;i++){
		data[i].pells = 0;
		data[i].livesLeft = 0;
		data[i].time = 0;
		data[i].cherry = 0;
		data[i].pacman_eaten = 0;
		data[i].ghost_eaten = 0;
		data[i].score = 0;
	}
}

void Score::Draw(void) {
	// position the background picture
	for(int i = 0;i<2;i++){
		data[i].score = data[i].pells*20 + data[i].ghost_eaten*100 + 
													data[i].pacman_eaten*150 + data[i].cherry*30;
	}
	FillBackground();
	glRasterPos2i(130,599);
	glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
	glColor3ub(0, 0, 0);

	//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//    glEnable(GL_BLEND);
	//
	//    glColor4ub(1.0, 1.0, 1.0,0.5);
	//    glBegin(GL_QUADS);
	//    glVertex2i(200,0);
	//    glVertex2i(1400,0);
	//    glVertex2i(1400,600);
	//    glVertex2i(200,600);
	//    glEnd();


	glColor3ub(255,255,255);
	glRasterPos2i(200+ 280, 450);
	char score1[1024],score2[1024];
	IntToChar(data[0].score,"Player1 Score: ",nullString,score1);
	YsGlDrawFontBitmap16x20(score1);
	glRasterPos2i(200+280, 500);
	IntToChar(data[1].score,"Player2 Score: ",nullString,score2);
	YsGlDrawFontBitmap16x20(score2);

	// winner
	glRasterPos2i(200+270, 170);
	char *winner;
	winner  = new char[256];
	if(data[0].score > data[1].score){
		strcpy(winner,"Player 1 Won !");
	}else if (data[0].score < data[1].score){
		strcpy(winner,"Player 2 Won !");
	}else{
		strcpy(winner,"A Draw ! Congratulations!");
	}
	YsGlDrawFontBitmap24x40(winner);
	if(winner != nullptr){
		delete [] winner;
	}
	
	/* Plot buttons */
	menu.Draw();
	rematch.Draw();
}

bool Score::ReadMenu(){
	return menu.ReadState();
}

bool Score::ReadRematch(){
	return rematch.ReadState();
}

#endif
