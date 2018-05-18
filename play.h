/*
 *	play.h - game logic and used as pacman environment
 */

#ifndef PLAYIMAGE_H
#define PLAYIMAGE_H

#include "yspng.h"
#include "yspngenc.h"
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "maze.h"
#include "maze3D.h"
#include "view.h"
#include <stdio.h>
#include "score.h"



class Play{
protected:
    /* Fancy Decoration */
	YsRawPngDecoder img;
	YsSoundPlayer musicPlayer;
	YsSoundPlayer::SoundData pacman_death, cherry, areyouready;

	/* Maze Params*/
	bool plot3d;
	View ghostView, pacView;
	FullMaze maze;
	FullMaze_3D maze_3d;
	int ***mazeArray;
	Agent pacInfo;
	vector<Agent> ghostInfo;
	time_t t0, dt, timeMax, timeLeft;
	int lives, countDown, loopCount;
   	bool setCherry, setPower; 
	/* Drawing functions */
	void DrawBackground();
	void DrawCountDown();
	void DrawGameInfo();
	void Draw2DMaze();
	void Draw3DMaze();

	bool exchangePlayers;
	void SendMazeCommand(int key);
	void Setup();
	void Update3DMaze();	

public:
    Play();
	Play(bool visualize, bool plot3d);
	~Play(){musicPlayer.End();};

	void Restart(bool exchangePlayers);
	void Restart();
	void Draw();
	void Step(int pacCmd, int ghostCmd, int &pacReward, int &ghostReward);
	void PacStep(int cmd, int &reward);
	void GhostStep(int cmd, int &reward);

	bool CheckEndCondition();
	void Render();
	bool CheckCountDown();
	void PauseTime();
	void UpdateTime();
	void UpdateGame();
};

Play::Play(){
	Setup();
	plot3d = false;
}

/* Render - Assumes main function is only running game */
void Play::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Draw();
	FsSwapBuffers();
}

Play::Play(bool visualize, bool plot3d){
	if(visualize == true) FsOpenWindow(0, 100, 1600, 600, 1);
	this->plot3d = plot3d;
	Setup();
	if(plot3d == true){
		mazeArray = new int**[6];
		for(int i = 0;i < 6;i++){
			mazeArray[i] = new int*[blockNumber];
			for(int j = 0;j < blockNumber;j++){
				mazeArray[i][j] = new int[blockNumber];
			}
		}
	}
}

void Play::Setup(){
    /* Set up background */
	img.Decode("graphs/PlayBackground.png");
    img.Flip();

	/* Set up 2D maze */
	maze.SetMaze(); // load map
	
	/* Game parameters */
	timeMax = 10;

	/* Set up music */
	musicPlayer.MakeCurrent();
	musicPlayer.Start();
	FsChangeToProgramDir();
	/* Load sound data */
	if (YSOK != pacman_death.LoadWav("music/pacman_death.wav")){
		printf("Error!  Cannot load pacman_death.wav!\n");
	}
	if (YSOK != cherry.LoadWav("music/pacman_eatfruit.wav")){
		printf("Error!  Cannot load pacman_eatfruit.wav!\n");
	}
	if (YSOK != areyouready.LoadWav("music/areyouready.wav")){
		printf("Error!  Cannot load pacman_eatfruit.wav!\n");
	}

}

void Play::PauseTime(){
	t0 = time(NULL);
}

void Play::UpdateTime(){
	time_t t = time(NULL);
	dt += (t - t0);
	t0 = time(NULL);
	timeLeft = timeMax - dt;
}

/* Check if the game has started */
bool Play::CheckCountDown(){
	if(countDown <= 0) return true;
	else{
		time_t t = time(NULL);
		countDown -= (t - t0);
		t0 = time(NULL);
	}
	return false;
}

bool Play::CheckEndCondition(){
	/* 
	 * Game ends one condition is satisfied 
	 * 1. times up 
	 * 2. pacman out of lives
	 */
	if(dt >= timeMax || lives <= 0){
		return true;
	}
	return false;	
}

void Play::UpdateGame(){
	// all data is set here, display
	if(dt > timeMax*(1.0/3.0) && setCherry == false){
		maze.SetCherry();
		setCherry = true;
	}
	if(dt > timeMax*(2.0/3.0) && setPower == false){
		maze.SetSuperPells();
		setPower = true;
	}
	
}

/* Sends commands in two player mode and updates game and score */
void Play::Step(int pacCmd, int ghostCmd, int &pacReward, int &ghostReward){
	/* Send command */
	maze.ChangePacDirection(pacCmd);
	maze.ChangeGhostDirection(ghostCmd);
	
	/* Update maze */
	int pacEat = maze.PacMove();
	switch(pacEat){
		case EAT_PELL:
			pacReward = 1;
			break;
		case EAT_CHERRY:
			pacReward = 20;
			break;
		case EAT_SUPERPELL:
			pacReward = 20;
			break;
		default:
			pacReward = 0;
	}
	maze.GhostMove(loopCount);
	
	int collision = maze.CollisionDetect();
	if(collision != COLL_NONE){
		if(collision == COLL_EATPAC){
			musicPlayer.Stop(pacman_death);
			musicPlayer.PlayOneShot(pacman_death);
			lives--;
			maze.SwitchGhost();
			ghostReward += 500;
			pacReward -= 500;

			/* Restore game to initial position */
			maze.Restore();
		}
		else{
			pacReward += 200;
			ghostReward -= 200;
		}
	}
	
	UpdateTime();
	UpdateGame();
	loopCount++;
	
}

/* Sends commands for pacman player only and updates game and score */
void Play::PacStep(int cmd, int &reward){
	/* Send command */
	maze.ChangePacDirection(cmd);
	
	/* Update maze */
	reward += maze.PacMove();
	if(maze.CollisionDetect()){
		musicPlayer.Stop(pacman_death);
		musicPlayer.PlayOneShot(pacman_death);
		lives--;
	}
	
	UpdateTime();
	UpdateGame();
	loopCount++;
	
}

/* Sends commands for ghost player only and updates game and score */
void Play::GhostStep(int cmd, int &reward){
	/* Send command */
	maze.ChangeGhostDirection(cmd);
	
	/* Update maze */
	maze.GhostMove(loopCount);
	if(maze.CollisionDetect()){
		musicPlayer.Stop(pacman_death);
		musicPlayer.PlayOneShot(pacman_death);
		lives--;
	}
	
	UpdateTime();
	UpdateGame();
	loopCount++;
	
	/* Update score */
	reward = 0;
}

/* Restart game */
void Play::Restart(bool exchangePlayers){
	musicPlayer.KeepPlaying();
	maze.Restart();
	this->exchangePlayers = exchangePlayers;
	
	t0 = time(NULL);
	timeLeft = timeMax;
	dt = 0;
	lives = 3;
	countDown = 3;
	loopCount = 0;
	setPower = false;
	setCherry = false;
	/* Play start music */
	musicPlayer.Stop(areyouready);
	musicPlayer.PlayOneShot(areyouready);
}

/* Restart game */
void Play::Restart(){
	musicPlayer.KeepPlaying();
	maze.Restart();
	exchangePlayers = false;
	
	t0 = time(NULL);
	timeLeft = timeMax;
	dt = 0;
	lives = 3;
	countDown = 3;
	loopCount = 0;
	setPower = false;
	setCherry = false;
	/* Play start music */
	musicPlayer.Stop(areyouready);
	musicPlayer.PlayOneShot(areyouready);
}

void Play::SendMazeCommand(int key){
	if(exchangePlayers == false){
		switch(key){
			case FSKEY_LEFT:
				maze.ChangePacDirection(1);
				break;
			case FSKEY_UP:
				maze.ChangePacDirection(2);
				break;
			case FSKEY_RIGHT:
				maze.ChangePacDirection(3);
				break;
			case FSKEY_DOWN:
				maze.ChangePacDirection(4);
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
				maze.SwitchGhost();
				break;
		}
	}
	else{
		switch(key){
			case FSKEY_A:
				maze.ChangePacDirection(1);
				break;
			case FSKEY_W:
				maze.ChangePacDirection(2);
				break;
			case FSKEY_D:
				maze.ChangePacDirection(3);
				break;
			case FSKEY_S:
				maze.ChangePacDirection(4);
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
				maze.SwitchGhost();
				break;
		}
	}

}

void Play::Draw2DMaze(){
	maze.Draw();
}

void Play::Draw3DMaze(){
	Update3DMaze();
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
	/* Plot on two sides */
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
	IntToChar(timeLeft, timeHeader, nullString, displayTime);

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
	if(plot3d == true) Draw3DMaze();
	else Draw2DMaze();
	if(countDown > 0){
		DrawCountDown();
	}
}

/* Read data from 2d Maze and load to 3d maze */
void Play::Update3DMaze(){
	maze.ReturnMaze(mazeArray);
	maze.ReturnPacman(pacInfo);
	maze.ReturnGhost(ghostInfo);

	/* Load data to 3d maze */
	maze_3d.SetMaze(mazeArray);
	maze_3d.SetCursor(pacInfo);
	maze_3d.SetGhost(&ghostInfo);
}


#endif
