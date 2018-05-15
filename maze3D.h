#ifndef MAZE3D_H
#define MAZE3D_H

extern int blockSize_3D; // Giada's Modification
extern const int blockNumber;
extern double myPi;

typedef struct Vector3Struct{
  double x;
  double y;
  double z;
}Vector3;

typedef struct CursorStruct_3D{
  int x;
  int y;
  int z;
  int xdir;
  int ydir;
  bool powerState = false;
}Coord_3D;
/*
typedef struct ColorStruct{
  int r;
  int g;
  int b;
}Color;
*/

class Maze_3D{
  protected:
    int **maze;
    Coord_3D origin; // the (0,0) point on the global coordinates

    // Giada's Edition
    Vector3 origin3;
    Vector3 nextX;
    Vector3 nextY;

    int curState; // 0 not in this surface, 1 not clear box, 2 clear box
    char orientation;
    Color baseColor; // R,G,B

  public:
    Coord_3D cursor;
    vector<Ghost> ghost;
    Maze_3D();
    ~Maze_3D();
    void SetPatterns();
    void SetMaze(int,int,int);
    void SetOrientation(char);
    void Draw3D();
    void DrawPerl(double,double,double);
    void DrawSuperPerl(double,double,double);
    void DrawCherry(double,double,double);
    void DrawPacMan(double,double,double);
    void DrawGhost(double,double,double,int,int);
    void Print();
    void Activate(Coord_3D,int);// give cursor coordinates and state
    void Deactivate();
    const int ReturnElement(int,int)const;

    char patternPerl[9];
    char patternSuperPerl[196];
    char patternPacMan[196];
    char patternCherry[196];
    char patternGhostLeft[196];
    char patternGhostRight[196];
    char patternGhostUp[196];
    char patternGhostDown[196];
    char patternVulnerableGhost[196];
};

Maze_3D::Maze_3D(){
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
}

Maze_3D::~Maze_3D(){
  for(int i = 0;i < blockNumber;i++){
    delete [] maze[i];
  }
  delete [] maze;
}

void Maze_3D::SetPatterns() {

  char pPerl[] =
  {
    "..."
    ".0."
    "..."
  };
  char pSuperPerl[] =
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
  for(i=0; i<9; i++) {
    patternPerl[i] = pPerl[i];
  }

  for(i=0; i<196; i++) {
    patternSuperPerl[i]       = pSuperPerl[i];
    patternPacMan[i]          = pPacMan[i];
    patternCherry[i]          = pCherry[i];
    patternGhostUp[i]         = pGhostUp[i];
    patternGhostDown[i]       = pGhostDown[i];
    patternGhostLeft[i]       = pGhostLeft[i];
    patternGhostRight[i]      = pGhostRight[i];
    patternVulnerableGhost[i] = pVulnerableGhost[i];
  }
}

void Maze_3D::SetMaze(int i,int j,int input){
  maze[i][j] = input;
}

void Maze_3D::SetOrientation(char orient){
  orientation = orient;

  switch(orient){
    case 'T':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = 0;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y =  blockNumber*blockSize_3D*0.5;
      origin3.z = -blockNumber*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = 0;
      nextY.z   = 1;

      break;
    case 'B':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = 2*blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y = -blockNumber*blockSize_3D*0.5;
      origin3.z =  blockNumber*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = 0;
      nextY.z   = -1;

      break;
    case 'N':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 0;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x =  (blockNumber  )*blockSize_3D*0.5;
      origin3.y =  (blockNumber  )*blockSize_3D*0.5;
      origin3.z = -(blockNumber)*blockSize_3D*0.5;
      nextX.x   = -1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'W':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y =  blockNumber*blockSize_3D*0.5;
      origin3.z = -blockNumber*blockSize_3D*0.5;
      nextX.x   = 0;
      nextX.y   = 0;
      nextX.z   = 1;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'S':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -(blockNumber)*blockSize_3D*0.5;
      origin3.y =  (blockNumber)*blockSize_3D*0.5;
      origin3.z =  (blockNumber)*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'E':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 3*blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = (blockNumber)*blockSize_3D*0.5;
      origin3.y = (blockNumber)*blockSize_3D*0.5;
      origin3.z = (blockNumber)*blockSize_3D*0.5;
      nextX.x   = 0;
      nextX.y   = 0;
      nextX.z   = -1;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;
      break;

  }
}

const int Maze_3D::ReturnElement(int i,int j)const{
  return maze[i][j];
}

void Maze_3D::Print(){
  printf("Orientation = %c\n",orientation);
  for(int i = 0;i < blockNumber;i++){
    for(int j = 0;j < blockNumber;j++){
      printf("%d ",maze[i][j]);
    }
    printf("\n");
  }
}

void Maze_3D::Activate(Coord_3D cur,int state){
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

void Maze_3D::Deactivate(){
  curState = 0;
}

void Maze_3D::Draw3D()
{
    double x,y,z;
    //int surface;
    //int gx,gy;

    for(int i = 0;i < blockNumber;i++){
      for(int j = 0;j < blockNumber;j++){

        x = (double)(origin3.x + nextX.x*blockSize_3D*i + nextY.x*blockSize_3D*j);
        y = (double)(origin3.y + nextX.y*blockSize_3D*i + nextY.y*blockSize_3D*j);
        z = (double)(origin3.z + nextX.z*blockSize_3D*i + nextY.z*blockSize_3D*j);

        if (curState > 0 && cursor.x == i && cursor.y == j) DrawPacMan(x,y,z);

        else {
          if (maze[i][j] == 1) {
            glColor3ub(baseColor.r,baseColor.g,baseColor.b);
            glBegin(GL_QUADS);
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*(j+1));
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*(j+1));
            glEnd();
          }
          else if (maze[i][j] == 0) DrawPerl(x,y,z);
          else if (maze[i][j] == 3) DrawSuperPerl(x,y,z);
          else if (maze[i][j] == 2) DrawCherry(x,y,z);
          else if (maze[i][j] == -1) {
            glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*(j+1));
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*(j+1));
            glEnd();
          }
        }

        for(int n=0; n<ghost.size(); n++) {
          int i = ghost[n].x;
          int j = ghost[n].y;
          int xdir = ghost[n].xdir;
          int ydir = ghost[n].ydir;
          x = (double)(origin3.x + nextX.x*blockSize_3D*i + nextY.x*blockSize_3D*j);
          y = (double)(origin3.y + nextX.y*blockSize_3D*i + nextY.y*blockSize_3D*j);
          z = (double)(origin3.z + nextX.z*blockSize_3D*i + nextY.z*blockSize_3D*j);

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
          DrawGhost(x,y,z,xdir,ydir);
        }
      }
    }
}

void Maze_3D::DrawPerl(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
  double unit = 2.333334;
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=unit) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=unit) {
      int bit = (int)((x_2D/unit)+((y_2D/unit)*3));
			if (patternPerl[bit] == '0') glColor3ub(255,255,255);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D  )*nextX.x + (y_2D  )*nextY.x,
                  drawY + (x_2D  )*nextX.y + (y_2D  )*nextY.y,
                  drawZ + (x_2D  )*nextX.z + (y_2D  )*nextY.z  );
      glVertex3d( drawX + (x_2D+unit)*nextX.x + (y_2D  )*nextY.x,
                  drawY + (x_2D+unit)*nextX.y + (y_2D  )*nextY.y,
                  drawZ + (x_2D+unit)*nextX.z + (y_2D  )*nextY.z  );
      glVertex3d( drawX + (x_2D+unit)*nextX.x + (y_2D+unit)*nextY.x,
                  drawY + (x_2D+unit)*nextX.y + (y_2D+unit)*nextY.y,
                  drawZ + (x_2D+unit)*nextX.z + (y_2D+unit)*nextY.z  );
      glVertex3d( drawX + (x_2D  )*nextX.x + (y_2D+unit)*nextY.x,
                  drawY + (x_2D  )*nextX.y + (y_2D+unit)*nextY.y,
                  drawZ + (x_2D  )*nextX.z + (y_2D+unit)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawSuperPerl(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      int bit = (int)((x_2D*2)+((y_2D*2)*14));
			if      (patternSuperPerl[bit] == '0') glColor3ub(255,255,50);
      else if (patternSuperPerl[bit] == '1') glColor3ub(255,155,50);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawCherry(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      int bit = (int)((x_2D*2)+((y_2D*2)*14));
			if      (patternCherry[bit] == '0') glColor3ub(255,255,255);
			else if (patternCherry[bit] == '1') glColor3ub(242,  0,  0);
			else if (patternCherry[bit] == '2') glColor3ub(170,138, 67);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawPacMan(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      double i=x_2D, j=y_2D;
      if (cursor.xdir == -1 && cursor.ydir == 0) { // left
        i = (blockSize_3D-0.5) - x_2D;
        j = y_2D;
      }
      else if (cursor.xdir == 0 && cursor.ydir == 1) { // up
        i = y_2D;
        j = (blockSize_3D-0.5) - x_2D;
      }
      else if (cursor.xdir == 0 && cursor.ydir == -1) { // down
        i = (blockSize_3D-0.5) - y_2D;
        j = (blockSize_3D-0.5) - x_2D;
      }

      int bit = (int)((i*2)+((j*2)*14));
			if (patternPacMan[bit] == '4') glColor3ub(255,255,  0);
      else                                  glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}



void Maze_3D::DrawGhost(double drawX, double drawY, double drawZ, int xdir, int ydir) {
	double x_2D, y_2D;
  //int i, j;

  for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
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
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
    }
  }
}

class FullMaze_3D{
  private:
    Maze_3D maze[6]; // 0-T,1-N,2-W,3-S,4-E,5-B
    Coord_3D cursor;
    char curSurface;
    int curState; // 1 for not clear, 2 for clear box
  public:
    FullMaze_3D();
    void Draw();
    void Print();
    void PrintGhost();
    void SetMaze(int ***);
    void SetCursor(PacMan);
    void SetGhost(vector<Ghost> *ghostInfo);
    const void ReturnMaze(int***)const;
};

FullMaze_3D::FullMaze_3D(){
  maze[0].SetOrientation('T');
  maze[1].SetOrientation('N');
  maze[2].SetOrientation('W');
  maze[3].SetOrientation('S');
  maze[4].SetOrientation('E');
  maze[5].SetOrientation('B');
  curSurface = 'S';
  curState = 1;
  cursor.x = rand()%blockNumber;
  cursor.y = rand()%blockNumber;
  maze[3].Activate(cursor,curState);

}

void FullMaze_3D::PrintGhost(){
  for(int i = 0;i < 6;i++){
    printf("%ld,",maze[i].ghost.size());
  }
  printf("\n");
}

void FullMaze_3D::SetGhost(vector<Ghost> *ghostInfo){
  int n = ghostInfo->size();
  for(int i = 0;i < 6;i++){
    maze[i].ghost.clear();
  }
  for(int i = 0;i < n;i++){
    int surface = ghostInfo->at(i).surface;
    maze[surface].ghost.push_back(ghostInfo->at(i));
  }
}

void FullMaze_3D::SetCursor(PacMan pacman){
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
  cursor.xdir = pacman.xdir;
  cursor.ydir = pacman.ydir;



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
    case 'S':
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


void FullMaze_3D::Draw(){
  for(int i = 1;i < 5;i++){
    //printf("full: %d\n", i);
    maze[i].Draw3D();
  }
}

void FullMaze_3D::SetMaze(int ***input){
  for(int i = 0;i < 6;i++){
    for(int j = 0;j < blockNumber;j++){
      for(int k = 0;k < blockNumber;k++){
        maze[i].SetMaze(k,j,input[i][k][j]);
      }
    }
  }
}

void FullMaze_3D::Print(){
  for(int i = 0;i < 6;i++){
    maze[i].Print();
  }
}

#endif
