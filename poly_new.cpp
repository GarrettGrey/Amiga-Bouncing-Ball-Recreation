/*
    Display a polygon of varying sides and move it around.
    A 16-gon will be used in the final product.
    This version is much more efficient than the March 2021 version, being based on how the points change based on the number of points in any polygon rather than the position of the last point in a 16-gon
    Garrett Grey
    10/10/23
*/

#include <GL/freeglut.h> 
#include <iostream>
#include <cmath>
using namespace std;

const float pi = 3.14159265;

float m[2];
int mdir = 0;

void setWindow (float left, float right, float bottom, float top){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (left, right, bottom, top);
}

void setViewport (int left, int right, int bottom, int top){
	glViewport (left, bottom, right-left, top-bottom);
}

void poly(int r, float pnts){
	glColor3f (1.0, 0.0, 0.0);  // red
	glBegin (GL_POLYGON);
		for(int i = 0; i < pnts; i++){
        	glVertex2f (m[0]+(r*sin((i*pi)/(pnts/2))),m[1]+(r*sin((((pnts/4)-i)*pi)/(pnts/2))));
        }
	glEnd();
}

void Render (void){
	glClear (GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT=Indicates the buffers currently enabled for color writing
	glClearColor (0.0, 0.0, 0.0, 0.0); // glClearColor() set the background color of the buffer to RGB(0,0,0)
	setWindow (-20.0, 20.0, -20.0, 20.0);
	setViewport (0, 640, 0, 480);

	poly(10, 16);

	glFlush(); // this fct flushes what we have in the buffer to the screen
}

void Mouse1(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON)
		m[mdir] += .5;
	if (btn == GLUT_RIGHT_BUTTON)
		m[mdir] -= .5;

	Render();
}

void Menu1(int index){
	mdir = index;
}

/////////  main  ////////////
int main(int argc,char** argv){
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 0);
	glutInitWindowSize (640, 480);
	glutInit(&argc,argv);
	glutCreateWindow ("ball");

	glutDisplayFunc (Render);
	glutMouseFunc(Mouse1);

	glutCreateMenu(Menu1);
 	  glutAddMenuEntry("horizontal", 0);
	  glutAddMenuEntry("vertical", 1);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}
