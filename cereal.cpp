//---------------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Cuckoo for Coco Puffs (Project #7)
// Due -------- November 10, 2023
//
// The program will draw a table with a photorealistic box of Coco Puffs along
// with a glass of orange juice.  
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.h"
#include <cmath>

//---------------------------------------------------------------------------------
// This function will compute a normal vector for the given vertices. 
//---------------------------------------------------------------------------------
void normalize(float *a, float *b, float *c)
{
    float product[3];
    float v1[3], v2[3];
    for (int j = 0; j < 3; j++) {
        v1[j] = c[j] - a[j];
        v2[j] = b[j] - a[j];
    }
	product[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	product[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	product[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    glNormal3fv(product);
	return;
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
                normalize(points[i], points[i+1], points[i+n]);
                glVertex3fv(points[i]);
                glVertex3fv(points[i+1]);
                glVertex3fv(points[i+1+n]);
                glVertex3fv(points[i+n]);
            }
            //this is for the last side
            else {
                normalize(points[i], points[0], points[i+n]);
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
    float orange[4] = { 1.0f, 0.6f, 0.0f, 1.0f };
    float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float cup[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

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

    //red cup
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cup);
    glPushMatrix();
        glTranslatef(5.0f, 2.5f, -2.0f);
        drawPrism(200, 0.35, 1.25, 0.35, false);
    glPopMatrix();

    //orange juice 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
    glPushMatrix();
        glTranslatef(5.0f, 2.5f, -2.0f);
        drawPrism(200, 0.30, 1.15, 0.30, true);
    glPopMatrix();

	glEnable(GL_TEXTURE_2D);
    //box of cocoa puffs 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
    glRotatef(45, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.0f, 2.5f, 2.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    //Front Face
    glBegin(GL_TRIANGLE_FAN);
	    glNormal3i(0, 0, 1);
        //top right corner 
        glTexCoord2d(0.42, 0.0);      
    	glVertex3i(5, 7, 2);
        //top left corner
    	glTexCoord2d(0.08, 0.0);       
    	glVertex3i(0, 7, 2);
        //bottom left corner 
    	glTexCoord2d(0.08, 0.98);
    	glVertex3i(0, 0, 2);
        //bottom right corner
    	glTexCoord2d(0.42, 0.98);
    	glVertex3i(5, 0, 2);
	glEnd();
    //Right Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(1, 0, 0);
        //top right corner
        glTexCoord2d(0.5, 0.0);
    	glVertex3i(5, 7, 0);
        //top left corner
        glTexCoord2d(0.42, 0.0);
    	glVertex3i(5, 7, 2);
        //bottom left corner
        glTexCoord2d(0.42, 0.98);
    	glVertex3i(5, 0, 2);
        //bottom right corner 
        glTexCoord2d(0.5, 0.98);
    	glVertex3i(5, 0, 0);
	glEnd();
    //Back Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, 0, -1);     
        //top right corner
        glTexCoord2d(0.84, 0.0);
    	glVertex3i(0, 7, 0);
        //top left corner
        glTexCoord2d(0.5, 0.0);
    	glVertex3i(5, 7, 0);
    	//bottom left corner
        glTexCoord2d(0.5, 0.98);
        glVertex3i(5, 0, 0);
        //bottom right corner
        glTexCoord2d(0.84, 0.98);
    	glVertex3i(0, 0, 0);
	glEnd();
    //Left Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(-1, 0, 0);      
        //top right corner
    	glTexCoord2d(0.08, 0.0);
    	glVertex3i(0, 7, 2);
    	//top left corner
        glTexCoord2d(0.0, 0.0);
    	glVertex3i(0, 7, 0);
    	//bottom left corner
        glTexCoord2d(0.0, 0.98);
    	glVertex3i(0, 0, 0);
    	//bottom right corner
        glTexCoord2d(0.08, 0.98);
    	glVertex3i(0, 0, 2);
	glEnd();
    //Top Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, 1, 0);      
        //top right corner
        glTexCoord2d(0.92, 0.68);
    	glVertex3i(5, 7, 0);
    	//top left corner
        glTexCoord2d(0.92, 0.0);
        glVertex3i(0, 7, 0);
        //bottom left corner
        glTexCoord2d(0.84, 0.0);
    	glVertex3i(0, 7, 2);
        //bottom right corner
        glTexCoord2d(0.84, 0.68);
    	glVertex3i(5, 7, 2);
	glEnd();
    //Bottom Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, -1, 0);     
        //top right corner
        glTexCoord2d(1.0, 0.68);
    	glVertex3i(5, 0, 2);
        //top left corner
        glTexCoord2d(1.0, 0.0);
    	glVertex3i(0, 0, 2);
        //bottom left corner
        glTexCoord2d(0.92, 0.0);
    	glVertex3i(0, 0, 0);
        //bottom right corner
        glTexCoord2d(0.92, 0.68);
    	glVertex3i(5, 0, 0);
	glEnd();
    glDisable(GL_TEXTURE_2D);
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
    //Load cocoa puffs image 
    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("cocoapuffs.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    return;
}

//---------------------------------------------------------------------------------
// The main function to drive the program.
//---------------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Cuckoo for Coco Puffs");
    glutDisplayFunc(display);
	init();
    glutMainLoop();
    return 0;
}