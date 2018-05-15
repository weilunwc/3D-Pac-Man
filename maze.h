/* This file is the header file for the maze class, each surface of the maze
 * if another subclass, the fullmaze class contains six surfaces
 * This program also alows users to design their own maze by moving the pacman
 * to design the maze structure, and also enabeles prototype experimentation
 * of the transfer between different surfaces
 * Wei Lun William Chen 2017.11.19
 * */
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include <vector>
using namespace std;

static char inputMaze[] = {
	"1111111111111111111111111"
		"1000000000000000000000001"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"1000000000100010000000001"
		"1011011010111110101101101"
		"1000011010000000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"1000000000000000000000001"
		"1111111111111111111111111"

		"1110111111110111111110111"
		"0000000000000000000000000"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"0000000000100010000000000"
		"1011011010111110101101101"
		"1000011010000000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"0000000000000000000000000"
		"1110111111110111111110111"

		"1110111111110111111110111"
		"0000000000000000000000000"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"0000000000100010000000000"
		"1011011010111110101101101"
		"1000011010000000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"0000000000000000000000000"
		"1110111111110111111110111"

		"1110111111110111111110111"
		"0000000000000000000000000"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"0000000000100010000000000"
		"1011011010111110101101101"
		"1000011010001000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"0000000000000000000000000"
		"1110111111110111111110111"

		"1110111111110111111110111"
		"0000000000000000000000000"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"0000000000100010000000000"
		"1011011010111110101101101"
		"1000011010000000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"0000000000000000000000000"
		"1110111111110111111110111"

		"1111111111111111111111111"
		"1000000000000000000000001"
		"1011110111101011110111101"
		"1011110111101011110111101"
		"1000000000101010000000001"
		"1011111010000000101111101"
		"1000000010111110100000001"
		"1011111010001000101111101"
		"1000000011101011100000001"
		"1111111010000000101111111"
		"1000011010110110101100001"
		"1011011010100010101101101"
		"1000000000100010000000001"
		"1011011010111110101101101"
		"1000011010000000101100001"
		"1111111010111110101111111"
		"1000000000000000000000001"
		"1011101011101011101011101"
		"1011101000000000001011101"
		"1000001011111111101000001"
		"1111101000011100001011111"
		"1000000011011101100000001"
		"1011111111011101111111101"
		"1000000000000000000000001"
		"1111111111111111111111111"
};

/* Global variables shared by the whole program */
extern int blockSize_2D;
extern const int blockNumber;  // the size of the surface array
extern double myPi;
extern const int ghostNumber;


/* the pacman x,y coordinates*/
typedef struct CoordStruct{
	int x;
	int y;
}Coord;

typedef struct GhostStruct{
	int x;
	int y;
	int prevX,prevY;
	int surface;
	int xdir,ydir;
	int dirIndex;
	int mode;
}Ghost;

typedef struct PacmManStruct{
	int x;
	int y;
	int prevX,prevY;
	int surface;
	int xdir,ydir;
	bool powerState;
}PacMan;


/* the rgb information */
typedef struct ColorStruct{
	int r;
	int g;
	int b;
}Color;


/* A maze on a single surface, uses an array to represent
 * each block
 */
class Maze{
	protected:
		int **maze;
		int pacState; // 0 not in this surface, 1 not clear box, 2 clear box
		Coord pacman;
		Coord cherry;
		vector<bool> ghostState;
		Coord origin; // the (0,0) point on the global coordinates
		char orientation;
		Color baseColor; // R,G,B

	public:
		Maze();
		~Maze();
		void SetMaze(int,int,int); // set the maze array
		void SetCherry();
		void SetPowerPells();
		void SetOrientation(char); // set the maze's relative position to other surfaces
		void Draw();
		void DrawGhost(int,int);
		void Print();
		bool EatPerl(int,int);
		bool EatCherry(int,int);
		bool EatPowerPell(int,int);
		void Activate(PacMan,int);// changes pacman coordinates and state
		void Deactivate(); // turns down the pacman drawing
		const int ReturnElement(int,int)const; // return the element of a coordinate
		int ReturnPerls();
};

Maze::Maze(){
	maze = new int*[blockNumber];
	for(int i = 0;i < blockNumber;i++){
		maze[i] = new int [blockNumber];
	}
	pacState = 0;
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			maze[i][j] = 1;
		}
	}
	cherry.x = 0;
	cherry.y = 0;
}

Maze::~Maze(){
	for(int i = 0;i < blockNumber;i++){
		delete [] maze[i];
	}
	delete [] maze;
}
void Maze::SetCherry(){
	int x = rand()%blockNumber;
	int y = rand()%blockNumber;
	while(maze[x][y] == 1){
		x = rand()%blockNumber;
		y = rand()%blockNumber;
	}
	cherry.x = x;
	cherry.y = y;
	maze[x][y] = 2;
}

void Maze::SetPowerPells(){
	int x = rand()%blockNumber;
	int y = rand()%blockNumber;
	while(maze[x][y] == 1){
		x = rand()%blockNumber;
		y = rand()%blockNumber;
	}
	maze[x][y] = 3;
}

bool Maze::EatPerl(int i,int j){

	if(maze[i][j] == 0){
		maze[i][j] = -1;
		return true;
	}
	return false;
}
bool Maze::EatCherry(int i,int j){

	if(maze[i][j] == 2){
		maze[i][j] = -1;
		return true;
	}
	return false;
}


bool Maze::EatPowerPell(int i,int j){

	if(maze[i][j] == 3){
		maze[i][j] = -1;
		return true;
	}
	return false;
}


int Maze::ReturnPerls(){
	int perls = 0;
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			if(maze[i][j] == -1){
				perls++;
			}
		}
	}
	return perls;
}

void Maze::SetMaze(int i,int j,int input){
	maze[i][j] = input;
}

void Maze::SetOrientation(char orient){
	orientation = orient;
	switch(orient){
		case 'T':
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = 0;
			break;
		case 'B':
			baseColor.r = 0;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = 2*blockNumber*blockSize_2D;
			break;
		case 'N':
			baseColor.r = 0;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = 0;
			origin.y = blockNumber*blockSize_2D;
			break;
		case 'W':
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = blockNumber*blockSize_2D;
			origin.y = blockNumber*blockSize_2D;
			break;
		case 'S':
			baseColor.r = 200;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = blockNumber*blockSize_2D;
			break;
		case 'E':
			baseColor.r = 0;
			baseColor.g = 200;
			baseColor.b = 200;
			origin.x = 3*blockNumber*blockSize_2D;
			origin.y = blockNumber*blockSize_2D;
			break;

	}
}


const int Maze::ReturnElement(int i,int j)const{
	return maze[i][j];
}

void Maze::Print(){
	//printf("Orientation = %c\n",orientation);
	for(int i = 0;i < blockNumber;i++){
		printf("%c",34);
		for(int j = 0;j < blockNumber;j++){
			printf("%d",maze[j][i]);
		}
		printf("%c\n",34);
	}
	printf("\n");
}

void Maze::Activate(PacMan cur,int state){
	pacman.x = cur.x;
	pacman.y = cur.y;
	pacState = state;
}

void Maze::Deactivate(){
	pacState = 0;
}
void Maze::DrawGhost(int x,int y){
	glColor3ub(0,0,0);
	glBegin(GL_QUADS);
	x *= blockSize_2D;
	y *= blockSize_2D;
	glVertex2i(origin.x + x            ,origin.y + y            );
	glVertex2i(origin.x + x + blockSize_2D,origin.y + y            );
	glVertex2i(origin.x + x + blockSize_2D,origin.y + y + blockSize_2D);
	glVertex2i(origin.x + x            ,origin.y + y + blockSize_2D);
	glEnd();
}


void Maze::Draw(){
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			int x = blockSize_2D*i;
			int y = blockSize_2D*j;
			if(maze[i][j] == 1){
				glColor3ub(baseColor.r,baseColor.g,baseColor.b);
			}
			else{
				glColor3ub(255,255,255);
			}
			glBegin(GL_QUADS);
			glVertex2i(origin.x + x            ,origin.y + y            );
			glVertex2i(origin.x + x + blockSize_2D,origin.y + y            );
			glVertex2i(origin.x + x + blockSize_2D,origin.y + y + blockSize_2D);
			glVertex2i(origin.x + x            ,origin.y + y + blockSize_2D);
			glEnd();

			if(maze[i][j] == 0){
				// draw the perls
				double centerx = origin.x + x + blockSize_2D/2;
				double centery = origin.y + y + blockSize_2D/2;
				double r = blockSize_2D/2.0 - 1.0;
				glColor3ub(100,100,0);
				glBegin(GL_POLYGON);
				for(int k = 0;k < 64;k++){
					double angle = (double)k*myPi/32.0;
					double cx = centerx + r*cos(angle);
					double cy = centery + r*sin(angle);
					glVertex2d(cx,cy);
				}
				glEnd();
			}
			if(maze[i][j] == 2){
				// draw the cherry
				double centerx = origin.x + x + blockSize_2D/2;
				double centery = origin.y + y + blockSize_2D/2;
				double r = blockSize_2D/2.0 - 1.0;
				glColor3ub(200,0,0);
				glBegin(GL_POLYGON);
				for(int k = 0;k < 64;k++){
					double angle = (double)k*myPi/32.0;
					double cx = centerx + r*cos(angle);
					double cy = centery + r*sin(angle);
					glVertex2d(cx,cy);
				}
				glEnd();
			}
			if(maze[i][j] == 3){
				// draw the power pells
				double centerx = origin.x + x + blockSize_2D/2;
				double centery = origin.y + y + blockSize_2D/2;
				double r = blockSize_2D/2.0 - 1.0;
				glColor3ub(0,0,200);
				glBegin(GL_POLYGON);
				for(int k = 0;k < 64;k++){
					double angle = (double)k*myPi/32.0;
					double cx = centerx + r*cos(angle);
					double cy = centery + r*sin(angle);
					glVertex2d(cx,cy);
				}
				glEnd();
			}
		}
	}

	/* Draw pacman */
	if(pacState > 0){
		double x = (double)(origin.x + blockSize_2D*pacman.x + blockSize_2D/2);
		double y = (double)(origin.y + blockSize_2D*pacman.y + blockSize_2D/2);
		double r = blockSize_2D/2;
		glColor3ub(0,0,100);
		glBegin(GL_POLYGON);
		for(int i = 0;i < 64;i++){
			double angle = (double)i*myPi/32.0;
			double cx = x + r*cos(angle);
			double cy = y + r*sin(angle);
			glVertex2d(cx,cy);
		}
		glEnd();
	}
	/*Draw the frame */
	glColor3ub(1,1,1);
	glBegin(GL_LINES);
	glVertex2i(origin.x,origin.y);
	glVertex2i(origin.x + blockNumber*blockSize_2D,origin.y);

	glVertex2i(origin.x + blockNumber*blockSize_2D,origin.y);
	glVertex2i(origin.x + blockNumber*blockSize_2D,origin.y + blockNumber*blockSize_2D);

	glVertex2i(origin.x + blockNumber*blockSize_2D,origin.y + blockNumber*blockSize_2D);
	glVertex2i(origin.x,origin.y + blockNumber*blockSize_2D);

	glVertex2i(origin.x,origin.y + blockNumber*blockSize_2D);
	glVertex2i(origin.x,origin.y);
	glEnd();
}





class FullMaze{
	private:
		Maze maze[6]; // 0-T,1-N,2-W,3-S,4-E,5-B

		vector<Ghost> ghost;
		int ghostControl;
		int ghostLives;

		//char pacSurface;
		int curState; // 1 for not clear, 2 for clear box
		//int xdir,ydir;
	public:
		PacMan pacman;
		int ghost_eaten;
		int perls;
		int cherries;
		FullMaze(){};
		void Draw();
		void Print();
		void PacMove();
		void GhostMove(int);
		void Restart();
		void Restore();
		void RandomDirection(int);
		void ChangeDirection(int);
		void ChangeGhostDirection(int);
		int ReturnGhostControl();
		bool CollisionDetect();
		void SetMaze();
		void SetCherry();
		void SetPowerPells();
		//void EatPerl(int,int,int);
		const void ReturnMaze(int***)const;
		void ReturnPacman(PacMan*);
		void ReturnGhost(vector<Ghost>*);
		int ReturnPerls();
		void ChangeIndexToDir(int);
		void SwitchGhost(int);
		int surfaceToNum(char);
		char NumToSurface(int);
		void GhostChase(int,int,int);
};


void FullMaze::Restart(){
	SetMaze();
	maze[0].SetOrientation('T');
	maze[1].SetOrientation('N');
	maze[2].SetOrientation('W');
	maze[3].SetOrientation('S');
	maze[4].SetOrientation('E');
	maze[5].SetOrientation('B');
	//pacSurface = 'S';
	ghost_eaten = 0;
	cherries = 0;
	pacman.surface = 3;
	curState = 1;
	pacman.x = 8;
	pacman.y = 12;
	pacman.prevX = 8;
	pacman.prevY = 12;
	pacman.powerState = false;
	perls = 0;
	pacman.xdir = 0;
	pacman.ydir = 0;
	maze[3].Activate(pacman,curState);
	ghostLives = ghostNumber;
	ghost.resize(ghostLives);
	int j = 0;
	int k = 0;
	int s = 1;
	ghostControl = 5;
	for(int i = 0;i < ghostLives;i++){
		if(i != ghostControl){
			RandomDirection(i);
		}
		else{
			ghost[i].xdir = 0;
			ghost[i].ydir = 0;
		}
		ghost[i].surface = s;
		ghost[i].x = k+11;
		ghost[i].y = 11;
		ghost[i].prevX = k+11;
		ghost[i].prevY = 11;
		k++;
		j++;
		if(j >= 2){
			s++;
			k = 0;
			j = 0;
		}
	}
}


void FullMaze::ChangeIndexToDir(int i) {
	switch (ghost[i].dirIndex) {
		case 0:
			ghost[i].xdir = 1;
			ghost[i].ydir = 0;
			break;
		case 1:
			ghost[i].xdir = 0;
			ghost[i].ydir = -1;
			break;
		case 2:
			ghost[i].xdir = -1;
			ghost[i].ydir = 0;
			break;
		case 3:
			ghost[i].xdir = 0;
			ghost[i].ydir = 1;
			break;
	}
}


int FullMaze::ReturnPerls(){
	int perls = 0;
	for(int i = 0;i < 6;i++){
		perls += maze[i].ReturnPerls();
	}
	return perls;
}

void FullMaze::GhostChase(int index, int x, int y) {
	int distx = abs(x - ghost[index].x);
	int disty = abs(y - ghost[index].y);
	int prevx = ghost[index].x;
	int prevy = ghost[index].y;

	if (distx < disty) {
		if (x > prevx) {
			ghost[index].dirIndex = 0;
		}
		else { ghost[index].dirIndex = 2; }
	}
	else {
		if (y > prevy) {
			ghost[index].dirIndex = 3;
		}
		else { ghost[index].dirIndex = 1; }
	}
}
void FullMaze::SetCherry(){
	for(int i = 0;i < 6;i++){
		maze[i].SetCherry();
	}
}

void FullMaze::SetPowerPells(){
	for(int i = 0;i < 6;i++){
		maze[i].SetPowerPells();
	}
}


int FullMaze::ReturnGhostControl(){
	return ghostControl;
}

void FullMaze::Restore(){
	/*
	   maze[0].SetOrientation('T');
	   maze[1].SetOrientation('N');
	   maze[2].SetOrientation('W');
	   maze[3].SetOrientation('S');
	   maze[4].SetOrientation('E');
	   maze[5].SetOrientation('B');
	   */
	//pacSurface = 'S';
	pacman.surface = 3;
	curState = 1;
	pacman.x = 8;
	pacman.y = 12;
	pacman.xdir = 0;
	pacman.ydir = 0;
	for(int i = 0;i < 6;i++){
		maze[i].Deactivate();
	}
	maze[3].Activate(pacman,curState);
	ghost.resize(ghostLives);
	int j = 0;
	int k = 0;
	int s = 1;
	ghostControl = ghostLives%6;
	for(int i = 0;i < ghostLives;i++){
		if(i != ghostControl){
			RandomDirection(i);
		}
		else{
			ghost[i].xdir = 0;
			ghost[i].ydir = 0;
		}
		ghost[i].surface = s;
		ghost[i].x = k+11;
		ghost[i].y = j+11;
		ghost[i].prevX = k+11;
		ghost[i].prevY = j+11;
		k++;
		j++;
		if(k >= 2){
			s++;
			k = 0;
			j = 0;

		}
	}
}
int FullMaze::surfaceToNum(char sur){
	switch(sur){
		case 'T':
			return 0;
		case 'N':
			return 1;
		case 'W':
			return 2;
		case 'S':
			return 3;
		case 'E':
			return 4;
		case 'B':
			return 5;
		default:
			return 3;
	}
}

char FullMaze::NumToSurface(int num){
	switch(num){
		case 0:
			return 'T';
		case 1:
			return 'N';
		case 2:
			return 'W';
		case 3:
			return 'S';
		case 4:
			return 'E';
		case 5:
			return 'B';
		default:
			return 'S';
	}
}

bool FullMaze::CollisionDetect(){
	int n = ghost.size();
	bool detect = false;
	for(int i = 0;i < n;i++){
		if(pacman.surface == ghost[i].surface && pacman.x == ghost[i].x && pacman.y == ghost[i].y){
			if(pacman.powerState == false){
				Restore();
				return true;
			}
			else{
				detect = true;
				// Eat the ghost
				if(n > 1){
					ghost.erase(ghost.begin() + i);
					ghostLives--;
					ghostControl = rand()%ghostLives;
					ghost_eaten++;
				}
				else{
					int i = 0;
					ghost[i].xdir = 0;
					ghost[i].ydir = 0;
					ghost[i].surface = 1+rand()%4;
					ghost[i].x = 11;
					ghost[i].y = 11;
					ghost[i].prevX = 11;
					ghost[i].prevY = 11;
				}
			}

		}
		else if(pacman.surface == ghost[i].surface && pacman.prevX == ghost[i].x && pacman.prevY == ghost[i].y
				&& pacman.x == ghost[i].prevX && pacman.y == ghost[i].prevY){

			if(pacman.powerState == false){
				Restore();
				return true;
			}
			else{
				detect = true;
				// Eat the ghost
				if(n > 1){
					ghost.erase(ghost.begin() + i);
					ghostLives--;
					ghostControl = rand()%ghostLives;
				}
				else{
					int i = 0;
					ghost[i].xdir = 0;
					ghost[i].ydir = 0;
					ghost[i].surface = 1+rand()%4;
					ghost[i].x = 11;
					ghost[i].y = 11;
					ghost[i].prevX = 11;
					ghost[i].prevY = 11;
				}
			}
		}
	}
	/*
	   if(n == 1 && detect){
	   ghost.resize(1);
	   ghostLives = 1;
	   int i = 0;
	   ghost[i].xdir = 0;
	   ghost[i].ydir = 0;
	   ghost[i].surface = 3;
	   ghost[i].x = 11;
	   ghost[i].y = 11;
	   ghost[i].prevX = 11;
	   ghost[i].prevY = 11;
	   Ghost lastGhost;
	   lastGhost.xdir = 0;
	   lastGhost.ydir = 0;
	   lastGhost.surface = 3;
	   lastGhost.x = 11;
	   lastGhost.y = 11;
	   lastGhost.prevX = 11;
	   lastGhost.prevY = 11;
	   ghost.push_back(lastGhost);
	   ghostControl = 0;
	   ghostLives++;
	   }
	   */
	return false;
}


void FullMaze::SwitchGhost(int index){
	//ghostControl = index % ghostLives;
	vector<int> tmp;
	int n = ghost.size();
	for (int i = 0;i < n;i++) {
		if (ghost[i].surface == pacman.surface){
			tmp.push_back(i);
		}
	}
	n = tmp.size();
	if(n != 0){
		ghostControl = tmp[rand() % n];
	}
	else{
		ghostControl = rand() % ghost.size();
	}
}

void FullMaze::Draw(){
	for(int i = 0;i < 6;i++){
		maze[i].Draw();
	}
	int n = ghost.size();
	int surface;
	int x,y;
	for(int i = 0;i < n;i++){
		surface = ghost[i].surface;
		x = ghost[i].x;
		y = ghost[i].y;
		maze[surface].DrawGhost(x,y);
	}
}

void FullMaze::ReturnGhost(vector<Ghost> *ghostInfo){
	int n = ghost.size();
	ghostInfo->clear();
	for(int i = 0;i < n;i++){
		ghostInfo->push_back(ghost[i]);
	}
}

void FullMaze::ReturnPacman(PacMan* pacInfo){
	/*
	   switch(pacman.surface){
	   case 'T':
	   curInfo[0] = 0;
	   break;
	   case 'N':
	   curInfo[0] = 1;
	   break;
	   case 'W':
	   curInfo[0] = 2;
	   break;
	   case 'S':
	   curInfo[0] = 3;
	   break;
	   case 'E':
	   curInfo[0] = 4;
	   break;
	   case 'B':
	   curInfo[0] = 5;
	   break;
	   }
	   */
	/*
	   curInfo[0] = pacman.surface;
	   curInfo[1] = pacman.x;
	   curInfo[2] = pacman.y;
	   curInfo[3] = pacman.xdir;
	   curInfo[4] = pacman.ydir;
	   */
	pacInfo->x = pacman.x;
	pacInfo->y = pacman.y;
	pacInfo->xdir = pacman.xdir;
	pacInfo->ydir = pacman.ydir;
	pacInfo->surface = pacman.surface;
	pacInfo->powerState = pacman.powerState;
}


void FullMaze::RandomDirection(int index){
	index = index%ghostLives;
	ghost[index].dirIndex = rand()%4;
	switch(ghost[index].dirIndex){
		case 0:
			ghost[index].xdir = 1;
			ghost[index].ydir = 0;
			break;
		case 1:
			ghost[index].xdir = 0;
			ghost[index].ydir = 1;
			break;
		case 2:
			ghost[index].xdir = -1;
			ghost[index].ydir = 0;
			break;
		case 3:
			ghost[index].xdir = 0;
			ghost[index].ydir = -1;
			break;
	}
}


void FullMaze::SetMaze(){
	for(int i = 0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			for(int k = 0;k < blockNumber;k++){
				maze[i].SetMaze(k, j, inputMaze[625*i + 25*j+k] - '0');
			}
		}
	}


	/*
	   fstream input;
	   string buffer;
	   input.open(mazeFIle,ios::in);
	   for(int i = 0;i < 6;i++){
	   for(int j = 0;j < blockNumber;j++){
	   input >> buffer;
	   for(int k = 0;k < blockNumber;k++){
	   maze[i].SetMaze(j,k,buffer[k] - '0');
	   }
	   cout << buffer << endl;
	   }
	   cout << endl;
	   }
	   input.close();
	   */
}


void FullMaze::Print(){
	for(int i = 0;i < 6;i++){
		maze[i].Print();
	}
}

const void FullMaze::ReturnMaze(int *** output)const{
	for(int k = 0;k < 6;k++){
		for(int i = 0;i < blockNumber;i++){
			for(int j = 0;j < blockNumber;j++){
				output[k][j][i] = maze[k].ReturnElement(j,i);
			}
		}
	}
}

/*
   void FullMaze::EatPerl(int i,int j,int k){
   maze[i].EatPerl(j,k);
   }
   */
void FullMaze::ChangeDirection(int dir){
	switch(dir){
		case 1:
			pacman.xdir = -1;
			pacman.ydir = 0;
			break;
		case 2:
			pacman.ydir = -1;
			pacman.xdir = 0;
			break;
		case 3:
			pacman.xdir = 1;
			pacman.ydir = 0;
			break;
		case 4:
			pacman.xdir = 0;
			pacman.ydir = 1;
			break;
		default:
			// do nothing if unknown command */
			break;
	}
}

void FullMaze::ChangeGhostDirection(int dir){
	switch(dir){
		case 1:
			ghost[ghostControl].xdir = -1;
			ghost[ghostControl].ydir = 0;
			break;
		case 2:
			ghost[ghostControl].ydir = -1;
			ghost[ghostControl].xdir = 0;
			break;
		case 3:
			ghost[ghostControl].xdir = 1;
			ghost[ghostControl].ydir = 0;
			break;
		case 4:
			ghost[ghostControl].xdir = 0;
			ghost[ghostControl].ydir = 1;
			break;
		default:
			/* do nothing if unknown command */
			break;
	}
}
/*
   void FullMaze::GhostMove(){

   int prevX,prevY,prevSurface;
   int n = ghost.size();
   for(int i = 0;i < n;i++){
   prevSurface = ghost[i].surface;
   prevX = ghost[i].x;
   prevY = ghost[i].y;
   if(ghost[i].xdir < 0){
   ghost[i].x--;
   if(ghost[i].x < 0){
   switch(ghost[i].surface){
   case 0:
   ghost[i].surface = 2;
   ghost[i].x = ghost[i].y;
   ghost[i].y = 0;
   ghost[i].xdir = 0;
   ghost[i].ydir = 1;
   break;
   case 1:
   ghost[i].surface = 4;
   ghost[i].x = blockNumber-1;
   break;
   case 2:
   ghost[i].surface = 1;
   ghost[i].x = blockNumber-1;
   break;
   case 3:
   ghost[i].surface = 2;
   ghost[i].x = blockNumber-1;
   break;
   case 4:
   ghost[i].surface = 3;
   ghost[i].x = blockNumber-1;
   break;
   case 5:
   ghost[i].surface = 2;
   ghost[i].x = blockNumber-1 - ghost[i].y;
   ghost[i].y = blockNumber-1;
   ghost[i].xdir = 0;
   ghost[i].ydir = -1;
   break;
   }
   }
   }
   else if(ghost[i].ydir < 0){
   ghost[i].y--;
   if(ghost[i].y < 0){
   switch(ghost[i].surface){
   case 0:
   ghost[i].surface = 1;
   ghost[i].x = blockNumber-1 - ghost[i].x;
   ghost[i].y = 0;
   ghost[i].ydir = 1;
   break;
   case 1:
   ghost[i].surface = 0;
   ghost[i].x = blockNumber-1 - ghost[i].x;
   ghost[i].y = 0;
   ghost[i].ydir = 1;
   break;
   case 2:
   ghost[i].surface = 0;
   ghost[i].y = ghost[i].x;
   ghost[i].x = 0;
   ghost[i].ydir = 0;
   ghost[i].xdir = 1;
   break;
   case 3:
   ghost[i].surface = 0;
ghost[i].y = blockNumber-1;
break;
case 4:
ghost[i].surface = 0;
ghost[i].y= blockNumber-1 - ghost[i].x;
ghost[i].x = blockNumber-1;
ghost[i].xdir = -1;
ghost[i].ydir = 0;
break;
case 5:
ghost[i].surface = 3;
ghost[i].y = blockNumber-1;
break;
}
}
}
else if(ghost[i].xdir > 0){
	ghost[i].x++;
	if(ghost[i].x >= blockNumber){
		switch(ghost[i].surface){
			case 0:
				ghost[i].surface = 4;
				ghost[i].x = blockNumber-1 - ghost[i].y;
				ghost[i].y = 0;
				ghost[i].xdir = 0;
				ghost[i].ydir = 1;
				break;
			case 1:
				ghost[i].surface = 2;
				ghost[i].x = 0;
				break;
			case 2:
				ghost[i].surface = 3;
				ghost[i].x = 0;
				break;
			case 3:
				ghost[i].surface = 4;
				ghost[i].x = 0;
				break;
			case 4:
				ghost[i].surface = 1;
				ghost[i].x = 0;
				break;
			case 5:
				ghost[i].surface = 4;
				ghost[i].x = ghost[i].y;
				ghost[i].y = blockNumber-1;
				ghost[i].xdir = 0;
				ghost[i].ydir = -1;
				break;
		}
	}
}
else if(ghost[i].ydir > 0){
	ghost[i].y++;
	if(ghost[i].y >= blockNumber){
		switch(ghost[i].surface){
			case 0:
				ghost[i].surface = 3;
				ghost[i].y = 0;
				break;
			case 1:
				ghost[i].surface = 5;
				ghost[i].x = blockNumber-1-ghost[i].x;
				ghost[i].y = blockNumber-1;
				ghost[i].ydir = -1;
				break;
			case 2:
				ghost[i].surface = 5;
				ghost[i].y = blockNumber-1-ghost[i].x;
				ghost[i].x = 0;
				ghost[i].xdir = 1;
				ghost[i].ydir=  0;
				break;
			case 3:
				ghost[i].surface = 5;
				ghost[i].y = 0;
				break;
			case 4:
				ghost[i].surface = 5;
				ghost[i].y = ghost[i].x;
				ghost[i].x = blockNumber-1;
				ghost[i].ydir = 0;
				ghost[i].xdir = -1;
				break;
			case 5:
				ghost[i].surface = 1;
				ghost[i].x = blockNumber-1 - ghost[i].x;
				ghost[i].y = blockNumber-1;
				ghost[i].ydir = -1;
				break;
		}
	}
}
int x = ghost[i].x;
int y = ghost[i].y;
int surface = ghost[i].surface;
if(maze[surface].ReturnElement(x,y) == 1){
	ghost[i].x = prevX;
	ghost[i].y = prevY;
	ghost[i].surface = prevSurface;
	if(i != ghostControl){
		RandomDirection(i);
	}
}
}
}
*/

void FullMaze::GhostMove(int loopCount) {
	int n = ghost.size();
	int prevX, prevY, prevSurface;
	for (int i = 0;i < n;i++) {
		prevSurface = ghost[i].surface;
		ghost[i].prevX = ghost[i].x;
		ghost[i].prevY = ghost[i].y;
		prevX = ghost[i].x;
		prevY = ghost[i].y;
		if (i != ghostControl){
			if((loopCount*3) % 4== 0){
				continue;
			}
			switch (ghost[i].dirIndex)
			{
				case 0: //right
					if (maze[prevSurface].ReturnElement(prevX, prevY - 1) != 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 1, 3 };
							ghost[i].dirIndex = tmp[rand() % 3];
						}
						else { if (pacman.y < ghost[i].y) { ghost[i].dirIndex = 1; }
							else if (pacman.y > ghost[i].y) { ghost[i].dirIndex = 3; }
							else { ghost[i].dirIndex = 0; }
						}

					}
					else if (maze[prevSurface].ReturnElement(prevX, prevY - 1) != 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) == 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 1 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.y < ghost[i].y) { ghost[i].dirIndex = 1; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX, prevY - 1) == 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 3 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else { if (pacman.y > ghost[i].y) { ghost[i].dirIndex = 3; } }
					}
					break;
				case 1: //up
					if (maze[prevSurface].ReturnElement(prevX + 1, prevY) != 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 1, 2 };
							ghost[i].dirIndex = tmp[rand() % 3];
						}
						else {
							if (pacman.x > ghost[i].x) { ghost[i].dirIndex = 0; }
							else if (pacman.x < ghost[i].x) { ghost[i].dirIndex = 2; }
							else { ghost[i].dirIndex = 1; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX + 1, prevY) != 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) == 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 1 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.x > ghost[i].x) { ghost[i].dirIndex = 0; }
							else { ghost[i].dirIndex = 1; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX + 1, prevY) == 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) != 1)
					{
						if (ghost[i].mode==1) {
							int tmp[] = { 1, 2 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.x < ghost[i].x) { ghost[i].dirIndex = 2; }
							else { ghost[i].dirIndex = 1; }
						}
					}
					break;
				case 2: //left
					if (maze[prevSurface].ReturnElement(prevX, prevY - 1) != 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 1, 2, 3 };
							ghost[i].dirIndex = tmp[rand() % 3];
						}
						else {
							if (pacman.y < ghost[i].y) { ghost[i].dirIndex = 1; }
							else if (pacman.y > ghost[i].y) { ghost[i].dirIndex = 3; }
							else { ghost[i].dirIndex = 2; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX, prevY - 1) != 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) == 1)
					{
						if (ghost[i].mode==1) {
							int tmp[] = { 1, 2 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else { if (pacman.y < ghost[i].y) { ghost[i].dirIndex = 1; }
							else { ghost[i].dirIndex = 2; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX, prevY - 1) == 1 && maze[prevSurface].ReturnElement(prevX, prevY + 1) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 2, 3 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.y > ghost[i].y) { ghost[i].dirIndex = 3; }
							else { ghost[i].dirIndex = 2; }
						}
					}
					break;
				case 3: //down
					if (maze[prevSurface].ReturnElement(prevX + 1, prevY) != 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 2, 3 };
							ghost[i].dirIndex = tmp[rand() % 3];
						}
						else {
							if (pacman.x > ghost[i].x) { ghost[i].dirIndex = 0; }
							else if (pacman.x < ghost[i].x) { ghost[i].dirIndex = 2; }
							else { ghost[i].dirIndex = 3; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX + 1, prevY) != 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) == 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 0, 3 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.x > ghost[i].x) { ghost[i].dirIndex = 0; }
							else { ghost[i].dirIndex = 3; }
						}
					}
					else if (maze[prevSurface].ReturnElement(prevX + 1, prevY) == 1 && maze[prevSurface].ReturnElement(prevX - 1, prevY) != 1)
					{
						if (ghost[i].mode == 1) {
							int tmp[] = { 3, 2 };
							ghost[i].dirIndex = tmp[rand() % 2];
						}
						else {
							if (pacman.x < ghost[i].x) { ghost[i].dirIndex = 2; }
							else { ghost[i].dirIndex = 3; }
						}
					}
					break;
			}
			ChangeIndexToDir(i);
		}


		if (ghost[i].xdir < 0) {
			ghost[i].x--;
			if (ghost[i].x < 0) {
				switch (ghost[i].surface) {
					case 0:
						ghost[i].surface = 2;
						ghost[i].x = ghost[i].y;
						ghost[i].y = 0;
						ghost[i].xdir = 0;
						ghost[i].ydir = 1;
						ghost[i].dirIndex = 3;
						break;
					case 1:
						ghost[i].surface = 4;
						ghost[i].x = blockNumber - 1;
						break;
					case 2:
						ghost[i].surface = 1;
						ghost[i].x = blockNumber - 1;
						break;
					case 3:
						ghost[i].surface = 2;
						ghost[i].x = blockNumber - 1;
						break;
					case 4:
						ghost[i].surface = 3;
						ghost[i].x = blockNumber - 1;
						break;
					case 5:
						ghost[i].surface = 2;
						ghost[i].x = blockNumber - 1 - ghost[i].y;
						ghost[i].y = blockNumber - 1;
						ghost[i].xdir = 0;
						ghost[i].ydir = -1;
						ghost[i].dirIndex = 1;
						break;
				}
			}
		}
		else if (ghost[i].ydir < 0) {
			ghost[i].y--;
			if (ghost[i].y < 0) {
				switch (ghost[i].surface) {
					case 0:
						ghost[i].surface = 1;
						ghost[i].x = blockNumber - 1 - ghost[i].x;
						ghost[i].y = 0;
						ghost[i].ydir = 1;
						ghost[i].dirIndex = 3;
						break;
					case 1:
						ghost[i].surface = 0;
						ghost[i].x = blockNumber - 1 - ghost[i].x;
						ghost[i].y = 0;
						ghost[i].ydir = 1;
						ghost[i].dirIndex = 3;
						break;
					case 2:
						ghost[i].surface = 0;
						ghost[i].y = ghost[i].x;
						ghost[i].x = 0;
						ghost[i].ydir = 0;
						ghost[i].xdir = 1;
						ghost[i].dirIndex = 0;
						break;
					case 3:
						ghost[i].surface = 0;
						ghost[i].y = blockNumber - 1;
						break;
					case 4:
						ghost[i].surface = 0;
						ghost[i].y = blockNumber - 1 - ghost[i].x;
						ghost[i].x = blockNumber - 1;
						ghost[i].xdir = -1;
						ghost[i].ydir = 0;
						ghost[i].dirIndex = 2;
						break;
					case 5:
						ghost[i].surface = 3;
						ghost[i].y = blockNumber - 1;
						break;
				}
			}
		}
		else if (ghost[i].xdir > 0) {
			ghost[i].x++;
			if (ghost[i].x >= blockNumber) {
				switch (ghost[i].surface) {
					case 0:
						ghost[i].surface = 4;
						ghost[i].x = blockNumber - 1 - ghost[i].y;
						ghost[i].y = 0;
						ghost[i].xdir = 0;
						ghost[i].ydir = 1;
						ghost[i].dirIndex = 3;
						break;
					case 1:
						ghost[i].surface = 2;
						ghost[i].x = 0;
						break;
					case 2:
						ghost[i].surface = 3;
						ghost[i].x = 0;
						break;
					case 3:
						ghost[i].surface = 4;
						ghost[i].x = 0;
						break;
					case 4:
						ghost[i].surface = 1;
						ghost[i].x = 0;
						break;
					case 5:
						ghost[i].surface = 4;
						ghost[i].x = ghost[i].y;
						ghost[i].y = blockNumber - 1;
						ghost[i].xdir = 0;
						ghost[i].ydir = -1;
						ghost[i].dirIndex = 1;
						break;
				}
			}
		}
		else if (ghost[i].ydir > 0) {
			ghost[i].y++;
			if (ghost[i].y >= blockNumber) {
				switch (ghost[i].surface) {
					case 0:
						ghost[i].surface = 3;
						ghost[i].y = 0;
						break;
					case 1:
						ghost[i].surface = 5;
						ghost[i].x = blockNumber - 1 - ghost[i].x;
						ghost[i].y = blockNumber - 1;
						ghost[i].ydir = -1;
						ghost[i].dirIndex = 1;
						break;
					case 2:
						ghost[i].surface = 5;
						ghost[i].y = blockNumber - 1 - ghost[i].x;
						ghost[i].x = 0;
						ghost[i].xdir = 1;
						ghost[i].ydir = 0;
						ghost[i].dirIndex = 0;
						break;
					case 3:
						ghost[i].surface = 5;
						ghost[i].y = 0;
						break;
					case 4:
						ghost[i].surface = 5;
						ghost[i].y = ghost[i].x;
						ghost[i].x = blockNumber - 1;
						ghost[i].ydir = 0;
						ghost[i].xdir = -1;
						ghost[i].dirIndex = 2;
						break;
					case 5:
						ghost[i].surface = 1;
						ghost[i].x = blockNumber - 1 - ghost[i].x;
						ghost[i].y = blockNumber - 1;
						ghost[i].ydir = -1;
						ghost[i].dirIndex = 1;
						break;
				}
			}
		}
		int x = ghost[i].x;
		int y = ghost[i].y;
		int surface = ghost[i].surface;
		if (maze[surface].ReturnElement(x, y) == 1) {
			ghost[i].x = prevX;
			ghost[i].y = prevY;
			ghost[i].surface = prevSurface;
			if (ghost[i].surface == pacman.surface)
			{ ghost[i].mode = 2; }
			else { ghost[i].mode = 1; }
			if (ghost[i].x >= 11 && ghost[i].x <= 13 && ghost[i].y >= 10 && ghost[i].y <= 12) { ghost[i].mode = 1; }
			if (i != ghostControl) {
				switch (ghost[i].mode)
				{
					case 1:
						RandomDirection(i);
						break;
					case 2 :
						if(pacman.powerState != true){
							GhostChase(i, pacman.x, pacman.y);
						}
						else{
							RandomDirection(i);
						}
						break;
				}

			}
		}
	}
}

void FullMaze::PacMove(){
	int prevX,prevY,prevSurface;
	prevX = pacman.x;
	prevY = pacman.y;
	pacman.prevX = pacman.x;
	pacman.prevY = pacman.y;
	prevSurface = pacman.surface;
	if(pacman.xdir < 0){
		pacman.x--;
		if(pacman.x < 0){
			switch(NumToSurface(pacman.surface)){
				case 'T':
					maze[0].Deactivate();
					pacman.surface = surfaceToNum('W');
					pacman.x = pacman.y;
					pacman.y = 0;
					pacman.xdir = 0;
					pacman.ydir = 1;
					break;
				case 'N':
					maze[1].Deactivate();
					pacman.surface = surfaceToNum('E');
					pacman.x = blockNumber-1;
					break;
				case 'W':
					maze[2].Deactivate();
					pacman.surface = surfaceToNum('N');
					//pacman.surface = 'N';
					pacman.x = blockNumber-1;
					break;
				case 'S':
					maze[3].Deactivate();
					//pacSurface = 'W';
					pacman.surface = surfaceToNum('W');
					pacman.x = blockNumber-1;
					break;
				case 'E':
					maze[4].Deactivate();
					//pacSurface = 'S';
					pacman.surface = surfaceToNum('S');
					pacman.x = blockNumber-1;
					break;
				case 'B':
					maze[5].Deactivate();
					pacman.surface = surfaceToNum('W');
					//pacSurface = 'W';
					pacman.x = blockNumber-1 - pacman.y;
					pacman.y = blockNumber-1;
					pacman.xdir = 0;
					pacman.ydir = -1;
					break;
			}
		}
	}
	else if(pacman.ydir < 0){
		pacman.y--;
		if(pacman.y < 0){
			switch(NumToSurface(pacman.surface)){
				case 'T':
					maze[0].Deactivate();
					//pacSurface = 'N';
					pacman.surface = surfaceToNum('N');
					pacman.x = blockNumber-1 - pacman.x;
					pacman.y = 0;
					pacman.ydir = 1;
					break;
				case 'N':
					maze[1].Deactivate();
					//pacSurface = 'T';
					pacman.surface = surfaceToNum('T');
					pacman.x = blockNumber-1 - pacman.x;
					pacman.y = 0;
					pacman.ydir = 1;
					break;
				case 'W':
					maze[2].Deactivate();
					//pacSurface = 'T';
					pacman.surface = surfaceToNum('T');
					pacman.y = pacman.x;
					pacman.x = 0;
					pacman.ydir = 0;
					pacman.xdir = 1;
					break;
				case 'S':
					maze[3].Deactivate();
					//pacSurface = 'T';
					pacman.surface = surfaceToNum('T');
					pacman.y = blockNumber-1;
					break;
				case 'E':
					maze[4].Deactivate();
					//pacSurface = 'T';
					pacman.surface = surfaceToNum('T');
					pacman.y= blockNumber-1 - pacman.x;
					pacman.x = blockNumber-1;
					pacman.xdir = -1;
					pacman.ydir = 0;
					break;
				case 'B':
					maze[5].Deactivate();
					//pacSurface = 'S';
					pacman.surface = surfaceToNum('S');
					pacman.y = blockNumber-1;
					break;
			}
		}
	}
	else if(pacman.xdir > 0){
		pacman.x++;
		if(pacman.x >= blockNumber){
			switch(NumToSurface(pacman.surface)){
				case 'T':
					maze[0].Deactivate();
					pacman.surface = surfaceToNum('E');
					//pacSurface = 'E';
					pacman.x = blockNumber-1 - pacman.y;
					pacman.y = 0;
					pacman.xdir = 0;
					pacman.ydir = 1;
					break;
				case 'N':
					maze[1].Deactivate();
					//pacSurface = 'W';
					pacman.surface = surfaceToNum('W');
					pacman.x = 0;
					break;
				case 'W':
					maze[2].Deactivate();
					//pacSurface = 'S';
					pacman.surface = surfaceToNum('S');
					pacman.x = 0;
					break;
				case 'S':
					maze[3].Deactivate();
					//pacSurface = 'E';
					pacman.surface = surfaceToNum('E');
					pacman.x = 0;
					break;
				case 'E':
					maze[4].Deactivate();
					//pacSurface = 'N';
					pacman.surface = surfaceToNum('N');
					pacman.x = 0;
					break;
				case 'B':
					maze[5].Deactivate();
					//pacSurface = 'E';
					pacman.surface = surfaceToNum('E');
					pacman.x = pacman.y;
					pacman.y = blockNumber-1;
					pacman.xdir = 0;
					pacman.ydir = -1;
					break;
			}
		}
	}
	else{
		pacman.y++;
		if(pacman.y >= blockNumber){
			switch(NumToSurface(pacman.surface)){
				case 'T':
					maze[0].Deactivate();
					//pacSurface = 'S';
					pacman.surface = surfaceToNum('S');
					pacman.y = 0;
					break;
				case 'N':
					maze[1].Deactivate();
					//pacSurface = 'B';
					pacman.surface = surfaceToNum('B');
					pacman.x = blockNumber-1-pacman.x;
					pacman.y = blockNumber-1;
					pacman.ydir = -1;
					break;
				case 'W':
					maze[2].Deactivate();
					//pacSurface = 'B';
					pacman.surface = surfaceToNum('B');
					pacman.y = blockNumber-1-pacman.x;
					pacman.x = 0;
					pacman.ydir = 0;
					pacman.xdir = 1;
					break;
				case 'S':
					maze[3].Deactivate();
					//pacSurface = 'B';
					pacman.surface = surfaceToNum('B');
					pacman.y = 0;
					break;
				case 'E':
					maze[4].Deactivate();
					//pacSurface = 'B';
					pacman.surface = surfaceToNum('B');
					pacman.y = pacman.x;
					pacman.x = blockNumber-1;
					pacman.ydir = 0;
					pacman.xdir = -1;
					//bool powerState;
					break;
				case 'B':
					maze[5].Deactivate();
					//pacSurface = 'N';
					pacman.surface = surfaceToNum('N');
					pacman.x = blockNumber-1 - pacman.x;
					pacman.y = blockNumber-1;
					pacman.ydir = -1;
					break;
			}
		}
	}
	int x = pacman.x;
	int y = pacman.y;
	switch(NumToSurface(pacman.surface)){
		case 'T':
			if(maze[0].ReturnElement(x,y) == 1){
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			break;
		case 'N':
			if(maze[1].ReturnElement(x,y) == 1){
				//pacSurface = prevSurface;
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			break;
		case 'W':
			if(maze[2].ReturnElement(x,y) == 1){
				//pacSurface = prevSurface;
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			break;
		case 'S':
			if(maze[3].ReturnElement(x,y) == 1){
				//pacSurface = prevSurface;
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			maze[3].Activate(pacman,curState);
			break;
		case 'E':
			if(maze[4].ReturnElement(x,y) == 1){
				//pacSurface = prevSurface;
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			break;
		case 'B':
			if(maze[5].ReturnElement(x,y) == 1){
				//pacSurface = prevSurface;
				pacman.surface = prevSurface;
				pacman.x = prevX;
				pacman.y = prevY;
			}
			break;
	}
	x = pacman.x;
	y = pacman.y;

	/* Update the pacman state in the surface maze */
	switch(NumToSurface(pacman.surface)){
		case 'T':
			maze[0].Activate(pacman,curState);
			if(maze[0].EatPerl(x,y)){perls++;}
			if(maze[0].EatCherry(x,y)){cherries++;}
			if(maze[0].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
		case 'N':
			maze[1].Activate(pacman,curState);
			if(maze[1].EatPerl(x,y)){perls++;};
			if(maze[1].EatCherry(x,y)){cherries++;};
			if(maze[1].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
		case 'W':
			maze[2].Activate(pacman,curState);
			if(maze[2].EatPerl(x,y)){perls++;};
			if(maze[2].EatCherry(x,y)){cherries++;};
			if(maze[2].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
		case 'S':
			maze[3].Activate(pacman,curState);
			if(maze[3].EatPerl(x,y)){perls++;};
			if(maze[3].EatCherry(x,y)){cherries++;};
			if(maze[3].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
		case 'E':
			maze[4].Activate(pacman,curState);
			if(maze[4].EatPerl(x,y)){perls++;};
			if(maze[4].EatCherry(x,y)){cherries++;};
			if(maze[4].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
		case 'B':
			maze[5].Activate(pacman,curState);
			if(maze[5].EatPerl(x,y)){perls++;};
			if(maze[5].EatCherry(x,y)){cherries++;};
			if(maze[5].EatPowerPell(x,y)){
				pacman.powerState = true;
			}
			break;
	}
}
#endif
