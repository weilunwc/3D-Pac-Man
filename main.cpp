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


int main(void){

	int menuLoop = 0;
	int ruleLoop = 0;
	
	srand((int)time(NULL));
	FullMaze maze;
	Menu menu;
	Rule rule;

	Score score;
	maze.SetMaze();
	PauseMenu pauseMenu;
	
	Play play(plot3d);
	
	FsOpenWindow(0,100,1600,600,1);
	FsPollDevice();
	int key = FsInkey();
	int gameState = GAME_MENU;
	bool pause = false;
	int pauseState;
	int countDown;
	int mouseEvent;
	int loopCount;
	int lb,mb,rb,mx,my;
	int lives;
	int pac_eaten = 0;
	bool rematch, finishGame;

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
				play.Restart();
				rematch = false;
				pause = false;
				finishGame = false;
				/* Start game */
				while(key != FSKEY_ESC && gameState == GAME_PLAY){
					/* Play background music */
					play.PlayBackgroundMusic();

					/* Get external device commands */
					FsPollDevice();
					key = FsInkey();
					if(key == FSKEY_SPACE) pause = !pause;	
					if(pause == false){
						play.Step(key);
					}


					/* Graphical display */	
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					play.Draw();;
					finishGame = play.CheckEndCondition();
					
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
								gameState = GAME_PLAY;
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
					FsSleep(20);

					/* If the user decided to rematch in pause page */
					if(rematch){
						break;
					}
					if(finishGame){
						gameState = GAME_SCORE;
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
	/* End of game */
	return 0;
}





