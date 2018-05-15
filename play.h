/*
 *	Draws the background page when playing
 */

#ifndef PLAYIMAGE_H
#define PLAYIMAGE_H

#include "yspng.h"
#include "yspngenc.h"
#include "fssimplewindow.h"
#include "maze.h"
#include "maze3D.h"
#include "view.h"
#include <stdio.h>
#include "score.h"
class PlayImage{
private:
    YsRawPngDecoder img;
public:
    PlayImage();
    void DrawBackground();
};

PlayImage::PlayImage(){
    img.Decode("graphs/PlayBackground.png");
    img.Flip();
}

void PlayImage::DrawBackground(){
    /* fill background */
    glColor3ub(3, 8, 20);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,600);
    glVertex2i(0,600);
    glEnd();
	
	/* Draw image */
    glRasterPos2i(175,599);
    glDrawPixels(img.wid,img.hei,GL_RGBA,GL_UNSIGNED_BYTE,img.rgba);
}

class Play{
protected:
    YsRawPngDecoder img;
	FullMaze maze;
    void DrawBackground();
	void DrawCountDown();
	void DrawGameInfo();
	void DrawMaze();
	time_t t0, dt, timeMax, timeLeft;
	int lives, countDown, loopCount;
	bool exchangePlayers, pause;
public:
    Play();
	void Restart();
	void Draw();
	void SendMazeCommand(int key);

};

Play::Play(){
    /* Set up background */
	img.Decode("graphs/PlayBackground.png");
    img.Flip();

	/* Set up 2D maze */
	maze.SetMaze(); // load map
	
	/* Game parameters */
	timeMax = 60;

}

void Play::Restart(){
	maze.Restart();
	t0 = time(NULL);
	timeLeft = timeMax;
	dt = 0;
	lives = 3;
	pause = false;
	countDown = 3;
	loopCount = 3;
	exchangePlayers = false;
}

void Play::SendMazeCommand(int key){
	if(exchangePlayers == false){
		switch(key){
			case FSKEY_LEFT:
				maze.ChangeDirection(1);
				break;
			case FSKEY_UP:
				maze.ChangeDirection(2);
				break;
			case FSKEY_RIGHT:
				maze.ChangeDirection(3);
				break;
			case FSKEY_DOWN:
				maze.ChangeDirection(4);
				break;
			case FSKEY_A:
				maze.ChangeGhostDirection(1);
				break;
			case FSKEY_W:
				maze.ChangeGhostDirection(2);
				break;
			case FSKEY_D:
				maze.ChangeGhostDirection(3);
				break;
			case FSKEY_S:
				maze.ChangeGhostDirection(4);
				break;
			case FSKEY_1:
				maze.SwitchGhost(0);
				break;
		}
	}
	else{
		switch(key){
			case FSKEY_A:
				maze.ChangeDirection(1);
				break;
			case FSKEY_W:
				maze.ChangeDirection(2);
				break;
			case FSKEY_D:
				maze.ChangeDirection(3);
				break;
			case FSKEY_S:
				maze.ChangeDirection(4);
				break;
			case FSKEY_LEFT:
				maze.ChangeGhostDirection(1);
				break;
			case FSKEY_UP:
				maze.ChangeGhostDirection(2);
				break;
			case FSKEY_RIGHT:
				maze.ChangeGhostDirection(3);
				break;
			case FSKEY_DOWN:
				maze.ChangeGhostDirection(4);
				break;
			case FSKEY_M:
				maze.SwitchGhost(0);
				break;
		}
	}

}

void Play::DrawMaze(){
	maze.Draw();
}

/* Draw the countdown page */
void Play::DrawCountDown(){
	/* Change the background color transparent */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 0.0, 0.0, 0.7);
	
	/* Draw count down time */
	glBegin(GL_QUADS); // big bar 
	glVertex2i(0,0);
	glVertex2i(1600,0);
	glVertex2i(1600,600);
	glVertex2i(0,600);
	glEnd();

	char displayCountDown[1024]; // time
	IntToChar(countDown, nullString, nullString, displayCountDown);
	glColor3ub(255,255,255);
	glRasterPos2i(600,300);
	YsGlDrawFontBitmap32x48(displayCountDown);
}

/* Display background picture */
void Play::DrawBackground(){
    /* fill background */
    glColor3ub(3, 8, 20);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,600);
    glVertex2i(0,600);
    glEnd();
	
	/* Draw image */
    glRasterPos2i(175,599);
    glDrawPixels(img.wid,img.hei,GL_RGBA,GL_UNSIGNED_BYTE,img.rgba);
}

/* Drae Game info such as lives, player, timeleft */
void Play::DrawGameInfo(){
	/* Preprocess string text to display */
	string playerHeader = "Player ";
	char displayPlayer[1024];
	if(exchangePlayers == false){
		IntToChar(1, playerHeader, nullString, displayPlayer);
	}
	else{
		IntToChar(2, playerHeader, nullString, displayPlayer);
	}

	string timeHeader = "Time Left: ";
	char displayTime[1024];
	IntToChar(timeLeft,timeHeader, nullString, displayTime);

	string livesHeader = "Lives: ";
	char displayLives[1024];
	IntToChar(lives, livesHeader, nullString, displayLives);
	
	/* Draw the game info */
	glColor3ub(255, 255, 255);
	glRasterPos2i(10, 20);
	YsGlDrawFontBitmap8x12(displayPlayer);
	glRasterPos2i(10, 40);
	YsGlDrawFontBitmap8x12(displayTime);
	glRasterPos2i(10,60);
	YsGlDrawFontBitmap8x12(displayLives);
}

void Play::Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawBackground();
	DrawGameInfo();
	if(countDown > 0){
		DrawCountDown();
	}
	maze.Draw();
}



class Play3D : public Play{
private:

	FullMaze_3D maze_3d;
	View ghostView, pacView;
	
	int ***mazeArray;
	PacMan pacInfo;
	vector<Ghost> ghostInfo;
	void DrawMaze();
public:
	Play3D();
	void Draw();
	void Update3DMaze();

};

Play3D::Play3D(){
	mazeArray = new int**[6];
	for(int i = 0;i < 6;i++){
		mazeArray[i] = new int*[blockNumber];
		for(int j = 0;j < blockNumber;j++){
			mazeArray[i][j] = new int[blockNumber];
		}
	}
}

void Play3D::Update3DMaze(){
	maze.ReturnMaze(mazeArray);
	maze.ReturnPacman(&pacInfo);
	maze.ReturnGhost(&ghostInfo);

	maze_3d.SetMaze(mazeArray);
	maze_3d.SetCursor(pacInfo);
	maze_3d.SetGhost(&ghostInfo);
}

void Play3D::DrawMaze(){
	
	int ghostNow = maze.ReturnGhostControl();
	
	/* Store the window size */	
	int wid,hei;
	FsGetWindowSize(wid,hei);

	/* Plot the pacman camera view */	
	pacView.CameraFollow(pacInfo.surface, pacInfo.x, pacInfo.y);
	if(exchangePlayers == false){
		glViewport(wid/4,0, wid, hei);
	}
	else{
		glViewport(-wid/4,0,wid,hei);
	}
	pacView.SetView();
	maze_3d.Draw();
	
	/* Plot the ghost camera view */
	ghostView.CameraFollow(ghostInfo[ghostNow].surface, ghostInfo[ghostNow].x, 
								ghostInfo[ghostNow].y);
	if(exchangePlayers == false){
		glViewport(-wid/4,0,wid,hei);
	}
	else{
		glViewport(wid/4,0,wid,hei);
	}
	ghostView.SetView();
	maze_3d.Draw();

	/* Reset 2D to display other 2D objects */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid-1, (float)hei-1, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, wid, hei);
}

void Play3D::Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawBackground();
	DrawGameInfo();
}


#endif
