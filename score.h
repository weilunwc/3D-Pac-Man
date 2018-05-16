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

using namespace std;
extern const string nullString;

/* Combine a number into a sentence char array */
void IntToChar(int input, string header, string footer, char* charArray){
	/* Change number to char array */
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
	strcpy(charArray, output.c_str());
}

class Score{
public:

	Score();
	void Draw();
	void ResetScore();
	inline void SetScore1(int);
	inline void SetScore2(int);
	
	/* Read buttons */
	bool ReadRematch();
	bool ReadMenu();

private:
	YsRawPngDecoder png;
	Button menu, rematch;
	void FillBackground();
	int score1, score2;
};

Score::Score() : menu(700, 440), rematch(700, 490){
	png.Decode("graphs/pacman.png");
	png.Flip();
	ResetScore();

	rematch.SetText("Again");
	menu.SetText("Menu");
}

void Score::SetScore1(int score){
	score1 = score;
}

void Score::SetScore2(int score){
	score2 = score;
}

void Score::FillBackground(){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(0,0);
	glVertex2i(1600,0);
	glVertex2i(1600,600);
	glVertex2i(0,600);
	glEnd();
}

void Score::ResetScore(){
	score1 = 0;
	score2 = 0;
}

void Score::Draw(void) {
	/* position the background picture */
	FillBackground();
	glRasterPos2i(130,599);
	glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE, png.rgba);
	glColor3ub(0, 0, 0);
	
	/* Display score */
	glColor3ub(255,255,255);
	glRasterPos2i(200+280, 450);
	char player1[1024], player2[1024];
	IntToChar(score1, "Player1 Score: ", nullString, player1);
	YsGlDrawFontBitmap16x20(player1);
	glRasterPos2i(200+280, 500);
	IntToChar(score2, "Player2 Score: ", nullString, player2);
	YsGlDrawFontBitmap16x20(player2);

	/* Winner and display */

	char *winner;
	winner  = new char[256];
	if(score1 > score2){
		strcpy(winner, "Player 1 Won !");
		glRasterPos2i(200+270, 170);
	}
	else if (score1 < score2){
		strcpy(winner, "Player 2 Won !");
		glRasterPos2i(200+270, 170);
	}
	else{
		strcpy(winner, "A Draw ! Wanna Rematch ?");
		glRasterPos2i(200+130, 170);
	}
	
	YsGlDrawFontBitmap24x40(winner);
	if(winner != nullptr){
		delete [] winner;
	}
	
	/* Plot buttons */
	menu.Draw();
	rematch.Draw();
}

/* Read the buttons */
bool Score::ReadMenu(){
	return menu.ReadState();
}

bool Score::ReadRematch(){
	return rematch.ReadState();
}

#endif
