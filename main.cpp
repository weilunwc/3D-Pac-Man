/*
 *	Main function of the 3D-pacman project where all the game logic is programmed
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

using namespace std;

const int blockNumber = 25;
int blockSize2D = 6;
int blockSize3D = 7;
const string nullString = "\0";

double myPi = 3.1415926;
//const int ghostNumber = 10;

/* Changes the keyboard commands to pacman control commnads */
int Key2PacCmd(int key, bool exchangePlayers){
	int cmd;
	if(exchangePlayers == false){
		/* player on the right is pacman */	
		switch(key){
			case FSKEY_LEFT:
				cmd = PAC_LEFT;
				break;
			case FSKEY_RIGHT:
				cmd = PAC_RIGHT;
				break;
			case FSKEY_UP:
				cmd = PAC_UP;
				break;
			case FSKEY_DOWN:
				cmd = PAC_DOWN;
				break;
			default:
				cmd = PAC_NONE;
				break;
		}
	}
	else{
		/* player on the left is pacman */
		switch(key){
			case FSKEY_A:
				cmd = PAC_LEFT;
				break;
			case FSKEY_D:
				cmd = PAC_RIGHT;
				break;
			case FSKEY_W:
				cmd = PAC_UP;
				break;
			case FSKEY_S:
				cmd = PAC_DOWN;
				break;
			default:
				cmd = PAC_NONE;
		}
	}
	return cmd;
}

/* Changes the keyboard commands to ghost control commnads */
int Key2GhostCmd(int key, bool exchangePlayers){
	int cmd;
	if(exchangePlayers == false){
		/* player on the left is ghost */	
		switch(key){
			case FSKEY_A:
				cmd = GHOST_LEFT;
				break;
			case FSKEY_D:
				cmd = GHOST_RIGHT;
				break;
			case FSKEY_W:
				cmd = GHOST_UP;
				break;
			case FSKEY_S:
				cmd = GHOST_DOWN;
				break;
			case FSKEY_1:
				cmd = GHOST_SWITCH;
				break;
			default:
				cmd = GHOST_NONE;
				break;
		}

	}
	else{
		/* player on the right is ghost */
		switch(key){
			case FSKEY_LEFT:
				cmd = GHOST_LEFT;
				break;
			case FSKEY_RIGHT:
				cmd = GHOST_RIGHT;
				break;
			case FSKEY_UP:
				cmd = GHOST_UP;
				break;
			case FSKEY_DOWN:
				cmd = GHOST_DOWN;
				break;
			case FSKEY_M:
				cmd = GHOST_SWITCH;
				break;
			default:
				cmd = GHOST_NONE;
				break;
		}
	}
	return cmd;
}


int main(void){
	/* random seed */
	srand((int)time(NULL));
	
	/* game pages */
	Menu menu;
	Rule rule;
	Score score;
	PauseMenu pauseMenu;
	bool plot3d = true, visualize = true;
	Play play(visualize, plot3d);
	
	FsOpenWindow(0, 100, 1600, 600, 1);
	FsPollDevice();
	int key = FsInkey();
	int gameState = GAME_MENU;
	bool pause = false;
	int pauseState;
	bool rematch, finishGame, exchangePlayers;
	int menuLoop, ruleLoop;
	int score1, score2;
	score1 = 0;
	score2 = 0;

	/* Music player */
	YsSoundPlayer musicPlayer;
	YsSoundPlayer::SoundData scene;
	musicPlayer.MakeCurrent();
	musicPlayer.Start();
	FsChangeToProgramDir();
	if(YSOK != scene.LoadWav("music/scene.wav")){
		cout << "Error! Cannod load scene.wav" << endl;
	}
	musicPlayer.PlayBackground(scene);	
	
	int*** observation;
	observation = new int**[6];
	for(int i = 0;i < 6;i++){
		observation[i] = new int*[25];
		for(int j = 0;j < 25;j++){
			observation[i][j] = new int[25];
		}
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
				rematch = false;
				pause = false;
				finishGame = false;
				exchangePlayers = false;
				play.Reset(exchangePlayers, observation);
				score1 = 0;
				score2 = 0;
				/* Start game */
				while(key != FSKEY_ESC && gameState == GAME_PLAY){

					/* Get external device commands */
					FsPollDevice();
					key = FsInkey();
					if(key == FSKEY_SPACE) pause = !pause;	
					bool done = false;
					
					if(pause == false){
						if(play.CheckCountDown()){
							/* Send keyboard signals through env API */
							int pacCmd = Key2PacCmd(key, exchangePlayers);
							int ghostCmd = Key2GhostCmd(key, exchangePlayers);
							int pacReward, ghostReward;
							pacReward = 0;
							ghostReward = 0;
							play.Step(pacCmd, ghostCmd, observation, pacReward, ghostReward, done);
							
							if(exchangePlayers == false){
								score1 += pacReward;
								score2 += ghostReward;
							}
							else{
								score1 += ghostReward;
								score2 += pacReward;
							}
						}
					}
					else{
						play.PauseTime();	
					}
					/* Graphical display */	
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					play.Draw();

					/* Check end conditions */
					if(done == true){
						if(exchangePlayers == true){
							finishGame = true;
						}
						else{
							exchangePlayers = true;
							play.Reset(exchangePlayers, observation);
						}
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
					FsSleep(100);

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
				score.SetScore1(score1);
				score.SetScore2(score2);

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
	musicPlayer.End();
	return 0;
}

