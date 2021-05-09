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
*/ 

#include <GL/freeglut.h> 
#include <iostream>
#include <cmath>
using namespace std;

const float pi = 3.14159265;

float m[2]; //m[0] is horizontal offset, m[1] is vertical offset
float v[2] = {.0075, 0}; //v[0] is horizontal velocity, v[1] is vertical velocity

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
        v[1] = .057;
    }else v[1] -= .0001;
    m[1] += v[1];

	if(m[0] <= -12 || m[0] >= 12){
		v[0] *= -1;
	}
	m[0] += v[0];
}

void poly(float n){
	glColor4f (1.0, 0.0, 0.0, 5.0);  // red
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
		pnt[1] = n*tan(pi/16) + m[1] + 1.125;
		glVertex2f (pnt[0],pnt[1]);

        for(int i = 2; i >= 0; i--){
            pnt[0] -= (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] += (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = n*-tan(pi/16) + m[0];
		pnt[1] = n + m[1] + 1.125;
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

void shadow(float n){
	glColor4f(.25,.25,.25,0.5);  // dark gray
	float pnt[2];
	glBegin (GL_POLYGON);
        //Draws counter-clockwise from the left point on the bottom horizontal edge.
		pnt[0] = n*tan(pi/16) + m[0] + 2;
		pnt[1] = -n + m[1] + 1;
		glVertex2f (pnt[0],pnt[1]);

        for(int i = 0; i < 3; i++){ // denominator in the sine increases by 4x^2 + 8, were x is i.
            pnt[0] += (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] += (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = n + m[0] + 2;
		pnt[1] = n*tan(pi/16) + m[1] + 1.125;
		glVertex2f (pnt[0],pnt[1]);

        for(int i = 2; i >= 0; i--){
            pnt[0] -= (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] += (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = n*-tan(pi/16) + m[0] + 2;
		pnt[1] = n + m[1] + 1.125;
		glVertex2f (pnt[0],pnt[1]);


        for(int i = 0; i < 3; i++){
            pnt[0] -= (2*n*tan(pi/16)*sin(3*pi/(4*(i*i)+8)));
            pnt[1] -= (2*n*tan(pi/16)*cos(3*pi/(4*(i*i)+8)));
            glVertex2f (pnt[0],pnt[1]);
        }
		pnt[0] = -n + m[0] + 2;
		pnt[1] = n*-tan(pi/16) + m[1] + 1;
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
	setViewport (0, 1366, 0, 768);

    bounce();

	grid();
	shadow(6.5);
    poly(6);

	glFlush(); // this fct flushes what we have in the buffer to the screen
	glutSwapBuffers();
    glutPostRedisplay(); //This allows the render function to loop, allowing any changes to act as frames in an animation
}

int main(int argc,char** argv){
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 0);
	glutInitWindowSize (1366, 768);
	glutInit(&argc,argv);
	glutCreateWindow ("Amiga Bouncing Ball Recreation");
	//glutFullScreen();
	glEnable (GL_BLEND); //enables transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc (Render);

	glutMainLoop();
    
	return 0;
}