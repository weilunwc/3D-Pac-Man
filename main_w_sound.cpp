#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "maze.h"
#include "playImage.h"
#include "menu.h"
#include "score.h"
#include "rule.h"
#include "3Dmaze.h"
#include "button.h"
#include "pauseMenu.h"
#include "yssimplesound.h"


const int blockNumber = 25;
int blockSize_2D = 6;
int blockSize_3D = 7;
const string nullString = "\0";
bool plot3d = true;
//bool plot3d = false;
int menuLoop = 0;
int ruleLoop = 0;



double myPi = 3.1415926;
const int ghostNumber = 8;
void DrawMainPage(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3ub(50,0,0);
  glBegin(GL_QUADS);
  glVertex2i(100,100);
  glVertex2i(150,100);
  glVertex2i(150,150);
  glVertex2i(100,150);
  glEnd();
  FsSwapBuffers();
}
const int totalPells = 1883;


void GetKey(int &key){
  FsPollDevice();
  key = FsInkey();
}


int main(void){
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
  Button back(700,550);
  back.SetText("Menu");
  Button rematch(700,500);
  rematch.SetText("Again");
  Score score;
  maze.SetMaze();
  PauseMenu pauseMenu;
  FullMaze_3D maze_3d;
  PlayImage play;
  CameraObject camera1, camera2;
  OrbitingViewer orbit1, orbit2;
  //camera1.z = 10.0;

  FsOpenWindow(0,100,1600,600,1);
  FsPollDevice();
  int key = FsInkey();
  int state = 0;
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
    
    
    YsSoundPlayer player;
    player.MakeCurrent();
    player.Start();
    FsChangeToProgramDir();
    YsSoundPlayer::SoundData pacman_death, scene, cherry, areyouready;
    
    
  while(key != FSKEY_ESC){
    switch(state){
      case 0:
        // the main menu
        menuLoop = 0;
        while(key != FSKEY_ESC && state == 0){
          FsPollDevice();
          key = FsInkey();
          state = menu.ReadInput(key);
          glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
          menuLoop++;
          menu.DrawMenu(menuLoop);
          FsSwapBuffers();
          FsSleep(20);
        }
        break;
      case 1:
        // start playing game
        player.KeepPlaying();
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
        while(key != FSKEY_ESC && state == 1){

          FsPollDevice();
          key = FsInkey();
          mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);
          /*
          back.ReadState(mx,my);
          if((lb || rb) && back.state){
            state = 0;
          }
          */
            
            if(loopCount == 0){
                player.Stop(areyouready);
                player.PlayOneShot(areyouready);
            }
            player.PlayBackground(scene);
        
          if(exchangePlayers == false)
            switch(key){
              case FSKEY_SPACE:
                pause = !pause;
                break;
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
          else{
            switch(key){
              case FSKEY_SPACE:
                pause = !pause;
                break;
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
          if(pause == false && countDown <= 0){

            maze.Move();
              if(maze.cherries > n){
                  player.Stop(scene);
                  player.Stop(cherry);
                  player.PlayOneShot(cherry);
              }
            maze.GhostMove(loopCount);
            if(maze.CollisionDetect()){
                player.Stop(scene);
                player.Stop(pacman_death);
                player.PlayOneShot(pacman_death);
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
          maze.ReturnMaze(mazeArray);
          maze.ReturnPacman(&pacInfo);
          maze.ReturnGhost(&ghostInfo);
          int ghostNow = maze.ReturnGhostControl();
          maze_3d.SetMaze(mazeArray);
          maze_3d.SetCursor(pacInfo);
          maze_3d.SetGhost(&ghostInfo);

          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          /*
          glColor3ub(0,0,0);
          glBegin(GL_QUADS);
          glVertex2i(0,0);
          glVertex2i(1800,0);
          glVertex2i(1800,600);
          glVertex2i(0,600);
          glEnd();
          */
          play.Draw();

          if(plot3d == true){
            if(0!=FsGetKeyState(FSKEY_F) && orbit1.dist > 1.0){
                orbit1.dist/=1.05;
                orbit2.dist/=1.05;
            }
            if(0!=FsGetKeyState(FSKEY_B) && orbit1.dist < 200.0){
                orbit1.dist*=1.05;
                orbit2.dist*=1.05;
            }
            /*
            if(0!=FsGetKeyState(FSKEY_A)){
                orbit.h+=5*myPi/180.0;
            }
            if(0!=FsGetKeyState(FSKEY_W)){
                orbit.p+=5*myPi/180.0;
            }
            if(0!=FsGetKeyState(FSKEY_S)){
                orbit.p-=5*myPi/180.0;
            }
            if(0!=FsGetKeyState(FSKEY_D)){
                orbit.h-=5*myPi/180.0;
            }
            */

            int wid,hei;
            FsGetWindowSize(wid,hei);


            /* calculate the h p angle and the posittion of the camera1 */
            double Px, Py, Pz;
            // 0 T
            if(pacInfo.surface == 0) {
                Px = -blockNumber * 0.5 + pacInfo.x;
                Py = blockNumber * 0.5;
                Pz = -blockNumber * 0.5 + pacInfo.y;
            }
            // 1 N
            else if (pacInfo.surface == 1) {
                Px = blockNumber * 0.5 - pacInfo.x;
                Py = blockNumber * 0.5 - pacInfo.y;
                Pz = -blockNumber * 0.5;
            }
            // 2 W
            else if (pacInfo.surface == 2) {
                Px = -blockNumber * 0.5;
                Py = blockNumber * 0.5 - pacInfo.y;
                Pz = -blockNumber * 0.5 + pacInfo.x;
            }
            // 3 S
            else if (pacInfo.surface == 3) {
                Px = -blockNumber * 0.5 + pacInfo.x;
                Py = blockNumber * 0.5 - pacInfo.y;
                Pz = blockNumber * 0.5;
            }
            // 4 E
            else if (pacInfo.surface == 4) {
                Px = blockNumber * 0.5;
                Py = blockNumber * 0.5 - pacInfo.y;
                Pz = blockNumber * 0.5 - pacInfo.x;
            }
            // 5 B
            else if (pacInfo.surface == 5) {
                Px = -blockNumber * 0.5 + pacInfo.x;
                Py = -blockNumber * 0.5;
                Pz = blockNumber * 0.5 - pacInfo.y;
            }

            double r = sqrt(Px*Px + Py*Py + Pz*Pz);
            orbit1.p =  - asin(Py / r);
            if(Pz == 0 && Px > 0) {
                orbit1.h = myPi / 2;
            }
            else if(Pz == 0 && Px < 0) {
                orbit1.h = myPi / 2 * 3;
            }
            else if(Pz > 0 && Px >= 0) {
                orbit1.h = acos(Pz / r / cos(orbit1.p));
            }
            else if(Pz < 0 && Px >= 0) {
                orbit1.h = acos(Pz / r / cos(orbit1.p));
            }
            else if(Pz < 0 && Px < 0) {
                orbit1.h = 2 * myPi - acos(Pz / r / cos(orbit1.p));
            }
            else {
                orbit1.h = 2 * myPi - acos(Pz / r / cos(orbit1.p));
            }

            /* update camera1 */
            orbit1.SetUpCamera(camera1);
            camera1.x = Px / r * orbit1.dist;
            camera1.y = Py / r * orbit1.dist;
            camera1.z = Pz / r * orbit1.dist;

           /* pacman player's view */

            if(exchangePlayers == false){
              glViewport(wid/4,0,wid,hei);
            }
            else{
              glViewport(-wid/4,0,wid,hei);
            }

            camera1.SetUpCameraProjection();
            camera1.SetUpCameraTransformation();
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1,1);
            maze_3d.Draw();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);


            double Gx, Gy, Gz;
            /* calculate the h p angle and the posittion of the camera1 */
            // 0 T
            if(ghostInfo[ghostNow].surface == 0) {
                Gx = -blockNumber * 0.5 + ghostInfo[ghostNow].x;
                Gy = blockNumber * 0.5;
                Gz = -blockNumber * 0.5 + ghostInfo[ghostNow].y;
            }
            // 1 N
            else if (ghostInfo[ghostNow].surface == 1) {
                Gx = blockNumber * 0.5 - ghostInfo[ghostNow].x;
                Gy = blockNumber * 0.5 - ghostInfo[ghostNow].y;
                Gz = -blockNumber * 0.5;
            }
            // 2 W
            else if (ghostInfo[ghostNow].surface == 2) {
                Gx = -blockNumber * 0.5;
                Gy = blockNumber * 0.5 - ghostInfo[ghostNow].y;
                Gz = -blockNumber * 0.5 + ghostInfo[ghostNow].x;
            }
            // 3 S
            else if (ghostInfo[ghostNow].surface == 3) {
                Gx = -blockNumber * 0.5 + ghostInfo[ghostNow].x;
                Gy = blockNumber * 0.5 - ghostInfo[ghostNow].y;
                Gz = blockNumber * 0.5;
            }
            // 4 E
            else if (ghostInfo[ghostNow].surface == 4) {
                Gx = blockNumber * 0.5;
                Gy = blockNumber * 0.5 - ghostInfo[ghostNow].y;
                Gz = blockNumber * 0.5 - ghostInfo[ghostNow].x;
            }
            // 5 B
            else if (ghostInfo[ghostNow].surface == 5) {
                Gx = -blockNumber * 0.5 + ghostInfo[ghostNow].x;
                Gy = -blockNumber * 0.5;
                Gz = blockNumber * 0.5 - ghostInfo[ghostNow].y;
            }

            double r2 = sqrt(Gx*Gx + Gy*Gy + Gz*Gz);
            orbit2.p =  - asin(Gy / r2);
            if(Gz == 0 && Gx > 0) {
                orbit2.h = myPi / 2;
            }
            else if(Gz == 0 && Gx < 0) {
                orbit2.h = myPi / 2 * 3;
            }
            else if(Gz > 0 && Gx >= 0) {
                orbit2.h = acos(Gz / r2 / cos(orbit2.p));
            }
            else if(Gz < 0 && Gx >= 0) {
                orbit2.h = acos(Gz / r2 / cos(orbit2.p));
            }
            else if(Gz < 0 && Gx < 0) {
                orbit2.h = 2 * myPi - acos(Gz / r2 / cos(orbit2.p));
            }
            else {
                orbit2.h = 2 * myPi - acos(Gz / r2 / cos(orbit2.p));
            }

            /* ghost player's view */
            if(exchangePlayers == false){
              glViewport(-wid/4,0,wid,hei);
            }
            else{
              glViewport(wid/4,0,wid,hei);
            }
            /* update camera2 */
            orbit2.SetUpCamera(camera2);
            camera2.x = Gx / r2 * orbit2.dist;
            camera2.y = Gy / r2 * orbit2.dist;
            camera2.z = Gz / r2 * orbit2.dist;

            camera2.SetUpCameraProjection();
            camera2.SetUpCameraTransformation();
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1,1);
            maze_3d.Draw();


            // reset 2D
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);
            glViewport(0,0,wid,hei);
          }
          else{
            maze.Draw();
          }
          //back.Draw();

          string playerHeader = "Player ";
          char displayPlayer[1024];
          if(exchangePlayers == false){
            IntToChar(1,playerHeader,nullString,displayPlayer);
          }
          else{
            IntToChar(2,playerHeader,nullString,displayPlayer);
          }


          string timeHeader = "Time Left: ";
          char displayTime[1024];
          IntToChar(timeLeft,timeHeader,nullString,displayTime);

          string livesHeader = "Lives: ";
          char displayLives[1024];
          IntToChar(lives,livesHeader,nullString,displayLives);



          glColor3ub(255, 255, 255);
          glRasterPos2i(10, 20);
          YsGlDrawFontBitmap8x12(displayPlayer);
          glRasterPos2i(10, 40);
          YsGlDrawFontBitmap8x12(displayTime);
          glRasterPos2i(10,60);
          YsGlDrawFontBitmap8x12(displayLives);

          if(countDown > 0){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.0,0.0,0.0,0.7);
            glBegin(GL_QUADS);
            glVertex2i(0,0);
            glVertex2i(1600,0);
            glVertex2i(1600,600);
            glVertex2i(0,600);
            glEnd();
            char displayCountDown[1024];
            IntToChar(countDown,nullString,nullString,displayCountDown);
            glColor3ub(255,255,255);
            glRasterPos2i(600,300);
            YsGlDrawFontBitmap32x48(displayCountDown);
          }
          if(pause == true){
            pauseState = pauseMenu.ReadInput(key);
            switch(pauseState){
              case 0:
                pause = false;
                break;
              case 1:
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
                break;
              case 2:
                state = 0;
                break;
              default:
                state = 1;
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
              score.SetGhost(0,3-lives);
              score.SetPacman(1,maze.ghost_eaten,perls,maze.cherries);
              state = 4;
            }
            else{
              // switch players
              //score.SetPlayer2(perls,lives,0,0,(int)totalTimeLeft);
              //score.SetPlayer1(0,0,0,pac_eaten,2*(int)totalTimeLeft);
              score.SetGhost(1,3-lives);
              score.SetPacman(0,maze.ghost_eaten,perls,maze.cherries);
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
        }
        break;
      case 2:
        // Rules state
        ruleLoop = 0;
        while(key != FSKEY_ESC && state == 2){
          FsPollDevice();
          mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);
          key = FsInkey();
          back.ReadState(mx,my);
          if((lb || rb) && back.state){
            state = 0;
          }
          glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
          ruleLoop++;
          rule.Draw(ruleLoop);
          back.Draw();
          FsSwapBuffers();
          FsSleep(20);
        }
        break;
      case 3:
        // Esc
        key = FSKEY_ESC;
        break;
      case 4:
        // Score state
        while(key != FSKEY_ESC && state == 4){
          FsPollDevice();
          mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);
          key = FsInkey();
          back.ReadState(mx,my);
          rematch.ReadState(mx,my);
          if(lb || rb){
            if(back.state){
              state = 0;
            }
            else if(rematch.state){
              state = 1;
            }
          }
          glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
          score.Draw();
          back.Draw();
          rematch.Draw();
          FsSwapBuffers();
          FsSleep(20);
        }
        break;
      case 5:
        // pause phase
        while(key != FSKEY_ESC && state == 5){
          state = 1;
          /*
          FsPollDevice();
          mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);
          key = FsInkey();
          back.ReadState(mx,my);
          if((lb || rb) && back.state){
            state = 0;
          }
          glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
          rule.Draw();
          back.Draw();
          FsSwapBuffers();
          FsSleep(20);
          */
        }
      default:
        GetKey(key);
        state = 0;
        FsSleep(20);
        break;
    }
  }
  for(int i =0;i < 6;i++){
    for(int j = 0;j < blockNumber;j++){
      delete [] mazeArray[i][j];
    }
    delete [] mazeArray[i];
  }
  delete [] mazeArray;
    player.End();
  return 0;
}





