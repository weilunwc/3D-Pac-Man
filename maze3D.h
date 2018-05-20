#ifndef MAZE3D_H
#define MAZE3D_H

#include "maze.h"
using namespace std;

extern int blockSize3D; // Giada's Modification
extern const int blockNumber;

class Maze3D{
protected:
    
	Vector origin;
    Vector xDir;
    Vector yDir;

    Color baseColor; // R,G,B
	
    /* Graph bitmap */
    void SetPatterns();
	char patternPell[9];
    char patternSuperPell[196];
    char patternPacMan[196];
    char patternCherry[196];
    char patternGhostLeft[196];
    char patternGhostRight[196];
    char patternGhostUp[196];
    char patternGhostDown[196];
    char patternVulnerableGhost[196];
	int smallPatternSize, largePatternSize;

	/* Cube Drawing */
	void DrawBackground(int x, int y);
	void DrawWall(int x, int y);
	void DrawPell(int x, int y);
	void DrawSuperPell(int x, int y);
	void DrawCherry(int x, int y);	
	
	/* Draw pixel by pixel */
	void DrawBit(double drawX, double drawY, double drawZ, double unit, int i, int j);
public:
    Maze3D();
    void SetOrientation(char);
    
	/* Pacman and ghost */
	void DrawPacman(Agent &pacman);
	void DrawGhost(Agent &ghost, bool powerState);

	/* Cube Drawing */
    void DrawMaze(int x, int y, int input);

};

Maze3D::Maze3D(){
    SetPatterns();

	/* Set suface color */
	baseColor.r = 0;
	baseColor.g = 0;
	baseColor.b = 175;
}

/* Set up the graphics bit map */
void Maze3D::SetPatterns() {
	
	smallPatternSize = 3;
	largePatternSize = 14;
    char pPell[] =
    {
        "..."
        ".0."
        "..."
    };
    char pSuperPell[] =
    {
        ".............."
        ".............."
        ".............."
        ".....1000....."
        "....110000...."
        "...11000000..."
        "...11000000..."
        "...11000000..."
        "...11000000..."
        "....110000...."
        ".....1000....."
        ".............."
        ".............."
    };
    char pPacMan[] =
    {
        ".....44444...."
        "...444444444.."
        "..44444444444."
        "..444444444444"
        ".4444444444..."
        ".44444444....."
        ".444444......."
        ".444444......."
        ".44444444....."
        ".4444444444..."
        "..444444444444"
        "..44444444444."
        "...444444444.."
        ".....44444...."
    };
    char pCherry[] =
    {
        ".............."
        "............22"
        "..........2222"
        "........22.2.."
        ".......2...2.."
        "..11112...2..."
        ".1111211.2...."
        ".111111.1211.."
        ".10111.112111."
        ".11011.111111."
        "..1111.101111."
        ".......110111."
        "........1111.."
    };
    char pGhostLeft[] =
    {
        ".....____....."
        "...________..."
        "..__________.."
        "._11____11___."
        ".2211__2211__."
        ".2211__2211__."
        "_2211__2211___"
        "__11____11____"
        "______________"
        "______________"
        "______________"
        "______________"
        "__.___..___.__"
        "_...__..__..._"
    };
    char pGhostRight[] =
    {
        ".....____....."
        "...________..."
        "..__________.."
        ".___11____11_."
        ".__1122__1122."
        ".__1122__1122."
        "___1122__1122_"
        "____11____11__"
        "______________"
        "______________"
        "______________"
        "______________"
        "__.___..___.__"
        "_...__..__..._"
    };
    char pGhostUp[] =
    {
        ".....____....."
        "...________..."
        ".._22____22_.."
        "._1221__1221_."
        "._1221__1221_."
        "__1111__1111__"
        "___11____11___"
        "______________"
        "______________"
        "______________"
        "______________"
        "______________"
        "__.___..___.__"
        "_...__..__..._"
    };
    char pGhostDown[] =
    {
        ".....____....."
        "...________..."
        "..__________.."
        "._11____11___."
        ".1111__1111__."
        ".1221__1221__."
        "_1221__1221___"
        "__22____22____"
        "______________"
        "______________"
        "______________"
        "______________"
        "__.___..___.__"
        "_...__..__..._"
    };
    char pVulnerableGhost[] =
    {
        ".....____....."
        "...________..."
        "..__________.."
        ".__11____11__."
        "._1111__1111_."
        ".__11____11__."
        "______________"
        "______________"
        "__111____111__"
        "_111111111111_"
        "_1___1111___1_"
        "______________"
        "__.___..___.__"
        "_...__..__..._"
    };

    for(int i = 0;i < 9;i++) {
        patternPell[i] = pPell[i];
    }

    for(int i = 0;i < 196;i++) {
        patternSuperPell[i]       = pSuperPell[i];
        patternPacMan[i]          = pPacMan[i];
        patternCherry[i]          = pCherry[i];
        patternGhostUp[i]         = pGhostUp[i];
        patternGhostDown[i]       = pGhostDown[i];
        patternGhostLeft[i]       = pGhostLeft[i];
        patternGhostRight[i]      = pGhostRight[i];
        patternVulnerableGhost[i] = pVulnerableGhost[i];
    }
}

/* Set each surface's origin point and x y vector in global frame */
void Maze3D::SetOrientation(char orient){
    switch(orient){
        case SURFACE_T:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z = -blockNumber*blockSize3D*0.5;
            xDir.x   =  1;
            xDir.y   =  0;
            xDir.z   =  0;
            yDir.x   =  0;
            yDir.y   =  0;
            yDir.z   =  1;
            break;
        case SURFACE_B:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y = -blockNumber*blockSize3D*0.5;
            origin.z =  blockNumber*blockSize3D*0.5;
            xDir.x   =  1;
            xDir.y   =  0;
            xDir.z   =  0;
            yDir.x   =  0;
            yDir.y   =  0;
            yDir.z   = -1;
            break;
        case SURFACE_N:
            origin.x =  blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z = -blockNumber*blockSize3D*0.5;
            xDir.x   = -1;
            xDir.y   =  0;
            xDir.z   =  0;
            yDir.x   =  0;
            yDir.y   = -1;
            yDir.z   =  0;
            break;
        case SURFACE_W:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z = -blockNumber*blockSize3D*0.5;
            xDir.x   =  0;
            xDir.y   =  0;
            xDir.z   =  1;
            yDir.x   =  0;
            yDir.y   = -1;
            yDir.z   =  0;
            break;
        case SURFACE_S:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z =  blockNumber*blockSize3D*0.5;
            xDir.x   =  1;
            xDir.y   =  0;
            xDir.z   =  0;
            yDir.x   =  0;
            yDir.y   = -1;
            yDir.z   =  0;
            break;
        case SURFACE_E:
            origin.x =  blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z =  blockNumber*blockSize3D*0.5;
            xDir.x   =  0;
            xDir.y   =  0;
            xDir.z   = -1;
            yDir.x   =  0;
            yDir.y   = -1;
            yDir.z   =  0;
            break;
    }
}


void Maze3D::DrawBackground(int x, int y){
	
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(origin.x + xDir.x*blockSize3D*x     + yDir.x*blockSize3D*y,
			   origin.y + xDir.y*blockSize3D*x     + yDir.y*blockSize3D*y,
			   origin.z + xDir.z*blockSize3D*x     + yDir.z*blockSize3D*y    );
	glVertex3d(origin.x + xDir.x*blockSize3D*(x+1) + yDir.x*blockSize3D*y,
			   origin.y + xDir.y*blockSize3D*(x+1) + yDir.y*blockSize3D*y,
		       origin.z + xDir.z*blockSize3D*(x+1) + yDir.z*blockSize3D*y    );
	glVertex3d(origin.x + xDir.x*blockSize3D*(x+1) + yDir.x*blockSize3D*(y+1),
			   origin.y + xDir.y*blockSize3D*(x+1) + yDir.y*blockSize3D*(y+1),
			   origin.z + xDir.z*blockSize3D*(x+1) + yDir.z*blockSize3D*(y+1));
	glVertex3d(origin.x + xDir.x*blockSize3D*x     + yDir.x*blockSize3D*(y+1),
			   origin.y + xDir.y*blockSize3D*x     + yDir.y*blockSize3D*(y+1),
			   origin.z + xDir.z*blockSize3D*x     + yDir.z*blockSize3D*(y+1));
	glEnd();

}

void Maze3D::DrawWall(int x, int y){
	
	glColor3ub(baseColor.r, baseColor.g, baseColor.b);
	glBegin(GL_QUADS);
	glVertex3d(origin.x + xDir.x*blockSize3D*x     + yDir.x*blockSize3D*y,
			   origin.y + xDir.y*blockSize3D*x     + yDir.y*blockSize3D*y,
			   origin.z + xDir.z*blockSize3D*x     + yDir.z*blockSize3D*y    );
	glVertex3d(origin.x + xDir.x*blockSize3D*(x+1) + yDir.x*blockSize3D*y,
			   origin.y + xDir.y*blockSize3D*(x+1) + yDir.y*blockSize3D*y,
		       origin.z + xDir.z*blockSize3D*(x+1) + yDir.z*blockSize3D*y    );
	glVertex3d(origin.x + xDir.x*blockSize3D*(x+1) + yDir.x*blockSize3D*(y+1),
			   origin.y + xDir.y*blockSize3D*(x+1) + yDir.y*blockSize3D*(y+1),
			   origin.z + xDir.z*blockSize3D*(x+1) + yDir.z*blockSize3D*(y+1));
	glVertex3d(origin.x + xDir.x*blockSize3D*x     + yDir.x*blockSize3D*(y+1),
			   origin.y + xDir.y*blockSize3D*x     + yDir.y*blockSize3D*(y+1),
			   origin.z + xDir.z*blockSize3D*x     + yDir.z*blockSize3D*(y+1));
	glEnd();
}

void Maze3D::DrawBit(double drawX, double drawY, double drawZ, double unit, int i, int j){
	double x2D, y2D;
	x2D = unit * (double)j;
	y2D = unit * (double)i;
	glBegin(GL_QUADS);
	glVertex3d(drawX + (x2D       ) * xDir.x + (y2D       ) * yDir.x,
			   drawY + (x2D       ) * xDir.y + (y2D       ) * yDir.y,
			   drawZ + (x2D       ) * xDir.z + (y2D       ) * yDir.z );
	glVertex3d(drawX + (x2D + unit) * xDir.x + (y2D       ) * yDir.x,
			   drawY + (x2D + unit) * xDir.y + (y2D       ) * yDir.y,
			   drawZ + (x2D + unit) * xDir.z + (y2D       ) * yDir.z );
	glVertex3d(drawX + (x2D + unit) * xDir.x + (y2D + unit) * yDir.x,
			   drawY + (x2D + unit) * xDir.y + (y2D + unit) * yDir.y,
			   drawZ + (x2D + unit) * xDir.z + (y2D + unit) * yDir.z );
	glVertex3d(drawX + (x2D       ) * xDir.x + (y2D + unit) * yDir.x,
			   drawY + (x2D       ) * xDir.y + (y2D + unit) * yDir.y,
			   drawZ + (x2D       ) * xDir.z + (y2D + unit) * yDir.z );
	glEnd();

}

void Maze3D::DrawPell(int x, int y){
	
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
    
    double unit = double(blockSize3D)/double(smallPatternSize); // stride size 
    for(int i = 0;i < smallPatternSize;i++){
		for(int j = 0;j < smallPatternSize;j++){
			int bit = i*smallPatternSize + j;
            if (patternPell[bit] == '0') glColor3ub(255,255,255);
            else glColor3ub(0,0,0);
			DrawBit(drawX, drawY, drawZ, unit, i, j);
		}
	}
}

void Maze3D::DrawSuperPell(int x, int y){
	/* Calculate the origin point of this maze block in global frame */
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
   	
	/* Draw each pixel stride */
    double unit = double(blockSize3D)/double(largePatternSize); // stride size 
	
	for(int i = 0;i < largePatternSize;i++){
		for(int j = 0;j < largePatternSize;j++){
			int bit = largePatternSize*i + j;
			switch(patternSuperPell[bit]){
				case '0':
					glColor3ub(255, 255, 50);
					break;
				case '1':
					glColor3ub(255, 155, 50);
					break;
				default:
					glColor3ub(0, 0, 0);
					break;
			}
			DrawBit(drawX, drawY, drawZ, unit, i, j);
		}
	}
}
void Maze3D::DrawCherry(int x, int y){
	/* Calculate the origin point of this maze block in global frame */
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
   	
	/* Draw each pixel stride */
    double unit = double(blockSize3D)/double(largePatternSize); // stride size 
	
	for(int i = 0;i < largePatternSize;i++){
		for(int j = 0;j < largePatternSize;j++){
			/* Determine bit color */
			int bit = largePatternSize*i + j;
			if(patternCherry[bit] == '0') glColor3ub(255, 255, 255);
			else if(patternCherry[bit] == '1') glColor3ub(242, 0, 255);
			else if(patternCherry[bit] == '2') glColor3ub(170, 138, 67);
			else glColor3ub(0, 0, 0);	
			DrawBit(drawX, drawY, drawZ, unit, i, j);

		}
	}
}

void Maze3D::DrawMaze(int x, int y, int input){

	switch(input){
		case MAZE_EMPTY:
			DrawBackground(x, y);
			break;
		case MAZE_WALL:
			DrawWall(x, y);
			break;
		case MAZE_PELL:
			DrawPell(x, y);
			break;
		case MAZE_SUPERPELL:
			DrawSuperPell(x, y);
			break;
		case MAZE_CHERRY:
			DrawCherry(x, y);
			break;
	}
}

void Maze3D::DrawPacman(Agent &pacman){
	/* Load coordinates */
	double x = pacman.x;
	double y = pacman.y;
	int xdir, ydir;
	Dir2XY(pacman.dir, xdir, ydir);

	/* Origin Point of the graph */
	double drawX, drawY, drawZ;
	drawX = (double)(origin.x + xDir.x*blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y*blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z*blockSize3D * x + yDir.z * blockSize3D * y);
    
    double unit = double(blockSize3D)/double(largePatternSize); // stride size 
   	
	for(int i = 0;i < largePatternSize;i++){
		for(int j = 0;j < largePatternSize;j++){
			int bit, row, col;
			/* Rotate the pacman pattern */
			switch(pacman.dir){
				case DIR_LEFT:
					row = i;
					col = largePatternSize - j;
					break;
				case DIR_DOWN:
					row = j;
					col = i;
					break;
				case DIR_UP:
					row = j;
					col = largePatternSize - i;
					break;
				default:
					row = i;
					col = j;
			}
			bit = largePatternSize * row + col;
            if (patternPacMan[bit] == '4') glColor3ub(255, 255, 0);
            else glColor3ub(0, 0, 0);
			DrawBit(drawX, drawY, drawZ, unit, i, j);
		}
	}
}

void Maze3D::DrawGhost(Agent &ghost, bool powerState){
	/* Load coordinates */
	int x = ghost.x;
	int y = ghost.y;

	/* Origin Point of the graph */
	double drawX, drawY, drawZ;
	drawX = (double)(origin.x + xDir.x*blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y*blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z*blockSize3D * x + yDir.z * blockSize3D * y);
	
	/* Draw each pixel stride */
    double unit = double(blockSize3D)/double(largePatternSize); // stride size 
	
	for(int i = 0;i < largePatternSize;i++){
		for(int j = 0;j < largePatternSize;j++){
			int bit = largePatternSize*i + j;
            if (powerState){
                /* Draw Vulnerable ghost */
				if(patternVulnerableGhost[bit] == '_') glColor3ub(150, 0, 255);
                else if(patternVulnerableGhost[bit] == '1') glColor3ub(0, 0, 0);
                else glColor3ub(0, 0, 0);
            }
            else{
				/* Draw normal ghost, first determine direction */	
				char* ghostPattern;
				switch(ghost.dir){
					case DIR_UP:
						ghostPattern = patternGhostUp;
						break;
					case DIR_LEFT:
						ghostPattern = patternGhostLeft;
						break;
					case DIR_RIGHT:
						ghostPattern = patternGhostRight;
						break;
					case DIR_DOWN:
						ghostPattern = patternGhostDown;
						break;
					default:
						ghostPattern = patternGhostDown;
				}
				if(ghostPattern[bit] == '_') glColor3ub(255, 0, 0);
				else if(ghostPattern[bit] == '1') glColor3ub(255, 255, 255);
				else if(ghostPattern[bit] == '2') glColor3ub(0, 0, 255);
				else glColor3ub(0, 0, 255);
            }
			
			DrawBit(drawX, drawY, drawZ, unit, i, j);
		}
	}
}

class FullMaze3D{
    private:
        Maze3D maze[6]; /* 6 surface maze */
    	bool powerState;
	public:
        FullMaze3D();
		/* Drawing function */
		void DrawPacman(Agent &pacman);
		void DrawGhost(vector<Agent> &ghost);
		void DrawMaze(Maze* fullMaze);
		void DrawMaze(int*** fullMaze);
		
		void ActivatePowerState();
};

FullMaze3D::FullMaze3D(){
	/* Set up the six surface orientation and vector */    
	maze[SURFACE_T].SetOrientation(SURFACE_T);
	maze[SURFACE_N].SetOrientation(SURFACE_N);
	maze[SURFACE_W].SetOrientation(SURFACE_W);
	maze[SURFACE_S].SetOrientation(SURFACE_S);
	maze[SURFACE_E].SetOrientation(SURFACE_E);
	maze[SURFACE_B].SetOrientation(SURFACE_B);
	powerState = false;
}

void FullMaze3D::ActivatePowerState(){
	powerState = true;
}

void FullMaze3D::DrawPacman(Agent &pacman){
	int surface = pacman.surface;
	maze[surface].DrawPacman(pacman);
}

void FullMaze3D::DrawGhost(vector<Agent> &ghost){
	int n = ghost.size();
	for(int i = 0;i < n;i++){
		int surface = ghost[i].surface;
		maze[surface].DrawGhost(ghost[i], powerState);
	}
}

void FullMaze3D::DrawMaze(Maze* fullMaze){
	for(int i = 0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			for(int k = 0;k < blockNumber;k++){
				maze[i].DrawMaze(k, j, fullMaze[i].ReturnElement(k,j));
			}
		}
	}
}

void FullMaze3D::DrawMaze(int*** fullMaze){
	for(int i = 0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			for(int k = 0;k < blockNumber;k++){
				maze[i].DrawMaze(k, j, fullMaze[i][k][j]);
			}
		}
	}
}
#endif
