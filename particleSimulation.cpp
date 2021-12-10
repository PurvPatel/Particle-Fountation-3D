#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "wallMaterials.h"
#include "lightConstants.h"
#include "particle3D.h"
#include "particleSystem.h"
#include "light.h"
#include "material.h"

//window width and height
int windowWidth = 800;
int windowHeight = 800;

/* explosion flag*/
bool initialExplosionMode = false;

/* trail flag*/
bool initialTrail = false;

/* particle Properties flag */
bool property = false;

/* Initial direction */
Vec3D initialDirection(0, 0, 0);


/* CAMERA */
float camPos[] = {0, 100, 100};
float cameraRotateAngle = 6;
float AngleAboutX = 0;
float AngleAboutY = 0;


/* LIGHT CONTROLS */
bool lights = true;
Light currentLight = light0;
float moveLightInc = 5;

/* Origin */
Point3D origin(0, 25, 0);

/* Platform size, origin, and colour*/
float platformSize = 200;
float base[3] = {0, -1, 0};
std::vector<float> planeColour({0.5, 0.5, 0, 1.0f});

/* Particle System*/
particleSystem particles(origin, std::vector<particle3D>(), initialExplosionMode, initialTrail, property);

/* Gravity constant */
float g = 0.1;

//particle age: 1200 / 60 FPS = 20 seconds (they are spawning at around 5 per second so you are looking at 100 max particles (not counting the explosions)) 
int age = 1200;

// Friction Flag
bool friction = true;

// Pause Flag
bool pause = false;

void toggle_lights(){
	lights = !lights;

	if (lights)
		glEnable(GL_LIGHTING);
	else 
		glDisable(GL_LIGHTING);
}

void moveLight(float dX, float dY, float dZ){
	currentLight.position[0] += dX;
	currentLight.position[1] += dY;
	currentLight.position[2] += dZ;
}

void reset(){
	//reset particles and all subsystems
	particles.particleList.clear();
	particles.subSystems.clear();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'l':
		case 'L':{
			toggle_lights();
			break;
		}
		case 'F':
		case 'f':{
			friction = !friction;
			break;
		}
		case 'R':
		case 'r':{
			reset();
			break;
		}
		case ' ':{
			pause = !pause;
			break;
		}
		case '0':{
			currentLight = light0;
			break;
		}
		case '1':{
			currentLight = light1;
			break;
		}
		case 'W':
		case 'w':{
			moveLight(moveLightInc, 0, 0);
			break;
		}
		case 'S':
		case 's':{
			moveLight(-moveLightInc, 0, 0);
			break;
		}
		case 'A':
		case 'a':{
			moveLight(0, 0, -moveLightInc);
			break;
		}
		case 'D':
		case 'd':{
			moveLight(0, 0, moveLightInc);
			break;
		}
		case '-':{
			moveLight(0, -moveLightInc, 0);
			break;
		}
		case '+':{
			moveLight(0, moveLightInc, 0);
			break;
		}
		case 'E':
		case 'e':{
			particles.isExplosive = !particles.isExplosive;
			break;
		}
		case 'T':
		case 't':{
			particles.trail = !particles.trail;
			break;
		}
		case 'P':
		case 'p':{
			particles.property = !particles.property;
			break;
		}
	}
}


/* drawPolygon
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

/* cube
 */
void cube(float v[8][3])
{
	//vertex normals average out for each face
	glNormal3f(0, 0, 1);
	drawPolygon(0, 3, 2, 1, v);

	glNormal3f(-1, 0, 0);
	drawPolygon(1, 0, 4, 5, v);

	glNormal3f(0, 1, 0);
	drawPolygon(5, 1, 2, 6, v);
	
	glNormal3f(1, 0, 0);
	drawPolygon(2, 3, 7, 6, v);
	
	glNormal3f(0, 0, -1);
	drawPolygon(6, 5, 4, 7, v);

	glNormal3f(0, -1, 0);
	drawPolygon(4, 0, 3, 7, v);
}

/* drawBox 
 */
void drawBox(float* c, float w, float h, float d)
{
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };

	cube(vertices);
}

void specialKeys(int key, int x, int y){
	switch(key)
	{
		case GLUT_KEY_UP: {
			if (AngleAboutX == 180)
				AngleAboutX = -180 + cameraRotateAngle;
			else
				AngleAboutX += cameraRotateAngle;
			break;
		}
		case GLUT_KEY_DOWN: {
			if (AngleAboutX == (cameraRotateAngle - 180))
				AngleAboutX = 180;
			else
				AngleAboutX -= cameraRotateAngle;
			break;
		}
		case GLUT_KEY_RIGHT: {
			if (AngleAboutY == 180)
				AngleAboutY = -180 + cameraRotateAngle;
			else
				AngleAboutY += cameraRotateAngle;
			break;
		}
		case GLUT_KEY_LEFT: {
			if (AngleAboutY == (cameraRotateAngle - 180))
				AngleAboutY = 180;
			else
				AngleAboutY -= cameraRotateAngle;
			break;
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//setting up camera
	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);

	//camera rotation
	glPushMatrix();
	glRotatef(AngleAboutX, 1, 0, 0);
	glRotatef(AngleAboutY, 0, 1, 0);

	//light parameters
	glLightfv(light0.LIGHT_NUM, GL_POSITION, light0.position);
	glLightfv(light1.LIGHT_NUM, GL_POSITION, light1.position);

	//Walls and floors
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wallMaterials[0].ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wallMaterials[0].diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wallMaterials[0].specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, wallMaterials[0].shininess);
	
	glColor4fv(planeColour.data());
	drawBox(base, platformSize, 1, platformSize);

	//update particle movements
	particles.updateParticleMovements(Vec3D(0, -g, 0), platformSize / 2, platformSize / 2, friction);

	//particle drawing
	particles.display();

	glPopMatrix();

	glutSwapBuffers();
}

void FPS(int val) {

	// add new particles every around every second (1.020 seconds minimum), put it here to avoid race conditions with particles as a shared resource
	if (!pause){
		if (val == 1020){
			val = - 17;
			particles.addRandParticles(5, age, initialDirection);
		}
	}
	else{
		val = -17;
	}
	glutPostRedisplay();
	glutTimerFunc(17, FPS, val + 17);
	// Rendering every 17ms
	// 1 sec = 1000, 60 FPS = 1000/60 =~17
}

void init(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHT1);

	glLightfv(light0.LIGHT_NUM, GL_AMBIENT, light0.ambient);
	glLightfv(light0.LIGHT_NUM, GL_DIFFUSE, light0.diffuse);
	glLightfv(light0.LIGHT_NUM, GL_SPECULAR, light0.specular);

	glLightfv(light1.LIGHT_NUM, GL_AMBIENT, light1.ambient);
	glLightfv(light1.LIGHT_NUM, GL_DIFFUSE, light1.diffuse);
	glLightfv(light1.LIGHT_NUM, GL_SPECULAR, light1.specular);

	glClearColor(0.5, 0.5, 0.5, 0);
	glColor3f(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 600);

	particles.addRandParticles(5, age, initialDirection);
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    
	
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Particles 3D");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	glutTimerFunc(17, FPS, 0);        //timer function for FPS

	glEnable(GL_DEPTH_TEST);
    
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}