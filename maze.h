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
extern double myPi;

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
	MAZE_SUPERPELL,
	MAZE_GHOST,
	MAZE_PACMAN,
	MAZE_VULNERGHOST
};

/* Collision Type */
enum
{
	COLL_NONE,
	COLL_EATPAC,
	COLL_EATGHOST
};

/* Eat type */
enum
{
	EAT_NONE,
	EAT_PELL,
	EAT_CHERRY,
	EAT_SUPERPELL
};

/* defines position */
typedef struct VectorStruct{
	int x;
	int y;
	int z;
}Vector;

/* the rgb information */
typedef struct ColorStruct{
	int r;
	int g;
	int b;
}Color;

/* Agent info (ghost, pacman) */
typedef struct AgentStruct{
	int x;
	int y;
	int prevX, prevY;
	int surface;
	int dir;
	bool powerState;
}Agent;

/* A maze on a single surface, uses an array to representeach block */
class Maze{
protected:
	int **maze;
	int blockNumber;
	int blockSize2D;
	Vector origin; // the (0,0) point on the global coordinates
	Color baseColor; // R,G,B

public:
	Maze();
	~Maze();
	void SetMaze(int x, int y , int input); // set the maze array
	void SetCherry();
	void SetSuperPells();
	void SetOrientation(int surface); // set the maze's relative position to other surfaces
	void Draw();
	void DrawGhost(int ghostX, int ghostY);
	void DrawPacman(int pacX, int pacY);
	void Print();
	bool EatPell(int,int);
	bool EatCherry(int,int);
	bool EatSuperPell(int,int);
	const int ReturnElement(int x, int y) const; // return the element of a coordinate
};

Maze::Maze(){
	blockNumber = 25;
	blockSize2D = 6;
	maze = new int*[blockNumber];
	for(int i = 0;i < blockNumber;i++){
		maze[i] = new int [blockNumber];
	}
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			maze[i][j] = 1;
		}
	}
}

Maze::~Maze(){
	for(int i = 0;i < blockNumber;i++){
		delete [] maze[i];
	}
	delete [] maze;
}
void Maze::SetCherry(){
	int x = rand() % blockNumber;
	int y = rand() % blockNumber;
	while(maze[x][y] == MAZE_WALL){
		x = rand() % blockNumber;
		y = rand() % blockNumber;
	}
	maze[x][y] = MAZE_CHERRY;
}

void Maze::SetSuperPells(){
	int x = rand() % blockNumber;
	int y = rand() % blockNumber;
	while(maze[x][y] == MAZE_WALL){
		x = rand() % blockNumber;
		y = rand() % blockNumber;
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

/* Build the maze */
void Maze::SetMaze(int x,int y,int input){
	if(input == 0) maze[x][y] = MAZE_PELL;
	else maze[x][y] = MAZE_WALL;
}

void Maze::SetOrientation(int surface){
	switch(surface){
		case SURFACE_T:
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 0;
			origin.x = 2 * blockNumber * blockSize2D;
			origin.y = 0;
			break;
		case SURFACE_B:
			baseColor.r = 0;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2 * blockNumber * blockSize2D;
			origin.y = 2 * blockNumber * blockSize2D;
			break;
		case SURFACE_N:
			baseColor.r = 0;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = 0;
			origin.y = blockNumber * blockSize2D;
			break;
		case SURFACE_W:
			baseColor.r = 200;
			baseColor.g = 0;
			baseColor.b = 200;
			origin.x = blockNumber * blockSize2D;
			origin.y = blockNumber * blockSize2D;
			break;
		case SURFACE_S:
			baseColor.r = 200;
			baseColor.g = 200;
			baseColor.b = 0;
			origin.x = 2 * blockNumber * blockSize2D;
			origin.y = blockNumber * blockSize2D;
			break;
		case SURFACE_E:
			baseColor.r = 0;
			baseColor.g = 200;
			baseColor.b = 200;
			origin.x = 3 * blockNumber * blockSize2D;
			origin.y = blockNumber * blockSize2D;
			break;
	}
}

const int Maze::ReturnElement(int x,int y) const{
	return maze[x][y];
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

void Maze::DrawGhost(int ghostX, int ghostY){
	glColor3ub(0,0,0);
	glBegin(GL_QUADS);
	ghostX *= blockSize2D;
	ghostY *= blockSize2D;
	glVertex2i(origin.x + ghostX            ,origin.y + ghostY            );
	glVertex2i(origin.x + ghostX + blockSize2D,origin.y + ghostY            );
	glVertex2i(origin.x + ghostX + blockSize2D,origin.y + ghostY + blockSize2D);
	glVertex2i(origin.x + ghostX            ,origin.y + ghostY + blockSize2D);
	glEnd();
}

void Maze::DrawPacman(int pacX, int pacY){
	double x = (double)(origin.x + blockSize2D*pacX + blockSize2D/2);
	double y = (double)(origin.y + blockSize2D*pacY + blockSize2D/2);
	double r = blockSize2D/2;
	glColor3ub(0, 0, 100);
	glBegin(GL_POLYGON);
	for(int i = 0;i < 64;i++){
		double angle = (double)i*myPi/32.0;
		double cx = x + r*cos(angle);
		double cy = y + r*sin(angle);
		glVertex2d(cx,cy);
	}
	glEnd();
}

void Maze::Draw(){
	for(int i = 0;i < blockNumber;i++){
		for(int j = 0;j < blockNumber;j++){
			int x = blockSize2D * i;
			int y = blockSize2D * j;
			
			/* Draw a color block */
			if(maze[i][j] == MAZE_WALL){
				glColor3ub(baseColor.r, baseColor.g, baseColor.b);
			}
			else{
				/* White color for path */
				glColor3ub(255,255,255);
			}
			glBegin(GL_QUADS);
			glVertex2i(origin.x + x               , origin.y + y               );
			glVertex2i(origin.x + x + blockSize2D, origin.y + y               );
			glVertex2i(origin.x + x + blockSize2D, origin.y + y + blockSize2D);
			glVertex2i(origin.x + x               , origin.y + y + blockSize2D);
			glEnd();
			
			/* Draw maze elements */
			if(maze[i][j] != MAZE_EMPTY){
				switch(maze[i][j]){
					case MAZE_PELL:
						glColor3ub(100,100,0);
						break;
					case MAZE_CHERRY:
						glColor3ub(200,0,0);
						break;
					case MAZE_SUPERPELL:
						glColor3ub(0,0,200);
						break;
				}
				
				double centerX = origin.x + x + blockSize2D/2;
				double centerY = origin.y + y + blockSize2D/2;
				double r = blockSize2D/2.0 - 1.0;

				glBegin(GL_POLYGON);
				for(int k = 0;k < 64;k++){
					double angle = (double)k*myPi/32.0;
					double cx = centerX + r*cos(angle);
					double cy = centerY + r*sin(angle);
					glVertex2d(cx,cy);
				}
				glEnd();
			}
		}
	}

	
	/*Draw the frame */
	glColor3ub(1,1,1);
	glBegin(GL_LINES);
	glVertex2i(origin.x,origin.y);
	glVertex2i(origin.x + blockNumber*blockSize2D,origin.y);

	glVertex2i(origin.x + blockNumber*blockSize2D,origin.y);
	glVertex2i(origin.x + blockNumber*blockSize2D,origin.y + blockNumber*blockSize2D);

	glVertex2i(origin.x + blockNumber*blockSize2D,origin.y + blockNumber*blockSize2D);
	glVertex2i(origin.x,origin.y + blockNumber*blockSize2D);

	glVertex2i(origin.x,origin.y + blockNumber*blockSize2D);
	glVertex2i(origin.x,origin.y);
	glEnd();
}

/* 6 Maze at each surface */
class FullMaze{
private:
	Maze maze[6]; // 0-T,1-N,2-W,3-S,4-E,5-B
	int blockNumber;
	vector<Agent> ghost;
	int ghostControl;
	int ghostLives;
	int ghostNumber;
public:
	Agent pacman;
	FullMaze();
	void Draw();
	void Print();
	int PacMove();
	void GhostMove(int);
	void Restart();
	void Restore();
	void GhostRandom(Agent &agent);
	void ChangePacDirection(int);
	void ChangeGhostDirection(int);
	int ReturnGhostControl();
	int CollisionDetect();
	void SetMaze();
	void SetCherry();
	void SetSuperPells();
	const void ReturnMaze(int***) const;
	
	Agent &ReturnPacman();
	vector<Agent> &ReturnGhost();
	Maze* ReturnMaze();	


	void ReturnPacman(Agent &pacInfo);
	void ReturnGhost(vector<Agent> &ghostInfo);
	void SwitchGhost();
	void GhostChase(int ghostIndex);
	void AgentMove(Agent &agent);

};

FullMaze::FullMaze(){
	blockNumber = 25;
	ghostNumber = 12;
	maze[SURFACE_T].SetOrientation(SURFACE_T);
	maze[SURFACE_N].SetOrientation(SURFACE_N);
	maze[SURFACE_W].SetOrientation(SURFACE_W);
	maze[SURFACE_S].SetOrientation(SURFACE_S);
	maze[SURFACE_E].SetOrientation(SURFACE_E);
	maze[SURFACE_B].SetOrientation(SURFACE_B);
}


Agent &FullMaze::ReturnPacman(){
	return pacman;
}
vector<Agent> &FullMaze::ReturnGhost(){
	return ghost;
}

Maze* FullMaze::ReturnMaze(){
	return maze;
}


void FullMaze::Restart(){
	/* restore initial map */
	SetMaze();
	
	/* pacman initial state */
	pacman.surface = SURFACE_S;
	pacman.x = 8;
	pacman.y = 12;
	pacman.prevX = 8;
	pacman.prevY = 12;
	pacman.dir = DIR_STOP;	
	pacman.powerState = false;

	/* ghost initial state */
	ghostLives = ghostNumber;
	ghost.resize(ghostLives);
	int j = 0;
	int k = 0;
	int s = 0;
	int surfaceSequence[6] = {SURFACE_S, SURFACE_E, SURFACE_W,
							  SURFACE_N, SURFACE_T, SURFACE_B};
	ghostControl = 0;
	for(int i = 0;i < ghostLives;i++){
		if(i != ghostControl){
			GhostRandom(ghost[i]);
		}
		else{
			ghost[i].dir = DIR_STOP;
		}
		ghost[i].surface = surfaceSequence[s];
		ghost[i].x = k + 11;
		ghost[i].y = 11;
		ghost[i].prevX = k + 11;
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


/* Simple heuristic AI for automatic ghost chase */
void FullMaze::GhostChase(int ghostIndex) {
	// this is probably wrong now
	int x = pacman.x;
	int y = pacman.y;
	int index = ghostIndex;
	int distx = abs(x - ghost[index].x);
	int disty = abs(y - ghost[index].y);
	int prevx = ghost[index].x;
	int prevy = ghost[index].y;

	if (distx < disty) {
		if (x < prevx) ghost[index].dir = DIR_RIGHT;
		else ghost[index].dir = DIR_LEFT; 
	}
	else {
		if (y < prevy) ghost[index].dir = DIR_UP;
		else ghost[index].dir = DIR_DOWN; 
	}
}

void FullMaze::GhostRandom(Agent &agent){
	int dir = rand() % 4;
	agent.dir = dir;
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

void FullMaze::Restore(){
	
	/* pacman initial state */
	pacman.surface = SURFACE_S;
	pacman.x = 8;
	pacman.y = 12;
	pacman.dir = DIR_STOP;
	
	/* ghost inital state */
	ghost.resize(ghostLives);
	int surfaceSequence[6] = {SURFACE_S, SURFACE_E, SURFACE_W,
							  SURFACE_N, SURFACE_T, SURFACE_B};
	ghostControl = 0;
	int j = 0;
	int k = 0;
	int s = 0;
	for(int i = 0;i < ghostLives;i++){
		if(i != ghostControl){
			GhostRandom(ghost[i]);
		}
		else{
			ghost[i].dir = DIR_STOP;
		}
		ghost[i].surface = surfaceSequence[s];
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

/* Check if there is a collision between ghost and pacman */
int FullMaze::CollisionDetect(){
	int n = ghost.size();
	for(int i = 0;i < n;i++){
		/* Check collision */
		bool collide = false;
		if(pacman.surface == ghost[i].surface && pacman.x == ghost[i].x && pacman.y == ghost[i].y) 
			collide = true;
		else if(pacman.surface == ghost[i].surface && pacman.prevX == ghost[i].x && pacman.prevY == ghost[i].y
					&& pacman.x == ghost[i].prevX && pacman.y == ghost[i].prevY) 
			collide = true;
		
		if(collide == true){
			if(pacman.powerState == false){
				/* Eat pacman */
				Restore();
				return COLL_EATPAC;
			}
			else{
				/* Eat ghost i */
				ghost.erase(ghost.begin() + i);
				ghostLives--;
				if(ghostLives > 0) ghostControl = rand()%ghostLives;
				else ghostControl = -1;
				return COLL_EATGHOST;
			}
		}
	}
	return COLL_NONE;
}

void FullMaze::Draw(){
	/* Draw maze map */
	for(int i = 0;i < 6;i++){
		maze[i].Draw();
	}
	/* Draw ghosts */
	int n = ghost.size();
	int x, y, surface;
	for(int i = 0;i < n;i++){
		surface = ghost[i].surface;
		x = ghost[i].x;
		y = ghost[i].y;
		maze[surface].DrawGhost(x,y);
	}
	
	/* Draw pacman */
	x = pacman.x;
	y = pacman.y;
	surface = pacman.surface;
	maze[surface].DrawPacman(x, y);
}

void FullMaze::ReturnGhost(vector<Agent> &ghostInfo){
	int n = ghost.size();
	ghostInfo.clear();
	for(int i = 0;i < n;i++){
		ghostInfo.push_back(ghost[i]);
	}
}

void FullMaze::ReturnPacman(Agent &pacInfo){
	pacInfo.x = pacman.x;
	pacInfo.y = pacman.y;
	pacInfo.surface = pacman.surface;
	pacInfo.powerState = pacman.powerState;
	pacInfo.dir = pacman.dir;
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

const void FullMaze::ReturnMaze(int *** output) const{
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
			break;
		case PAC_UP:
			pacman.dir = DIR_UP;
			break;
		case PAC_RIGHT:
			pacman.dir = DIR_RIGHT;
			break;
		case PAC_DOWN:
			pacman.dir = DIR_DOWN;
			break;
		default:
			// do nothing if unknown command */
			break;
	}
}

void FullMaze::ChangeGhostDirection(int dir){
	switch(dir){
		case GHOST_LEFT:
			ghost[ghostControl].dir = DIR_LEFT;
			break;
		case GHOST_UP:
			ghost[ghostControl].dir = DIR_UP;
			break;
		case GHOST_RIGHT:
			ghost[ghostControl].dir = DIR_RIGHT;
			break;
		case GHOST_DOWN:
			ghost[ghostControl].dir = DIR_DOWN;
			break;
		case GHOST_SWITCH:
			// switch the controlled ghost 
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
	/* find the ghost which is on the same surface as pacman */
	vector<int> closestGhost;
	int n = ghost.size();
	for (int i = 0;i < n;i++) {
		if (ghost[i].surface == pacman.surface){
			closestGhost.push_back(i);
		}
	}
	n = closestGhost.size();
	if(n != 0){
		ghostControl = closestGhost[rand() % n];
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
			/* Chase pacman if in reasonable range, or else random */
			if(ghost[i].surface == pacman.surface) GhostChase(i);
			else GhostRandom(ghost[i]);
			if((loopCount*3) % 4 == 0){
				// to slow down the ghost, speed 3/4 
				continue;
			}
		}
			
		/* Move the ghost */
		AgentMove(ghost[i]);
		
		/* Check if bump into the wall then restore */
		int x = ghost[i].x;
		int y = ghost[i].y;
		int surface = ghost[i].surface;
		if (maze[surface].ReturnElement(x, y) == MAZE_WALL) {
			ghost[i].x = prevX;
			ghost[i].y = prevY;
			ghost[i].surface = prevSurface;
		}
	}
}

/* Move an agent on the cube and the cube switching logic */
void FullMaze::AgentMove(Agent &agent){
	int surface = agent.surface;
	switch(agent.dir){
		case DIR_LEFT:
			agent.x--;
			if(agent.x < 0){
				switch(surface){
					case SURFACE_T:
						agent.surface = SURFACE_W;
						agent.x = agent.y;
						agent.y = 0;
						agent.dir = DIR_DOWN;
						break;
					case SURFACE_N:
						agent.surface = SURFACE_E;
						agent.x = blockNumber-1;
						break;
					case SURFACE_W:
						agent.surface = SURFACE_N;
						//agent.surface = SURFACE_N;
						agent.x = blockNumber-1;
						break;
					case SURFACE_S:
						//pacSurface = SURFACE_W;
						agent.surface = SURFACE_W;
						agent.x = blockNumber-1;
						break;
					case SURFACE_E:
						//pacSurface = SURFACE_S;
						agent.surface = SURFACE_S;
						agent.x = blockNumber-1;
						break;
					case SURFACE_B:
						agent.surface = SURFACE_W;
						//pacSurface = SURFACE_W;
						agent.x = blockNumber-1 - agent.y;
						agent.y = blockNumber-1;
						agent.dir = DIR_UP;
						break;
				}
			}
			break;
		case DIR_UP:
			agent.y--;
			if(agent.y < 0){
				switch(agent.surface){
					case SURFACE_T:
						//pacSurface = SURFACE_N;
						agent.surface = SURFACE_N;
						agent.x = blockNumber-1 - agent.x;
						agent.y = 0;
						agent.dir = DIR_DOWN;
						break;
					case SURFACE_N:
						//pacSurface = SURFACE_T;
						agent.surface = SURFACE_T;
						agent.x = blockNumber-1 - agent.x;
						agent.y = 0;
						agent.dir = DIR_DOWN;
						break;
					case SURFACE_W:
						//pacSurface = SURFACE_T;
						agent.surface = SURFACE_T;
						agent.y = agent.x;
						agent.x = 0;
						agent.dir = DIR_RIGHT;
						break;
					case SURFACE_S:
						//pacSurface = SURFACE_T;
						agent.surface = SURFACE_T;
						agent.y = blockNumber-1;
						break;
					case SURFACE_E:
						//pacSurface = SURFACE_T;
						agent.surface = SURFACE_T;
						agent.y= blockNumber-1 - agent.x;
						agent.x = blockNumber-1;
						agent.dir = DIR_LEFT;
						break;
					case SURFACE_B:
						//pacSurface = SURFACE_S;
						agent.surface = SURFACE_S;
						agent.y = blockNumber-1;
						break;
				}
			}
			break;
		case DIR_RIGHT:
			agent.x++;
			if(agent.x >= blockNumber){
				switch(agent.surface){
					case SURFACE_T:
						agent.surface = SURFACE_E;
						//pacSurface = SURFACE_E;
						agent.x = blockNumber - 1 - agent.y;
						agent.y = 0;
						agent.dir = DIR_DOWN;
						break;
					case SURFACE_N:
						//pacSurface = SURFACE_W;
						agent.surface = SURFACE_W;
						agent.x = 0;
						break;
					case SURFACE_W:
						//pacSurface = SURFACE_S;
						agent.surface = SURFACE_S;
						agent.x = 0;
						break;
					case SURFACE_S:
						//pacSurface = SURFACE_E;
						agent.surface = SURFACE_E;
						agent.x = 0;
						break;
					case SURFACE_E:
						//pacSurface = SURFACE_N;
						agent.surface = SURFACE_N;
						agent.x = 0;
						break;
					case SURFACE_B:
						//pacSurface = SURFACE_E;
						agent.surface = SURFACE_E;
						agent.x = agent.y;
						agent.y = blockNumber-1;
						agent.dir = DIR_UP;
						break;
				}
			}
			break;
		case DIR_DOWN:
			agent.y++;
			if(agent.y >= blockNumber){
				switch(agent.surface){
					case SURFACE_T:
						//pacSurface = SURFACE_S;
						agent.surface = SURFACE_S;
						agent.y = 0;
						break;
					case SURFACE_N:
						//pacSurface = SURFACE_B;
						agent.surface = SURFACE_B;
						agent.x = blockNumber-1-agent.x;
						agent.y = blockNumber-1;
						agent.dir = DIR_UP;
						break;
					case SURFACE_W:
						//pacSurface = SURFACE_B;
						agent.surface = SURFACE_B;
						agent.y = blockNumber-1-agent.x;
						agent.x = 0;
						agent.dir = DIR_RIGHT;
						break;
					case SURFACE_S:
						//pacSurface = SURFACE_B;
						agent.surface = SURFACE_B;
						agent.y = 0;
						break;
					case SURFACE_E:
						//pacSurface = SURFACE_B;
						agent.surface = SURFACE_B;
						agent.y = agent.x;
						agent.x = blockNumber-1;
						agent.dir = DIR_LEFT;
						//bool powerState;
						break;
					case SURFACE_B:
						//pacSurface = SURFACE_N;
						agent.surface = SURFACE_N;
						agent.x = blockNumber - 1 - agent.x;
						agent.y = blockNumber - 1;
						agent.dir = DIR_UP;
						break;
				}
			}
			break;
	}
}

/* Move pacman and update map from eaten item, and return score */
int FullMaze::PacMove(){
	/* Store the current state to prevent bumping to walls */
	int prevX, prevY, prevSurface;
	int x, y, surface;
	prevX = pacman.x;
	prevY = pacman.y;
	pacman.prevX = pacman.x;
	pacman.prevY = pacman.y;
	prevSurface = pacman.surface;
	AgentMove(pacman);
	
	/* The moved parameters */
	x = pacman.x;
	y = pacman.y;
	surface = pacman.surface;
	/* If there is a contradiction in the movement, restore and stop */
	if(maze[surface].ReturnElement(x,y) == MAZE_WALL){
		pacman.surface = prevSurface;
		pacman.x = prevX;
		pacman.y = prevY;
		x = pacman.x;
		y = pacman.y;
	}
	
	/* Update the pacman state in the surface maze and calculate reward */
	surface = pacman.surface;
	int eat = EAT_NONE;
	if(maze[surface].EatPell(x,y)) eat = EAT_PELL;
	if(maze[surface].EatCherry(x,y)) eat = EAT_CHERRY;
	if(maze[surface].EatSuperPell(x,y)){
		pacman.powerState = true;
		eat = EAT_SUPERPELL;
	}
	return eat;
}
#endif



