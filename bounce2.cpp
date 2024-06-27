/*
    Have the ball bounce horizontally and add finishing touches to improve presentation.
    Garrett Grey
    4/12/21 moved ball horizontally
	4/13/21 attempted to add texture to ball
	4/15/21 removed texture functionality
			changed resolution to 1366x768 to fit the full screen of the laptop I will show the program in
			adjusted the horizontal speed to more accurately reflect the original
			made the program run fullscreen
			adjusted the size of the ball to make the length and height roughly equal and more accurately reflect the original
	4/16/21	adjusted the bouncing to more accurately reflect the original
			added the ball's shadow
	4/21/21 took some slight liberties and adjusted the shadow of the ball to be cast at an angle. The original doesn't do this, but it looks nicer this way.
	4/23/21	adjusted the angle and size of the ball's shadow.
	4/26/21 adjusted the grid's bottom diagonals.
    10/10/23 replaced the polygon/shadow functions with the new one from poly_new.cpp
	10/13/23 removed fullscreen
			 changed the program window to create a 4x3 window based on the height of the host monitor
	10/16/23 readjusted the shadow's position to reflect the original.
    3/13/24 capped the framerate to approximately 60 fps (way easier than I expected, even though it involed me using a namespace other than std for the first time)
    		adjusted speed of the ball to compinsate for the framerate limit
            slightly ajusted horizontal bounds for when the ball changes direction
            rotated the ball so that its vertical and horizontal sides are flat instead of a point like in the original
    
    TODO:
    Add the grid texture to the ball
    Add sound
*/ 

#include <GL/freeglut.h> 
#include <iostream>
#include <cmath>
#include <chrono>
#include <unistd.h> //will not work in Windows.
#include <thread>
  
using namespace std;

const float pi = 3.14159265;
double goalFrameTime = 1000/60; //how long a frame should last in ms (denominator is fps)

int height;
int width;

float m[2]; //m[0] is horizontal offset, m[1] is vertical offset
float v[2] = {.025, 0}; //v[0] is horizontal velocity, v[1] is vertical velocity

void setWindow (float left, float right, float bottom, float top){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (left, right, bottom, top);
}

void setViewport (int left, int right, int bottom, int top){
	glViewport (left, bottom, right-left, top-bottom);
}

void grid(){
	//Grid has total length of 34 and height of 30.6. Length is divided into 15ths and height is divided into 12ths.
    glColor4f (1.0, 0.0, 1.0, 1.0);  // purple
	for(int i = 0; i <= 15; i++){ //verticals
		glBegin (GL_LINES);
		  glVertex2f (-17+(2.266666667*i), 17);
		  glVertex2f (-17+(2.266666667*i), -13.6);
		glEnd();
	}
	for(int i = 0; i <=12; i++){ //horizontans
		glBegin (GL_LINES);
	  	  glVertex2f (-17, 17-(2.55*i));
	  	  glVertex2f (17, 17-(2.55*i));
		glEnd();
	}

    for(int i = 0; i <= 15; i++){ //bottom diagonals
		double pnt[] = {-17+(2.266666667*i), -13.6};
		float theta = (pi/2)+((pi/4)*-(pnt[0]/17));
		glBegin (GL_LINES);
		  glVertex2f (pnt[0],pnt[1]);
		  glVertex2f (pnt[0] + 5/tan(theta), pnt[1] - 5);
		glEnd();
	}



	for(int i = 1; i <=3; i++){ //bottom horizontals
		glBegin (GL_LINES);
		glVertex2f (-17-i*sqrt(1.275), -13.6-i*sqrt(1.275));
		glVertex2f (17+i*sqrt(1.275), -13.6-i*sqrt(1.275));
		glEnd();
	}
}

void bounce(){
    if(m[1] <= -8){
        v[1] = .15;
    }else v[1] -= .001;
    m[1] += v[1];

	if(m[0] <= -12.5 || m[0] >= 12.5){
		v[0] *= -1;
	}
	m[0] += v[0];
}

void poly(int r, float pnts, double rot){ //r=radius, pnts=points, rot=rotation
	glColor3f (1.0, 0.0, 0.0);  // red
	glBegin (GL_POLYGON);
		for(int i = 0; i < pnts; i++){
        	glVertex2f (m[0]+(r*sin(((i*pi)/(pnts/2))+rot)),m[1]+(r*sin(((((pnts/4)-i)*pi)/(pnts/2))-rot)));
        }
	glEnd();
}

void shadow(float r, float pnts, double rot){ //r=radius, pnts=points, rot=rotation
	glColor4f(.25,.25,.25,0.5);  // half-transparent dark gray
	glBegin (GL_POLYGON);
		for(int i = 0; i < pnts; i++){
        	glVertex2f (m[0]+(r*sin(((i*pi)/(pnts/2))+rot))+2,m[1]+(r*sin(((((pnts/4)-i)*pi)/(pnts/2))-rot))+1); 
        }
	glEnd();
}

void Render (void){
  	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	glClear (GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT=Indicates the buffers currently enabled for color writing
	glClearColor (.65, .65, .65, 0.0); // glClearColor() set the background color of the buffer to gray
	setWindow (-20.0, 20.0, -20.0, 20.0);
	setViewport (0, width, 0, height);

    bounce();

	grid();
	shadow(6.5,16,pi/16);
    poly(6,16,pi/16);

	glFlush(); // this fct flushes what we have in the buffer to the screen
	glutSwapBuffers();
    glutPostRedisplay(); //This allows the render function to loop, allowing any changes to act as frames in an animation
  	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
  	chrono::duration<double, std::milli> time_span = t2 - t1;//get time spent on this loop
  	//if it is less than 1/60, call sleep until 1/60 seconds have passed
  	if(time_span.count() < goalFrameTime){
      	int timeLeft = (goalFrameTime - time_span.count());
    	cout << "Time to render: " << time_span.count() << "ms, waiting " << timeLeft << "ms\n";
      	this_thread::sleep_for(chrono::milliseconds(timeLeft));
    }
}

int main(int argc,char** argv){
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 0);
	glutInit(&argc,argv);
	height = glutGet(GLUT_SCREEN_HEIGHT);
	width = height*4/3;
	glutInitWindowSize (width, height);

	glutCreateWindow ("Amiga Bouncing Ball Recreation");
	glEnable (GL_BLEND); //enables transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc (Render);

	glutMainLoop();
    
	return 0;
}