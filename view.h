/* 
 * view.h - Defines functions and classes related to user's camera view
 */

#ifndef VIEW_H
#define VIEW_H

#include "fssimplewindow.h"

class CameraObject{
public:
    double x,y,z;
    double h,p,b;

    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);
    void GetForwardVector(double &vx,double &vy,double &vz);
};

CameraObject::CameraObject(){
    Initialize();
}

void CameraObject::Initialize(void){
    x=0;
    y=0;
    z=0;
    h=0;
    p=0;
    b=0;

    fov=myPi/6.0;  // 30 degree
    nearZ=0.1;
    farZ=1000;
}

void CameraObject::SetUpCameraProjection(void){
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/myPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/myPi,0.0,0.0,1.0);
    glRotated(-p*180.0/myPi,1.0,0.0,0.0);
    glRotated(-h*180.0/myPi,0.0,1.0,0.0);
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz){
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

class OrbitingViewer{
public:
    double h,p;
    double dist;
    double focusX,focusY,focusZ;

    OrbitingViewer();
    void Initialize(void);
    void SetUpCamera(CameraObject &camera);
};

OrbitingViewer::OrbitingViewer(){
    Initialize();
}

void OrbitingViewer::Initialize(void){
    h=0;
    p=0;
    dist=500.0;
    focusX=0.0;
    focusY=0.0;
    focusZ=0.0;
}

void OrbitingViewer::SetUpCamera(CameraObject &camera)
{
    camera.h=h;
    camera.p=p;
    camera.b=0.0;

    double vx,vy,vz;
    camera.GetForwardVector(vx,vy,vz);
    camera.x=focusX-vx*dist;
    camera.y=focusY-vy*dist;
    camera.z=focusZ-vz*dist;
}


/* Controls the view point of player */
class View{
private:
	CameraObject camera;
	OrbitingViewer orbit;
public:
	View(){};
	void KeyboardChangeView();
	void CameraFollow(int surface, int x, int y);
	void SetView();
};

/* Camera's view point directly above object */
void View::CameraFollow(int surface, int x, int y){
	/* calculate the h p angle and the posittion of the camera */
	
	/* Get the coordinates */
	double Px, Py, Pz;
	Px = 0; Py = 0; Pz = 0;
	// 0 T
	if(surface == 0) {
		Px = -blockNumber * 0.5 + x;
		Py = blockNumber * 0.5;
		Pz = -blockNumber * 0.5 + y;
	}
	// 1 N
	else if (surface == 1) {
		Px = blockNumber * 0.5 - x;
		Py = blockNumber * 0.5 - y;
		Pz = -blockNumber * 0.5;
	}
	// 2 W
	else if (surface == 2) {
		Px = -blockNumber * 0.5;
		Py = blockNumber * 0.5 - y;
		Pz = -blockNumber * 0.5 + x;
	}
	// 3 S
	else if (surface == 3) {
		Px = -blockNumber * 0.5 + x;
		Py = blockNumber * 0.5 - y;
		Pz = blockNumber * 0.5;
	}
	// 4 E
	else if (surface == 4) {
		Px = blockNumber * 0.5;
		Py = blockNumber * 0.5 - y;
		Pz = blockNumber * 0.5 - x;
	}
	// 5 B
	else if (surface == 5) {
		Px = -blockNumber * 0.5 + x;
		Py = -blockNumber * 0.5;
		Pz = blockNumber * 0.5 - y;
	}

	double r = sqrt(Px*Px + Py*Py + Pz*Pz);
	orbit.p =  - asin(Py / r);
	if(Pz == 0 && Px > 0) {
		orbit.h = myPi / 2;
	}
	else if(Pz == 0 && Px < 0) {
		orbit.h = myPi / 2 * 3;
	}
	else if(Pz > 0 && Px >= 0) {
		orbit.h = acos(Pz / r / cos(orbit.p));
	}
	else if(Pz < 0 && Px >= 0) {
		orbit.h = acos(Pz / r / cos(orbit.p));
	}
	else if(Pz < 0 && Px < 0) {
		orbit.h = 2 * myPi - acos(Pz / r / cos(orbit.p));
	}
	else {
		orbit.h = 2 * myPi - acos(Pz / r / cos(orbit.p));
	}

	/* update camera */
	orbit.SetUpCamera(camera);
	camera.x = Px / r * orbit.dist;
	camera.y = Py / r * orbit.dist;
	camera.z = Pz / r * orbit.dist;

}
/* Manually change view from keyboard input */
void View::KeyboardChangeView(){
	FsPollDevice();
	// change scale
	if(0!=FsGetKeyState(FSKEY_F) && orbit.dist > 1.0){
		orbit.dist/=1.05;
	}
	if(0!=FsGetKeyState(FSKEY_B) && orbit.dist < 200.0){
		orbit.dist*=1.05;
	}
	
	// change view angle
	if(0!=FsGetKeyState(FSKEY_A)){
		orbit.h += 5*myPi/180.0;
	}
	if(0!=FsGetKeyState(FSKEY_W)){
		orbit.p += 5*myPi/180.0;
	}
	if(0!=FsGetKeyState(FSKEY_S)){
		orbit.p -= 5*myPi/180.0;
	}
	if(0!=FsGetKeyState(FSKEY_D)){
		orbit.h -= 5*myPi/180.0;
	}
}

void View::SetView(){
	camera.SetUpCameraProjection();
	camera.SetUpCameraTransformation();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1,1);
	
}
#endif
