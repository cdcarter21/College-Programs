//---------------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Lighted Scene (Project #6)
// Due -------- October 27, 2023
//
// The program will draw a scene with lighted objects. 
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
void drawPrism(int n, float x, float y, float z, bool top) {
    float points[n*2][3];
    float twoPi = 2.0f * 3.14159265359;
    //compute the vertices
    for(int i = 0; i < n*2; i++) {
        points[i][0] = x * cos(i * twoPi/n);
        if (i < n)
            points[i][1] = 0.0f;
        else
            points[i][1] = y;
        points[i][2] = z * sin(i * twoPi/n);
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
    if (top) {
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0.0f, 2.0f, 0.0f);
            glVertex3f(0.0f,y,0.0f);
            for(int i = n; i < n*2; i++)
                glVertex3fv(points[i]);
            glVertex3fv(points[n]);
        glEnd();
    }
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

    //the colors i will be using for my objects
    float tableColor[4] = { 0.7f, 0.5f, 0.4f, 1.0f };
    float holderColor[4] = { 0.7f, 0.25f, 0.7f, 1.0f };
    float pencilColor[4] = { 1.0f, 0.7f, 0.0f, 1.0f };
    float pink[4] = { 1.0f, 0.25f, 0.9f, 1.0f };
    float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float water[4] = { 0.8f, 0.95f, 0.97f, 0.5f };
    float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, tableColor);
    //table leg
    glScalef(0.25f, 0.25f, 0.25f);
    drawPrism(4, 0.5, 2, 0.5, true);
    //table leg
    glPushMatrix();
        glTranslatef(4.0f, 0.0f, -4.0f);
        drawPrism(4, 0.5, 2, 0.5, true);
    glPopMatrix();
    //table leg
    glPushMatrix();
        glTranslatef(3.0f, 0.0f, 3.0f);
        drawPrism(4, 0.5, 2, 0.5, true);
    glPopMatrix();
    //table leg
    glPushMatrix();
        glTranslatef(7.0f, 0.0f, -1.0f);
        drawPrism(4, 0.5, 2, 0.5, true);
    glPopMatrix();
    //table top 
    glPushMatrix();
        glTranslatef(3.5f, 2.0f, -0.5f);
        drawPrism(4, 4.5, 0.5, 4.5, true);
    glPopMatrix();

    //pencil holder
    glMaterialfv(GL_FRONT, GL_DIFFUSE, holderColor);
    glPushMatrix();
        glTranslatef(1.0f, 2.5f, 0.0f);
        drawPrism(100, 0.5, 1, 0.5, false);
    glPopMatrix();

    //make three pencils 
    for (float i = 0.8; i < 1.4; i += 0.2) {
        //pencil base
        glMaterialfv(GL_FRONT, GL_DIFFUSE, pencilColor);
        glPushMatrix();
            //glScalef(0.25f, 0.25f, 0.25f);
            glTranslatef(i, 2.5f, 0.0f);
            drawPrism(100, 0.1, 1.3, 0.1, true);
        glPopMatrix();

        //eraser
        glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
        glPushMatrix();
            glTranslatef(i, 3.8f, 0.0f);
            drawPrism(100, 0.1, 0.2, 0.1, true);
        glPopMatrix();
    }

    //paper
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glPushMatrix();
        glTranslatef(3.5f, 2.5f, -0.5f);
        drawPrism(4, 1.5, 0.05, 1.5, true);
    glPopMatrix();

    //cup
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glPushMatrix();
        glTranslatef(4.0f, 2.5f, -3.0f);
        drawPrism(200, 0.35, 1.0, 0.35, false);
    glPopMatrix();

    //water
    glMaterialfv(GL_FRONT, GL_DIFFUSE, water);
    glPushMatrix();
        glTranslatef(4.0f, 2.5f, -3.0f);
        drawPrism(200, 0.30, 0.9, 0.30, true);
    glPopMatrix();

    //straw
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glPushMatrix();
        glTranslatef(4.0f, 2.5f, -3.0f);
        glRotatef(10, 1.0f, 0.0f, 0.0f);
        drawPrism(100, 0.1, 1.5, 0.1, true);
    glPopMatrix();

    //surprise
    glBegin(GL_LINES);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glVertex2f(1.0f, 1.9f);
        glVertex2f(2.0f, 1.9f);

        glVertex2f(1.5f, 1.9f);
        glVertex3f(1.5f, 1.9f, 0.5f);

        glVertex3f(1.0f, 1.9f, 0.5f);
        glVertex3f(2.0f, 1.9f, 0.5f);

        glVertex3f(1.0f, 1.9f, 1.0f);
        glVertex3f(2.0f, 1.9f, 1.0f);

    glEnd(); 

    glFlush();
}

//---------------------------------------------------------------------------------
// The init function sets up the lighting and Eck's trackball camera.
//---------------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    glPushMatrix();
        float lightpos[] = { 15.0f, 15.0f, 15.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glPopMatrix();
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