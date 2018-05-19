#ifndef MAZE3D_H
#define MAZE3D_H

#include "maze.h"
using namespace std;

extern int blockSize3D; // Giada's Modification
extern const int blockNumber;
extern double myPi;


typedef struct CursorStruct_3D{
    int x;
    int y;
    int z;
    int xdir;
    int ydir;
    bool powerState = false;
}Coord_3D;

class Maze3D{
protected:
    int **maze;
    
	Vector origin;
    Vector xDir;
    Vector yDir;

    int curState; // 0 not in this surface, 1 not clear box, 2 clear box
    char orientation;
    Color baseColor; // R,G,B
	


public:
    Coord_3D cursor;
    vector<Agent> ghost;
    Maze3D();
    ~Maze3D();
    void SetPatterns();
    void SetMaze(int,int,int);
    void SetOrientation(char);
    void Draw3D();
    void DrawPell(double,double,double);
    void DrawSuperPell(double,double,double);
    void DrawCherry(double,double,double);
    void DrawPacman(double,double,double);
	void DrawGhost(double,double,double,int,int);
    
	/* Below is mine */
	void DrawPacman(Agent &pacman);
	void DrawGhost(Agent &ghost, bool powerState);

	
	
	/* Cube Drawing */
    void DrawMaze(int x, int y, int input);
	void DrawBackground(int x, int y);
	void DrawWall(int x, int y);
	void DrawPell(int x, int y);
	void DrawSuperPell(int x, int y);
	void DrawCherry(int x, int y);	
	
	
	void Activate(Coord_3D,int);// give cursor coordinates and state
    void Deactivate();

    char patternPell[9];
    char patternSuperPell[196];
    char patternPacMan[196];
    char patternCherry[196];
    char patternGhostLeft[196];
    char patternGhostRight[196];
    char patternGhostUp[196];
    char patternGhostDown[196];
    char patternVulnerableGhost[196];
};

Maze3D::Maze3D(){
    SetPatterns();
    maze = new int*[blockNumber];
    for(int i = 0;i < blockNumber;i++){
        maze[i] = new int [blockNumber];
    }
    curState = 0;
    for(int i = 0;i < blockNumber;i++){
        for(int j = 0;j < blockNumber;j++){
            maze[i][j] = 1;
        }
    }

	/* Set suface color */
	baseColor.r = 0;
	baseColor.g = 0;
	baseColor.b = 175;
}

Maze3D::~Maze3D(){
    for(int i = 0;i < blockNumber;i++){
        delete [] maze[i];
    }
    delete [] maze;
}

void Maze3D::SetPatterns() {

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

    int i;
    for(i = 0;i < 9;i++) {
        patternPell[i] = pPell[i];
    }

    for(i = 0;i < 196;i++) {
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

void Maze3D::SetMaze(int i,int j,int input){
    maze[i][j] = input;
}

void Maze3D::SetOrientation(char orient){
    orientation = orient;

    switch(orient){
        case SURFACE_T:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z = -blockNumber*blockSize3D*0.5;
            xDir.x   = 1;
            xDir.y   = 0;
            xDir.z   = 0;
            yDir.x   = 0;
            yDir.y   = 0;
            yDir.z   = 1;

            break;
        case SURFACE_B:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y = -blockNumber*blockSize3D*0.5;
            origin.z =  blockNumber*blockSize3D*0.5;
            xDir.x   = 1;
            xDir.y   = 0;
            xDir.z   = 0;
            yDir.x   = 0;
            yDir.y   = 0;
            yDir.z   = -1;
            break;
        case SURFACE_N:
            origin.x =  (blockNumber  )*blockSize3D*0.5;
            origin.y =  (blockNumber  )*blockSize3D*0.5;
            origin.z = -(blockNumber)*blockSize3D*0.5;
            xDir.x   = -1;
            xDir.y   = 0;
            xDir.z   = 0;
            yDir.x   = 0;
            yDir.y   = -1;
            yDir.z   = 0;
            break;
        case SURFACE_W:
            origin.x = -blockNumber*blockSize3D*0.5;
            origin.y =  blockNumber*blockSize3D*0.5;
            origin.z = -blockNumber*blockSize3D*0.5;
            xDir.x   = 0;
            xDir.y   = 0;
            xDir.z   = 1;
            yDir.x   = 0;
            yDir.y   = -1;
            yDir.z   = 0;
            break;
        case SURFACE_S:
            origin.x = -(blockNumber)*blockSize3D*0.5;
            origin.y =  (blockNumber)*blockSize3D*0.5;
            origin.z =  (blockNumber)*blockSize3D*0.5;
            xDir.x   = 1;
            xDir.y   = 0;
            xDir.z   = 0;
            yDir.x   = 0;
            yDir.y   = -1;
            yDir.z   = 0;
            break;
        case SURFACE_E:
            origin.x = (blockNumber)*blockSize3D*0.5;
            origin.y = (blockNumber)*blockSize3D*0.5;
            origin.z = (blockNumber)*blockSize3D*0.5;
            xDir.x   = 0;
            xDir.y   = 0;
            xDir.z   = -1;
            yDir.x   = 0;
            yDir.y   = -1;
            yDir.z   = 0;
            break;

    }
}

void Maze3D::Activate(Coord_3D cur,int state){
    cursor.x = cur.x;
    cursor.y = cur.y;
    cursor.xdir = cur.xdir;
    cursor.ydir = cur.ydir;
    curState = state;
    if(curState == 2){
        maze[cursor.x][cursor.y] = 0;
    }
    if(curState == 3){
        maze[cursor.x][cursor.y] = 1;
    }
}

void Maze3D::Deactivate(){
    curState = 0;
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


void Maze3D::DrawPell(int x, int y){
	
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
    
	double x_2D, y_2D;
    double unit = 2.333334;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=unit) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=unit) {
            int bit = (int)((x_2D/unit)+((y_2D/unit)*3));
            if (patternPell[bit] == '0') glColor3ub(255,255,255);
            else glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D + unit) * yDir.z );
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D + unit) * yDir.z );
            glEnd();
        }
    }
}

void Maze3D::DrawSuperPell(int x, int y){
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
    double x_2D, y_2D;
    double unit = 0.5;
	for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=unit) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=unit) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
            if      (patternSuperPell[bit] == '0') glColor3ub(255,255,50);
            else if (patternSuperPell[bit] == '1') glColor3ub(255,155,50);
            else glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D + unit) * yDir.z );
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D + unit) * yDir.z );
            glEnd();
        }
    }
}
void Maze3D::DrawCherry(int x, int y){
	
	double drawX, drawY, drawZ;	
	drawX = (double)(origin.x + xDir.x * blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y * blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z * blockSize3D * x + yDir.z * blockSize3D * y);
    double x_2D, y_2D;
    double unit = 0.5;
	for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=unit) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=unit) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
			/* Choose color */
			if      (patternCherry[bit] == '0') glColor3ub(255,255,255);
            else if (patternCherry[bit] == '1') glColor3ub(242,  0,  0);
            else if (patternCherry[bit] == '2') glColor3ub(170,138, 67);
            else glColor3ub(0,0,0);
            
			
			glBegin(GL_QUADS);
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D       ) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D       ) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D       ) * yDir.z );
            glVertex3d(drawX + (x_2D + unit) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D + unit) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D + unit) * xDir.z + (y_2D + unit) * yDir.z );
            glVertex3d(drawX + (x_2D       ) * xDir.x + (y_2D + unit) * yDir.x,
                       drawY + (x_2D       ) * xDir.y + (y_2D + unit) * yDir.y,
                       drawZ + (x_2D       ) * xDir.z + (y_2D + unit) * yDir.z );
            glEnd();
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
    
	double x_2D, y_2D;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            double i=x_2D, j=y_2D;
            if (xdir == -1 && ydir == 0) { // left
                i = (blockSize3D-0.5) - x_2D;
                j = y_2D;
            }
            else if (xdir == 0 && ydir == 1) { // up
                i = y_2D;
                j = (blockSize3D-0.5) - x_2D;
            }
            else if (xdir == 0 && ydir == -1) { // down
                i = (blockSize3D-0.5) - y_2D;
                j = (blockSize3D-0.5) - x_2D;
            }

            int bit = (int)((i*2)+((j*2)*14));
            if (patternPacMan[bit] == '4') glColor3ub(255,255,  0);
            else                                  glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
	
}

void Maze3D::DrawGhost(Agent &ghost, bool powerState){
	/* Load coordinates */
	int x = ghost.x;
	int y = ghost.y;
	int xdir, ydir;
	Dir2XY(ghost.dir, xdir, ydir);


	/* Origin Point of the graph */
	double drawX, drawY, drawZ;
	drawX = (double)(origin.x + xDir.x*blockSize3D * x + yDir.x * blockSize3D * y);
	drawY = (double)(origin.y + xDir.y*blockSize3D * x + yDir.y * blockSize3D * y);
	drawZ = (double)(origin.z + xDir.z*blockSize3D * x + yDir.z * blockSize3D * y);
    
	double x_2D, y_2D;

    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
            if (powerState) {
                if      (patternVulnerableGhost[bit] == '_') glColor3ub(150,  0,255);
                else if (patternVulnerableGhost[bit] == '1') glColor3ub(  0,  0,  0);
                else glColor3ub(0,0,0);
            }
            else {
                if      ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '_') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '_') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '_') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '_') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '_')) {
                    glColor3ub(255,  0,  0);
                }
                else if ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '1') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '1') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '1') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '1') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '1')) {
                    glColor3ub(255,255,255);
                }
                else if ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '2') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '2') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '2') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '2') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '2')) {
                    glColor3ub(  0,  0,255);
                }
                else glColor3ub(0,0,0);
            }

            glBegin(GL_QUADS);
            glVertex3d(drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                       drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                       drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d(drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                       drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                       drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d(drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                       drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                       drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d(drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                       drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                       drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
}

void Maze3D::Draw3D()
{
    double x,y,z;
    //int surface;
    //int gx,gy;

    for(int i = 0;i < blockNumber;i++){
        for(int j = 0;j < blockNumber;j++){

            x = (double)(origin.x + xDir.x*blockSize3D*i + yDir.x*blockSize3D*j);
            y = (double)(origin.y + xDir.y*blockSize3D*i + yDir.y*blockSize3D*j);
            z = (double)(origin.z + xDir.z*blockSize3D*i + yDir.z*blockSize3D*j);

            //if (curState > 0 && cursor.x == i && cursor.y == j) DrawPacman(x,y,z);
			if(1 == 100) cout << "shutup" << endl;
            else {
                if (maze[i][j] == MAZE_WALL) {
                    glColor3ub(baseColor.r, baseColor.g, baseColor.b);
                    glBegin(GL_QUADS);
                    glVertex3d(origin.x + xDir.x*blockSize3D*i     + yDir.x*blockSize3D*j,
                               origin.y + xDir.y*blockSize3D*i     + yDir.y*blockSize3D*j,
                               origin.z + xDir.z*blockSize3D*i     + yDir.z*blockSize3D*j    );
                    glVertex3d(origin.x + xDir.x*blockSize3D*(i+1) + yDir.x*blockSize3D*j,
                               origin.y + xDir.y*blockSize3D*(i+1) + yDir.y*blockSize3D*j,
                               origin.z + xDir.z*blockSize3D*(i+1) + yDir.z*blockSize3D*j    );
                    glVertex3d(origin.x + xDir.x*blockSize3D*(i+1) + yDir.x*blockSize3D*(j+1),
                               origin.y + xDir.y*blockSize3D*(i+1) + yDir.y*blockSize3D*(j+1),
                               origin.z + xDir.z*blockSize3D*(i+1) + yDir.z*blockSize3D*(j+1));
                    glVertex3d(origin.x + xDir.x*blockSize3D*i     + yDir.x*blockSize3D*(j+1),
                               origin.y + xDir.y*blockSize3D*i     + yDir.y*blockSize3D*(j+1),
                               origin.z + xDir.z*blockSize3D*i     + yDir.z*blockSize3D*(j+1));
                    glEnd();
                }
                else if (maze[i][j] == MAZE_PELL) DrawPell(x,y,z);
                else if (maze[i][j] == MAZE_SUPERPELL) DrawSuperPell(x,y,z);
                else if (maze[i][j] == MAZE_CHERRY) DrawCherry(x,y,z);
                else if (maze[i][j] == MAZE_EMPTY) {
                    glColor3ub(0,0,0);
                    glBegin(GL_QUADS);
                    glVertex3d(origin.x + xDir.x*blockSize3D*i     + yDir.x*blockSize3D*j,
                               origin.y + xDir.y*blockSize3D*i     + yDir.y*blockSize3D*j,
                               origin.z + xDir.z*blockSize3D*i     + yDir.z*blockSize3D*j    );
                    glVertex3d(origin.x + xDir.x*blockSize3D*(i+1) + yDir.x*blockSize3D*j,
                              origin.y + xDir.y*blockSize3D*(i+1) + yDir.y*blockSize3D*j,
                              origin.z + xDir.z*blockSize3D*(i+1) + yDir.z*blockSize3D*j    );
                    glVertex3d(origin.x + xDir.x*blockSize3D*(i+1) + yDir.x*blockSize3D*(j+1),
                               origin.y + xDir.y*blockSize3D*(i+1) + yDir.y*blockSize3D*(j+1),
                               origin.z + xDir.z*blockSize3D*(i+1) + yDir.z*blockSize3D*(j+1));
                    glVertex3d(origin.x + xDir.x*blockSize3D*i     + yDir.x*blockSize3D*(j+1),
                               origin.y + xDir.y*blockSize3D*i     + yDir.y*blockSize3D*(j+1),
                               origin.z + xDir.z*blockSize3D*i     + yDir.z*blockSize3D*(j+1));
                    glEnd();
                }
            }

            for(int n=0; n < ghost.size(); n++) {
                int i = ghost[n].x;
                int j = ghost[n].y;

                x = (double)(origin.x + xDir.x*blockSize3D*i + yDir.x*blockSize3D*j);
                y = (double)(origin.y + xDir.y*blockSize3D*i + yDir.y*blockSize3D*j);
                z = (double)(origin.z + xDir.z*blockSize3D*i + yDir.z*blockSize3D*j);

                switch(orientation){
                    case 'T':
                        y += 0.75;
                        break;
                    case 'B':
                        y -= 0.75;
                        break;
                    case 'N':
                        z -= 0.75;
                        break;
                    case 'W':
                        x -= 0.75;
                        break;
                    case 'S':
                        z += 0.75;
                        break;
                    case 'E':
                        x += 0.75;
                        break;
                }
                int dir = ghost[n].dir;
                int xdir, ydir;
                switch(dir){
                    case DIR_RIGHT:
                        xdir = 1;
                        ydir = 0;
                        break;
                    case DIR_DOWN:
                        xdir = 0;
                        ydir = 1;
                        break;
                    case DIR_UP:
                        xdir = 0;
                        ydir = -1;
                        break;
                    case DIR_LEFT:
                        xdir = -1;
                        ydir = 0;
                        break;
                    default:
                        xdir = 1;
                        ydir = 0;
                        break;
                }
                DrawGhost(x, y, z, xdir, ydir);
            }
        }
    }
}

void Maze3D::DrawPell(double drawX, double drawY, double drawZ) {
    double x_2D, y_2D;
    double unit = 2.333334;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=unit) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=unit) {
            int bit = (int)((x_2D/unit)+((y_2D/unit)*3));
            if (patternPell[bit] == '0') glColor3ub(255,255,255);
            else glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d( drawX + (x_2D  )*xDir.x + (y_2D  )*yDir.x,
                    drawY + (x_2D  )*xDir.y + (y_2D  )*yDir.y,
                    drawZ + (x_2D  )*xDir.z + (y_2D  )*yDir.z  );
            glVertex3d( drawX + (x_2D+unit)*xDir.x + (y_2D  )*yDir.x,
                    drawY + (x_2D+unit)*xDir.y + (y_2D  )*yDir.y,
                    drawZ + (x_2D+unit)*xDir.z + (y_2D  )*yDir.z  );
            glVertex3d( drawX + (x_2D+unit)*xDir.x + (y_2D+unit)*yDir.x,
                    drawY + (x_2D+unit)*xDir.y + (y_2D+unit)*yDir.y,
                    drawZ + (x_2D+unit)*xDir.z + (y_2D+unit)*yDir.z  );
            glVertex3d( drawX + (x_2D  )*xDir.x + (y_2D+unit)*yDir.x,
                    drawY + (x_2D  )*xDir.y + (y_2D+unit)*yDir.y,
                    drawZ + (x_2D  )*xDir.z + (y_2D+unit)*yDir.z  );
            glEnd();
        }
    }
}

void Maze3D::DrawSuperPell(double drawX, double drawY, double drawZ) {
    double x_2D, y_2D;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
            if      (patternSuperPell[bit] == '0') glColor3ub(255,255,50);
            else if (patternSuperPell[bit] == '1') glColor3ub(255,155,50);
            else glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
}

void Maze3D::DrawCherry(double drawX, double drawY, double drawZ) {
    double x_2D, y_2D;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
            if      (patternCherry[bit] == '0') glColor3ub(255,255,255);
            else if (patternCherry[bit] == '1') glColor3ub(242,  0,  0);
            else if (patternCherry[bit] == '2') glColor3ub(170,138, 67);
            else glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
}

void Maze3D::DrawPacman(double drawX, double drawY, double drawZ) {
    double x_2D, y_2D;
    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            double i=x_2D, j=y_2D;
            if (cursor.xdir == -1 && cursor.ydir == 0) { // left
                i = (blockSize3D-0.5) - x_2D;
                j = y_2D;
            }
            else if (cursor.xdir == 0 && cursor.ydir == 1) { // up
                i = y_2D;
                j = (blockSize3D-0.5) - x_2D;
            }
            else if (cursor.xdir == 0 && cursor.ydir == -1) { // down
                i = (blockSize3D-0.5) - y_2D;
                j = (blockSize3D-0.5) - x_2D;
            }

            int bit = (int)((i*2)+((j*2)*14));
            if (patternPacMan[bit] == '4') glColor3ub(255,255,  0);
            else                                  glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d( drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d( drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                    drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                    drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
}





void Maze3D::DrawGhost(double drawX, double drawY, double drawZ, int xdir, int ydir) {
    double x_2D, y_2D;

    for (y_2D = 0.0; y_2D < blockSize3D; y_2D+=0.5) {
        for (x_2D = 0.0; x_2D < blockSize3D; x_2D+=0.5) {
            int bit = (int)((x_2D*2)+((y_2D*2)*14));
            if (cursor.powerState) {
                if      (patternVulnerableGhost[bit] == '_') glColor3ub(150,  0,255);
                else if (patternVulnerableGhost[bit] == '1') glColor3ub(  0,  0,  0);
                else glColor3ub(0,0,0);
            }
            else {
                if      ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '_') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '_') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '_') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '_') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '_')) {
                    glColor3ub(255,  0,  0);
                }
                else if ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '1') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '1') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '1') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '1') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '1')) {
                    glColor3ub(255,255,255);
                }
                else if ((xdir == -1 && ydir ==  0 && patternGhostLeft[bit]  == '2') ||
                        (xdir ==  1 && ydir ==  0 && patternGhostRight[bit] == '2') ||
                        (xdir ==  0 && ydir == -1 && patternGhostUp[bit]    == '2') ||
                        (xdir ==  0 && ydir ==  1 && patternGhostDown[bit]  == '2') ||
                        (xdir ==  0 && ydir ==  0 && patternGhostRight[bit] == '2')) {
                    glColor3ub(  0,  0,255);
                }
                else glColor3ub(0,0,0);
            }

            glBegin(GL_QUADS);
            glVertex3d(drawX + (x_2D    )*xDir.x + (y_2D    )*yDir.x,
                       drawY + (x_2D    )*xDir.y + (y_2D    )*yDir.y,
                       drawZ + (x_2D    )*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d(drawX + (x_2D+0.5)*xDir.x + (y_2D    )*yDir.x,
                       drawY + (x_2D+0.5)*xDir.y + (y_2D    )*yDir.y,
                       drawZ + (x_2D+0.5)*xDir.z + (y_2D    )*yDir.z  );
            glVertex3d(drawX + (x_2D+0.5)*xDir.x + (y_2D+0.5)*yDir.x,
                       drawY + (x_2D+0.5)*xDir.y + (y_2D+0.5)*yDir.y,
                       drawZ + (x_2D+0.5)*xDir.z + (y_2D+0.5)*yDir.z  );
            glVertex3d(drawX + (x_2D    )*xDir.x + (y_2D+0.5)*yDir.x,
                       drawY + (x_2D    )*xDir.y + (y_2D+0.5)*yDir.y,
                       drawZ + (x_2D    )*xDir.z + (y_2D+0.5)*yDir.z  );
            glEnd();
        }
    }
}

class FullMaze3D{
    private:
        Maze3D maze[6]; /* 6 surface maze */
        Coord_3D cursor;
        char curSurface;
        int curState; // 1 for not clear, 2 for clear box
    	bool powerState;
	public:
        FullMaze3D();
        void Draw();
        void SetMaze(int ***);
        void SetPacman(Agent);
        void SetGhost(vector<Agent> *ghostInfo);
		
		/* Drawing function */
		void DrawMaze(int *** fullMaze);
		void DrawPacman(Agent &pacman);
		void DrawGhost(vector<Agent> &ghost);
		void DrawMaze(Maze* fullMaze);

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


void FullMaze3D::SetGhost(vector<Agent> *ghostInfo){
    int n = ghostInfo->size();
    for(int i = 0;i < 6;i++){
        maze[i].ghost.clear();
    }
    for(int i = 0;i < n;i++){
        int surface = ghostInfo->at(i).surface;
        maze[surface].ghost.push_back(ghostInfo->at(i));
    }
}

void FullMaze3D::SetPacman(Agent pacman){
    switch(pacman.surface){
        case 0:
            curSurface = 'T';
            break;
        case 1:
            curSurface = 'N';
            break;
        case 2:
            curSurface = 'W';
            break;
        case 3:
            curSurface = 'S';
            break;
        case 4:
            curSurface = 'E';
            break;
        case 5:
            curSurface = 'B';
            break;
    }
    cursor.x    = pacman.x;
    cursor.y    = pacman.y;

    for(int i = 0;i < 6;i++){
        maze[i].Deactivate();
        maze[i].cursor.powerState = pacman.powerState;
    }

    switch(curSurface){
        case 'T':
            maze[0].Activate(cursor,curState);
            break;
        case 'N':
            maze[1].Activate(cursor,curState);
            break;
        case 'W':
            maze[2].Activate(cursor,curState);
            break;
        case 'S':V
            maze[3].Activate(cursor,curState);
            break;
        case 'E':
            maze[4].Activate(cursor,curState);
            break;
        case 'B':
            maze[5].Activate(cursor,curState);
            break;
    }
}


void FullMaze3D::Draw(){
    for(int i = 0;i < 6;i++){
        maze[i].Draw3D();
    }
}

void FullMaze3D::SetMaze(int ***input){
    for(int i = 0;i < 6;i++){
        for(int j = 0;j < blockNumber;j++){
            for(int k = 0;k < blockNumber;k++){
                maze[i].SetMaze(k,j,input[i][k][j]);
            }
        }
    }
}


void FullMaze3D::DrawMaze(int ***fullMaze){
	for(int i = 0;i < 6;i++){
		for(int j = 0;j < blockNumber;j++){
			for(int k = 0;k < blockNumber;k++){
				maze[i].DrawMaze(k, j, fullMaze[i][k][j]);
			}
		}
	}
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

#endif
