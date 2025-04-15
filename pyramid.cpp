//--------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Hexagonal Bipyramid (Project #4)
//
// Draw a hexagonal bipyramid and be able to spin it with your mouse.
//--------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include "camera.h"
#include <cmath>

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

	 cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);  
	 cameraApply();                                     


    float point[8][3] = {
        {0.0, 0.0, 1.0}, //bottom left corner of front side
        {0.5, 1.0, 0.5}, //top middle point
        {0.75, 0.0, 1.0}, //bottom right corner of front side
        {1.05, 0.0, 0.5}, //bottom right/left corners of right sides
        {0.75, 0.0, 0.0}, //bottom right corner of back side
        {0.0, 0.0, 0.0}, //bottom left corner of back side
        {-0.25, 0.0, 0.5}, //bottom left/right corners of left sides
        {0.5, -1.0, 0.5} //bottom middle point
    };

    glBegin(GL_TRIANGLES);
    //----------------------top pyramid--------------------
        //front, light blue
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(point[0]);
        glVertex3fv(point[1]);
        glVertex3fv(point[2]);

        //right, orange
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3fv(point[2]);
        glVertex3fv(point[1]);
        glVertex3fv(point[3]);

        //right, light blue
        glColor3f(0.0f, 1.0f, 1.0f); 
        glVertex3fv(point[3]);
        glVertex3fv(point[1]);
        glVertex3fv(point[4]);

        //back, orange
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3fv(point[4]);
        glVertex3fv(point[1]);
        glVertex3fv(point[5]);

        //left, light blue
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(point[5]);
        glVertex3fv(point[1]);
        glVertex3fv(point[6]);

        //left, orange
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3fv(point[6]);
        glVertex3fv(point[1]);
        glVertex3fv(point[0]);

        //------------------bottom pyramid------------------
        //front, orange
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3fv(point[0]);
        glVertex3fv(point[7]);
        glVertex3fv(point[2]);

        //right, light blue
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(point[2]);
        glVertex3fv(point[7]);
        glVertex3fv(point[3]);

        //right, orange
        glColor3f(1.0f, 0.5f, 0.0f); 
        glVertex3fv(point[3]);
        glVertex3fv(point[7]);
        glVertex3fv(point[4]);

        //back, light blue
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(point[4]);
        glVertex3fv(point[7]);
        glVertex3fv(point[5]);

        //left, orange
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3fv(point[5]);
        glVertex3fv(point[7]);
        glVertex3fv(point[6]);

        //left, light blue
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3fv(point[6]);
        glVertex3fv(point[7]);
        glVertex3fv(point[0]);

    glEnd();

    glFlush();
}

void init()
{
    glutMouseFunc(trackballMouseFunction);
	glutMotionFunc(trackballMotionFunction);
    return;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Hexagonal Bipyramid");
    glutDisplayFunc(display);
	init();
    glutMainLoop();
    return 0;
}