/*
 *	Main function of the 3D-pacman project where all the game switching logic is programmed
 *	Maintainer: Wei Lun William Chen
 *	email: weilunwc@andrew.cmu.edu
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "maze.h"
#include "play.h"
#include "menu.h"
#include "score.h"
#include "rule.h"
#include "maze3D.h"
#include "pauseMenu.h"
#include "yssimplesound.h"
#include "view.h"

using namespace std;

const int blockNumber = 25;
int blockSize_2D = 6;
int blockSize_3D = 7;
const string nullString = "\0";
bool plot3d = true;
//bool plot3d = false;


double myPi = 3.1415926;
const int ghostNumber = 10;
const int totalPells = 1883;

void DrawCountDown(int countDown){
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

void DrawGameInfo(){
}

void SendMazeCommand(FullMaze &maze, int key, bool exchangePlayers){
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



int main(void){

	int menuLoop = 0;
	int ruleLoop = 0;
	
	int ***mazeArray;
	PacMan pacInfo;
	srand((int)time(NULL));
	vector<Ghost> ghostInfo;
	mazeArray = new int**[6];
	for(int i = 0;i < 6;i++){
		mazeArray[i] = new int*[blockNumber];
		for(int j = 0;j < blockNumber;j++){
			mazeArray[i][j] = new int[blockNumber];
		}
	}
	FullMaze maze;
	Menu menu;
	Rule rule;

	Score score;
	maze.SetMaze();
	PauseMenu pauseMenu;
	FullMaze_3D maze_3d;
	PlayImage play;
	View pacView, ghostView;
	//camera1.z = 10.0;
	Play playTest;
	
	FsOpenWindow(0,100,1600,600,1);
	FsPollDevice();
	int key = FsInkey();
	int gameState = GAME_MENU;
	bool exchangePlayers;
	bool pause = false;
	int pauseState;
	int countDown;
	int mouseEvent;
	int loopCount;
	int lb,mb,rb,mx,my;
	time_t  t0,t,dt,timeLeft,timeMax,totalTimeLeft = 0;
	timeMax = 60;
	int lives;
	int pac_eaten = 0;
	bool rematch;
	/* Set up music */
	YsSoundPlayer musicPlayer;
	musicPlayer.MakeCurrent();
	musicPlayer.Start();
	FsChangeToProgramDir();
	/* Load sound data */
	YsSoundPlayer::SoundData pacman_death, scene, cherry, areyouready;
	if (YSOK != pacman_death.LoadWav("music/pacman_death.wav")){
		printf("Error!  Cannot load pacman_death.wav!\n");
	}
	if (YSOK != scene.LoadWav("music/scene.wav")){
		printf("Error!  Cannot load scene.wav!\n");
	}
	if (YSOK != cherry.LoadWav("music/pacman_eatfruit.wav")){
		printf("Error!  Cannot load pacman_eatfruit.wav!\n");
	}
	if (YSOK != areyouready.LoadWav("music/areyouready.wav")){
		printf("Error!  Cannot load pacman_eatfruit.wav!\n");
	}

	/* Start game */	
	while(key != FSKEY_ESC){
		switch(gameState){
			case GAME_MENU:
				/* Main menu */
				menuLoop = 0;
				while(key != FSKEY_ESC && gameState == 0){
					/* Read keyboard input */
					FsPollDevice();
					key = FsInkey();
					gameState = menu.ReadInput(key);
					/* Graphical display */           
					glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
					menu.DrawMenu(menuLoop); // menuloop for pacman animation
					FsSwapBuffers();
					FsSleep(20);
					menuLoop++;
				}
				break;
			case GAME_PLAY:
				/* Game mode */
				musicPlayer.KeepPlaying();
				maze.Restart();
				t0 = time(NULL);
				dt = 0;
				timeLeft = timeMax;
				lives = 3;
				pause = false;
				countDown = 3;
				loopCount = 0;
				score.ResetScore();
				exchangePlayers = false;
				rematch = false;
				/* Start game */
				while(key != FSKEY_ESC && gameState == GAME_PLAY){
					/* Get external device commands */
					FsPollDevice();
					key = FsInkey();
					if(key == FSKEY_SPACE) pause = !pause;	
					
					if(loopCount == 1){
						musicPlayer.Stop(areyouready);
						musicPlayer.PlayOneShot(areyouready);
					}
					musicPlayer.PlayBackground(scene);
					
					if(pause == false && countDown <= 0){
						/* Game running */
						
						/* Send commands to the pacman and ghost */
						SendMazeCommand(maze, key, exchangePlayers);
						int n = maze.cherries;
						maze.Move();
						if(maze.cherries > n){
							musicPlayer.Stop(scene);
							musicPlayer.Stop(cherry);
							musicPlayer.PlayOneShot(cherry);
						}
						maze.GhostMove(loopCount);
						if(maze.CollisionDetect()){
							musicPlayer.Stop(scene);
							musicPlayer.Stop(pacman_death);
							musicPlayer.PlayOneShot(pacman_death);
							lives--;
							pac_eaten++;
							totalTimeLeft += timeLeft;
							maze.SwitchGhost(0);
						}
						// update the time
						t = time(NULL);
						dt += (t - t0);
						t0 = time(NULL);
						timeLeft = timeMax - dt;
						// all data is set here, display
						if(loopCount == 50){
							maze.SetCherry();
						}
						if(loopCount == 150){
							maze.SetPowerPells();
						}
						loopCount++;
					}
					/* Pause gameState */
					else{
						if(countDown <= 0){
							t0 = time(NULL);
						}
						else{
							t = time(NULL);
							countDown -= (t - t0);
							t0 = time(NULL);
						}
					}

					/* Graphical display */	
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					play.DrawBackground();

					if(plot3d == true){
						maze.ReturnMaze(mazeArray);
						maze.ReturnPacman(&pacInfo);
						maze.ReturnGhost(&ghostInfo);
						int ghostNow = maze.ReturnGhostControl();
						maze_3d.SetMaze(mazeArray);
						maze_3d.SetCursor(pacInfo);
						maze_3d.SetGhost(&ghostInfo);
						
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
					else{
						maze.Draw();
					}
					/* Finish drawing the maze Now draw game info */
					
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
					
					/* Count down 3 2 1 */
					if(countDown > 0){
						DrawCountDown(countDown);
					}
					/* Pause game */
					if(pause == true){
						pauseState = pauseMenu.ReadInput(key);
						switch(pauseState){
							case PAUZE_RESUME:
								/* resume */
								pause = false;
								break;
							case PAUZE_REMATCH:
								/* rematch */
								rematch = true;
								break;
							case PAUZE_MENU:
								/* menu */
								gameState = GAME_MENU;
								break;
							default:
								/* to prevent bug resume playing */
								gameState = GAME_PLAY;
						}
						pauseMenu.Draw();
					}
					FsSwapBuffers();
					FsSleep(1);

					//if(lives <= 0 || maze.perls == totalPells){
					if(dt >= timeMax || lives <= 0 || maze.perls == totalPells){
						int perls = maze.perls;
						if(exchangePlayers == true){
							// game finished
							score.SetGhost(0, 3-lives);
							score.SetPacman(1, maze.ghost_eaten, perls, maze.cherries);
							gameState = GAME_SCORE;
						}
						else{
							// switch players
							//score.SetPlayer2(perls,lives,0,0,(int)totalTimeLeft);
							//score.SetPlayer1(0,0,0,pac_eaten,2*(int)totalTimeLeft);
							score.SetGhost(1,3-lives);
							score.SetPacman(0, maze.ghost_eaten, perls, maze.cherries);
							maze.Restart();
							t0 = time(NULL);
							dt = 0;
							lives = 3;
							timeLeft = timeMax;
							loopCount = 0;
							exchangePlayers = true;
							totalTimeLeft = 0;
							countDown = 3;
						}
					}
					/* If the user decided to rematch in pause page */
					if(rematch){
						break;
					}
				}
				break;
			case GAME_RULE:
				/* Rules page */
				ruleLoop = 0;
				while(key != FSKEY_ESC && gameState == GAME_RULE){
					/* Read external device */
					FsPollDevice();
					mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);
					key = FsInkey();
					if(rule.ReadMenu() == true){
						gameState = GAME_MENU;
					}

					/* graphics */
					glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
					rule.Draw(ruleLoop);
					FsSwapBuffers();
					FsSleep(20);
					ruleLoop++;
				}
				break;
			case GAME_SCORE:
				/* Score page */
				while(key != FSKEY_ESC && gameState == GAME_SCORE){
					/* interact with external device */
					FsPollDevice();
					key = FsInkey();
					if(score.ReadMenu() == true){
						gameState = GAME_MENU;
					}
					if(score.ReadRematch() == true){
						gameState = GAME_PLAY;
					}

					/* graphical display */
					glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
					score.Draw();
					FsSwapBuffers();
					FsSleep(20);
				}
				break;
			case GAME_EXIT:
				/* Exit State */
				key = FSKEY_ESC;
				break;
			default:
				/* Could be an error, redirect to menu page */
				FsPollDevice();
				key = FsInkey();
				gameState = GAME_MENU;
				FsSleep(20);
				break;
		}

	}
	/* End of game, clean up resources */
	for(int i =0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			delete [] mazeArray[i][j];
		}
		delete [] mazeArray[i];
	}
	delete [] mazeArray;
	musicPlayer.End();
	return 0;
}





