/*
    Combine poly.cpp and background.cpp and have the ball bounce vertically.
    Garrett Grey
    4/9/21
*/ 

#include <GL/freeglut.h> 
#include <iostream>
#include <cmath>
using namespace std;

const float pi = 3.14159265;

float m[2]; //m[0] is horizontal offset, m[1] is vertical offset
float v = 0; //ball's velocity

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
    glColor3f (1.0f, 0.0f, 1.0f);  // purple
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
		glBegin (GL_LINES);
		  glVertex2f (-17+(2.266666667*i), -13.6);
		  glVertex2f ((-17+(2.266666667*i))+(((-17+(2.266666667*i))/17)*(6.375*sin(pi/4))), -13.6-(6.375*sin(pi/4)));
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
        v = .01275;
    }else v -= .00001;
    m[1] += v;
}

void poly(float n){ //noticed the ball isn't perfect, it's slightly longer than it is tall. Cannot figure out why.
	glColor3f (1.0, 0.0, 0.0);  // red
	float pnt[2];
	glBegin (GL_POLYGON);
        //Draws counter-clockwise from the left point on the bottom horizontal edge.
		pnt[0] = n*tan(pi/16) + m[0];
		pnt[1] = -n + m[1];
		glVertex2f (pnt[0],pnt[1]);

        for(int i = 0; i < 3; i++){ // denominator in the sine increases by 4x^2 + 8, were x is i.
            pnt[0] += (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] += (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = n + m[0];
		pnt[1] = n*tan(pi/16) + m[1];
		glVertex2f (pnt[0],pnt[1]);

        for(int i = 2; i >= 0; i--){
            pnt[0] -= (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] += (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = n*-tan(pi/16) + m[0];
		pnt[1] = n + m[1];
		glVertex2f (pnt[0],pnt[1]);


        for(int i = 0; i < 3; i++){
            pnt[0] -= (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] -= (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = -n + m[0];
		pnt[1] = n*-tan(pi/16) + m[1];
		glVertex2f (pnt[0],pnt[1]);

		for(int i = 2; i >= 0; i--){
            pnt[0] += (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] -= (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
	glEnd();
}

void Render (void){
	glClear (GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT=Indicates the buffers currently enabled for color writing
	glClearColor (.65, .65, .65, 0.0); // glClearColor() set the background color of the buffer to gray
	setWindow (-20.0, 20.0, -20.0, 20.0);
	setViewport (0, 640, 0, 480);
    bounce();

	grid();
    poly(7.5);

	glFlush(); // this fct flushes what we have in the buffer to the screen
    glutPostRedisplay(); //This allows the render function to loop, allowing any changes to act as frames in an animation
}

int main(int argc,char** argv){
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 0);
	glutInitWindowSize (640, 480);
	glutInit(&argc,argv);
	glutCreateWindow ("ball and background");

	glutDisplayFunc (Render);

	glutMainLoop();
        
	return 0;
}