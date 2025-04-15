//---------------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Lighted Prism (Project #5)
// Due -------- October 18, 2023
//
// Draw two differing prisms with lighting enabled by using normal vectors.
//---------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------
// This function will compute a normal vector for the given vertices. 
//---------------------------------------------------------------------------------
float product[3];
float* normalize(float *a, float *b, float *c)
{
    float v1[3], v2[3];
    for (int j = 0; j < 3; j++) {
        v1[j] = c[j] - a[j];
        v2[j] = b[j] - a[j];
    }
	product[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	product[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	product[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	return product;
}

//---------------------------------------------------------------------------------
// This function will draw a prism with n sides.
//---------------------------------------------------------------------------------
void drawPrism(int n) {
    float points[n*2][3];
    float twoPi = 2.0f * 3.14159265359;
    //compute the vertices
    for(int i = 0; i < n*2; i++) {
        points[i][0] = 0.5 * cos(i * twoPi/n);
        if (i < n)
            points[i][1] = 0.0f;
        else
            points[i][1] = 1.0f;
        points[i][2] = 0.5 * sin(i * twoPi/n);
    }
    //bottom base
	glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, -2.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		for(int i = 0; i < n; i++)
			glVertex3fv(points[i]);
        glVertex3fv(points[0]);
    glEnd();
    //top base
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 2.0f, 0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
        for(int i = n; i < n*2; i++)
			glVertex3fv(points[i]);
        glVertex3fv(points[n]);
	glEnd();
    //loop for drawing each rectangular side 
    for (int i = 0; i < n; i++) {
        //draw the side
        glBegin(GL_TRIANGLE_FAN); 
            if (i < (n-1)) {
                float *normal = normalize(points[i], points[i+1], points[i+n]);
                glNormal3fv(normal);
                glVertex3fv(points[i]);
                glVertex3fv(points[i+1]);
                glVertex3fv(points[i+1+n]);
                glVertex3fv(points[i+n]);
            }
            //this is for the last side
            else {
                float *normal = normalize(points[i], points[0], points[i+n]);
                glNormal3fv(normal);
                glVertex3fv(points[i]);
                glVertex3fv(points[0]);
                glVertex3fv(points[n]);
                glVertex3fv(points[i+n]);
            }
        glEnd();
    }
}

//---------------------------------------------------------------------------------
// The display function is where we will be setting up our drawing.
//---------------------------------------------------------------------------------
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);  
	cameraApply();

    float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    float pink[4] = { 1.0f, 0.5f, 1.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    drawPrism(7);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
    glTranslatef(1.5f, 0.5f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawPrism(5);
    glFlush();
}

//---------------------------------------------------------------------------------
// The init function sets up the lighting and Eck's trackball camera.
//---------------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    glEnable(GL_NORMALIZE);
    glutMouseFunc(trackballMouseFunction);
	glutMotionFunc(trackballMotionFunction);
    return;
}

//---------------------------------------------------------------------------------
// The main function to drive the program.
//---------------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Prism");
    glutDisplayFunc(display);
	init();
    glutMainLoop();
    return 0;
}