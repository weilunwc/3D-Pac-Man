/* 
 * maze.h 
 * The header file for the maze class, each surface of the maze
 * in another subclass, the fullmaze class contains six surfaces
 * This program also alows users to design their own maze by moving the pacman
 * to design the maze structure, and also enabeles prototype experimentation
 * of the transfer between different surfaces
 * Wei Lun William Chen 2017.11.19
 */
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

/* Global variables shared by the whole program */
extern int blockSize_2D;
extern const int blockNumber;  // the size of the surface array
extern double myPi;
extern const int ghostNumber;

/* Commands */
enum
{
	PAC_UP,
	PAC_DOWN,
	PAC_LEFT,
	PAC_RIGHT,
	PAC_NONE
};

enum
{
	GHOST_UP,
	GHOST_DOWN,
	GHOST_LEFT,
	GHOST_RIGHT,
	GHOST_SWITCH,
	GHOST_NONE
};

/* Direction */
enum
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_STOP
};


/* Surface */
enum
{
	SURFACE_T,
	SURFACE_N,
	SURFACE_W,
	SURFACE_S,
	SURFACE_E,
	SURFACE_B,
};

/* Maze Element */
enum
{
	MAZE_PELL,
	MAZE_EMPTY,
	MAZE_WALL,
	MAZE_CHERRY,
	MAZE_SUPERPELL
};


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
	int dir;
	bool powerState;
}PacMan;


/* the rgb information */
typedef struct ColorStruct{
	int r;
	int g;
	int b;
}Color;


/* A maze on a single surface, uses an array to representeach block */
class Maze{
protected:
	int **maze;
	int pacState; // 0 not in this surface, 1 not clear box, 2 clear box
	Coord pacman;
	Coord cherry;
	vector<bool> ghostState;
	Coord origin; // the (0,0) point on the global coordinates
	Color baseColor; // R,G,B

public:
	Maze();
	~Maze();
	void SetMaze(int,int,int); // set the maze array
	void SetCherry();
	void SetSuperPells();
	void SetOrientation(char); // set the maze's relative position to other surfaces
	void Draw();
	void DrawGhost(int,int);
	void Print();
	bool EatPell(int,int);
	bool EatCherry(int,int);
	bool EatSuperPell(int,int);
	void Activate(PacMan,int);// changes pacman coordinates and state
	void Deactivate(); // turns down the pacman drawing
	const int ReturnElement(int,int)const; // return the element of a coordinate
	int ReturnPells();
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
	while(maze[x][y] == MAZE_WALL){
		x = rand()%blockNumber;
		y = rand()%blockNumber;
	}
	cherry.x = x;
	cherry.y = y;
	maze[x][y] = MAZE_CHERRY;
}

void Maze::SetSuperPells(){
	int x = rand()%blockNumber;
	int y = rand()%blockNumber;
	while(maze[x][y] == MAZE_WALL){
		x = rand()%blockNumber;
		y = rand()%blockNumber;
	}
	maze[x][y] = MAZE_SUPERPELL;
}

bool Maze::EatPell(int i,int j){

	if(maze[i][j] == MAZE_PELL){
		maze[i][j] = MAZE_EMPTY;
		return true;
	}
	return false;
}
bool Maze::EatCherry(int i,int j){

	if(maze[i][j] == MAZE_CHERRY){
		maze[i][j] = MAZE_EMPTY;
		return true;
	}
	return false;
}


bool Maze::EatSuperPell(int i,int j){

	if(maze[i][j] == MAZE_SUPERPELL){
		maze[i][j] = MAZE_EMPTY;
		return true;
	}
	return false;
}


int Maze::ReturnPells(){
	int pells = 0;
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			if(maze[i][j] == -1){
				pells++;
			}
		}
	}
	return pells;
}

/* Build the maze */
void Maze::SetMaze(int i,int j,int input){
	if(input == 0) maze[i][j] = MAZE_PELL;
	else maze[i][j] = MAZE_WALL;
}

void Maze::SetOrientation(char orient){
	switch(orient){
		case SURFACE_T:
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = 0;
			break;
		case SURFACE_B:
			baseColor.r = 0;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = 2*blockNumber*blockSize_2D;
			break;
		case SURFACE_N:
			baseColor.r = 0;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = 0;
			origin.y = blockNumber*blockSize_2D;
			break;
		case SURFACE_W:
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = blockNumber*blockSize_2D;
			origin.y = blockNumber*blockSize_2D;
			break;
		case SURFACE_S:
			baseColor.r = 200;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2*blockNumber*blockSize_2D;
			origin.y = blockNumber*blockSize_2D;
			break;
		case SURFACE_E:
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

/* Print the maze components */
void Maze::Print(){
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			printf("%d",maze[j][i]);
		}
		printf("\n");
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
			
			/* Draw background */
			if(maze[i][j] == MAZE_WALL){
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

			if(maze[i][j] == MAZE_PELL){
				// draw the pells
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
			if(maze[i][j] == MAZE_CHERRY){
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
			if(maze[i][j] == MAZE_SUPERPELL){
				// draw the super pells
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

/* 6 Maze at each surface */
class FullMaze{
private:
	Maze maze[6]; // 0-T,1-N,2-W,3-S,4-E,5-B

	vector<Ghost> ghost;
	int ghostControl;
	int ghostLives;

	//char pacSurface;
	int curState; // 1 for not clear, 2 for clear box

public:
	PacMan pacman;
	int ghost_eaten;
	int pells;
	int cherries;
	FullMaze(){};
	void Draw();
	void Print();
	void PacMove();
	void GhostMove(int);
	void Restart();
	void Restore();
	void RandomDirection(int);
	void ChangePacDirection(int);
	void ChangeGhostDirection(int);
	int ReturnGhostControl();
	bool CollisionDetect();
	void SetMaze();
	void SetCherry();
	void SetSuperPells();
	const void ReturnMaze(int***)const;
	void ReturnPacman(PacMan &pacInfo);
	void ReturnGhost(vector<Ghost> &ghostInfo);
	int ReturnPells();
	void ChangeIndexToDir(int);
	void SwitchGhost();
	void GhostChase(int,int,int);
};


void FullMaze::Restart(){
	SetMaze();
	maze[SURFACE_T].SetOrientation(SURFACE_T);
	maze[SURFACE_N].SetOrientation(SURFACE_N);
	maze[SURFACE_W].SetOrientation(SURFACE_W);
	maze[SURFACE_S].SetOrientation(SURFACE_S);
	maze[SURFACE_E].SetOrientation(SURFACE_E);
	maze[SURFACE_B].SetOrientation(SURFACE_B);
	//pacSurface = SURFACE_S;
	ghost_eaten = 0;
	cherries = 0;
	pacman.surface = SURFACE_S;
	curState = 1;
	pacman.x = 8;
	pacman.y = 12;
	pacman.prevX = 8;
	pacman.prevY = 12;
	pacman.powerState = false;
	pells = 0;
	pacman.xdir = 0;
	pacman.ydir = 0;
	maze[SURFACE_S].Activate(pacman, curState);
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

/* Restore - when pacman dies, return to initial location */
void FullMaze::Restore(){
	pacman.surface = SURFACE_S;
	curState = 1;
	pacman.x = 8;
	pacman.y = 12;
	pacman.xdir = 0;
	pacman.ydir = 0;
	for(int i = 0;i < 6;i++){
		maze[i].Deactivate();
	}
	maze[SURFACE_S].Activate(pacman,curState);
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


int FullMaze::ReturnPells(){
	int pells = 0;
	for(int i = 0;i < 6;i++){
		pells += maze[i].ReturnPells();
	}
	return pells;
}

/* Simple heuristic AI for automatic ghost chase */
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

/* Place cherry on every surface */
void FullMaze::SetCherry(){
	for(int i = 0;i < 6;i++){
		maze[i].SetCherry();
	}
}

/* Place PowerPells */
void FullMaze::SetSuperPells(){
	for(int i = 0;i < 6;i++){
		maze[i].SetSuperPells();
	}
}

/* returns the player controlled ghost index */
int FullMaze::ReturnGhostControl(){
	return ghostControl;
}



/* Check if there is a collision between ghost and pacman */
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
	return false;
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

void FullMaze::ReturnGhost(vector<Ghost> &ghostInfo){
	int n = ghost.size();
	ghostInfo.clear();
	for(int i = 0;i < n;i++){
		ghostInfo.push_back(ghost[i]);
	}
}

void FullMaze::ReturnPacman(PacMan &pacInfo){
	pacInfo.x = pacman.x;
	pacInfo.y = pacman.y;
	pacInfo.xdir = pacman.xdir;
	pacInfo.ydir = pacman.ydir;
	pacInfo.surface = pacman.surface;
	pacInfo.powerState = pacman.powerState;
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

/* Load from text and build maze */
void FullMaze::SetMaze(){

	fstream input;
	string buffer;
	input.open("maps/mapfull25.txt",ios::in);
	for(int i = 0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			input >> buffer;
			for(int k = 0;k < blockNumber;k++){
				maze[i].SetMaze(k, j, buffer[k] - '0');
			}
		}
	}
	input.close();
}

/* Print the full maze */
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

/* PacMan reads command and change directiond */
//note that the ydir is not intuitive due to matrix nature 
void FullMaze::ChangePacDirection(int dir){
	switch(dir){
		case PAC_LEFT:
			pacman.dir = DIR_LEFT;
			pacman.xdir = -1;
			pacman.ydir = 0;
			break;
		case PAC_UP:
			pacman.dir = DIR_UP;
			pacman.ydir = -1;
			pacman.xdir = 0;
			break;
		case PAC_RIGHT:
			pacman.dir = DIR_RIGHT;
			pacman.xdir = 1;
			pacman.ydir = 0;
			break;
		case PAC_DOWN:
			pacman.dir = DIR_DOWN;
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
		case GHOST_LEFT:
			ghost[ghostControl].xdir = -1;
			ghost[ghostControl].ydir = 0;
			break;
		case GHOST_UP:
			ghost[ghostControl].ydir = -1;
			ghost[ghostControl].xdir = 0;
			break;
		case GHOST_RIGHT:
			ghost[ghostControl].xdir = 1;
			ghost[ghostControl].ydir = 0;
			break;
		case GHOST_DOWN:
			ghost[ghostControl].xdir = 0;
			ghost[ghostControl].ydir = 1;
			break;
		case GHOST_SWITCH:
			SwitchGhost();
			break;
		case GHOST_NONE:
			// do nothing 
			break;
		default:
			/* do nothing if unknown command */
			break;
	}
}

/* ghost player switch the ghost it wants to control */
void FullMaze::SwitchGhost(){
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

/* move the ghost */
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
			/* automatic ghost */
			if((loopCount*3) % 4 == 0){
				// to slow down the ghost, speed 3/4 
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
		if (maze[surface].ReturnElement(x, y) == MAZE_WALL) {
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

/* Move pacman */
void FullMaze::PacMove(){
	/* Store the current state to prevent bumping to walls */
	int prevX, prevY, prevSurface;
	int x, y, surface;
	prevX = pacman.x;
	prevY = pacman.y;
	pacman.prevX = pacman.x;
	pacman.prevY = pacman.y;
	prevSurface = pacman.surface;

	surface = pacman.surface;
	if(pacman.xdir < 0){
		
		pacman.x--;
		if(pacman.x < 0){
			switch(surface){
				case SURFACE_T:
					maze[surface].Deactivate();
					pacman.surface = SURFACE_W;
					pacman.x = pacman.y;
					pacman.y = 0;
					pacman.xdir = 0;
					pacman.ydir = 1;
					break;
				case SURFACE_N:
					maze[surface].Deactivate();
					pacman.surface = SURFACE_E;
					pacman.x = blockNumber-1;
					break;
				case SURFACE_W:
					maze[surface].Deactivate();
					pacman.surface = SURFACE_N;
					//pacman.surface = SURFACE_N;
					pacman.x = blockNumber-1;
					break;
				case SURFACE_S:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_W;
					pacman.surface = SURFACE_W;
					pacman.x = blockNumber-1;
					break;
				case SURFACE_E:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_S;
					pacman.surface = SURFACE_S;
					pacman.x = blockNumber-1;
					break;
				case SURFACE_B:
					maze[surface].Deactivate();
					pacman.surface = SURFACE_W;
					//pacSurface = SURFACE_W;
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
			switch(pacman.surface){
				case SURFACE_T:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_N;
					pacman.surface = SURFACE_N;
					pacman.x = blockNumber-1 - pacman.x;
					pacman.y = 0;
					pacman.ydir = 1;
					break;
				case SURFACE_N:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_T;
					pacman.surface = SURFACE_T;
					pacman.x = blockNumber-1 - pacman.x;
					pacman.y = 0;
					pacman.ydir = 1;
					break;
				case SURFACE_W:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_T;
					pacman.surface = SURFACE_T;
					pacman.y = pacman.x;
					pacman.x = 0;
					pacman.ydir = 0;
					pacman.xdir = 1;
					break;
				case SURFACE_S:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_T;
					pacman.surface = SURFACE_T;
					pacman.y = blockNumber-1;
					break;
				case SURFACE_E:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_T;
					pacman.surface = SURFACE_T;
					pacman.y= blockNumber-1 - pacman.x;
					pacman.x = blockNumber-1;
					pacman.xdir = -1;
					pacman.ydir = 0;
					break;
				case SURFACE_B:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_S;
					pacman.surface = SURFACE_S;
					pacman.y = blockNumber-1;
					break;
			}
		}
	}
	else if(pacman.xdir > 0){
		pacman.x++;
		if(pacman.x >= blockNumber){
			switch(pacman.surface){
				case SURFACE_T:
					maze[surface].Deactivate();
					pacman.surface = SURFACE_E;
					//pacSurface = SURFACE_E;
					pacman.x = blockNumber - 1 - pacman.y;
					pacman.y = 0;
					pacman.xdir = 0;
					pacman.ydir = 1;
					break;
				case SURFACE_N:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_W;
					pacman.surface = SURFACE_W;
					pacman.x = 0;
					break;
				case SURFACE_W:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_S;
					pacman.surface = SURFACE_S;
					pacman.x = 0;
					break;
				case SURFACE_S:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_E;
					pacman.surface = SURFACE_E;
					pacman.x = 0;
					break;
				case SURFACE_E:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_N;
					pacman.surface = SURFACE_N;
					pacman.x = 0;
					break;
				case SURFACE_B:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_E;
					pacman.surface = SURFACE_E;
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
			switch(pacman.surface){
				case SURFACE_T:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_S;
					pacman.surface = SURFACE_S;
					pacman.y = 0;
					break;
				case SURFACE_N:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_B;
					pacman.surface = SURFACE_B;
					pacman.x = blockNumber-1-pacman.x;
					pacman.y = blockNumber-1;
					pacman.ydir = -1;
					break;
				case SURFACE_W:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_B;
					pacman.surface = SURFACE_B;
					pacman.y = blockNumber-1-pacman.x;
					pacman.x = 0;
					pacman.ydir = 0;
					pacman.xdir = 1;
					break;
				case SURFACE_S:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_B;
					pacman.surface = SURFACE_B;
					pacman.y = 0;
					break;
				case SURFACE_E:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_B;
					pacman.surface = SURFACE_B;
					pacman.y = pacman.x;
					pacman.x = blockNumber-1;
					pacman.ydir = 0;
					pacman.xdir = -1;
					//bool powerState;
					break;
				case SURFACE_B:
					maze[surface].Deactivate();
					//pacSurface = SURFACE_N;
					pacman.surface = SURFACE_N;
					pacman.x = blockNumber - 1 - pacman.x;
					pacman.y = blockNumber - 1;
					pacman.ydir = -1;
					break;
			}
		}
	}
	x = pacman.x;
	y = pacman.y;
	/* If there is a contradiction in the movement, restore and stop */
	if(maze[pacman.surface].ReturnElement(x,y) == MAZE_WALL){
		pacman.surface = prevSurface;
		pacman.x = prevX;
		pacman.y = prevY;
		x = pacman.x;
		y = pacman.y;
	}
	
	/* Update the pacman state in the surface maze */
	surface = pacman.surface;
	maze[surface].Activate(pacman, curState);
	if(maze[surface].EatPell(x,y)){pells++;}
	if(maze[surface].EatCherry(x,y)){cherries++;}
	if(maze[surface].EatSuperPell(x,y)){
		pacman.powerState = true;
	}
}
#endif
