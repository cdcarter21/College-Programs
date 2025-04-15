//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3233
// Project-----Project #3
// Due---------September 20, 2023
//
// This program uses a triangle fan to draw a polygon of the number of sides
// specified by the user. 
//------------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <cmath>
#include <iostream>
using namespace std; 

int sidesInput; 

void drawPolygon(float x, float y, float radius, int sides){
	float twoPi = 2.0f * 3.14159265359;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(int i = 0; i <= sides; i++) 
			glVertex2f(x + (radius * cos(i * twoPi/sides)), y + (radius * sin(i * twoPi/sides)));
	glEnd();
}

void display() {
    glClearColor(0.13, 0.0f, 0.44, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 

    glColor3f(0.43, 0.62, 0.94);
    drawPolygon(0.0f, 0.0f, 0.7f, sidesInput);

    glFlush(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    cout << "Please enter the number of sides you would like: "; 
    cin >> sidesInput; 
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(500, 50);
    glutCreateWindow("Assignment #3");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}