//---------------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Exam #2
// Due -------- November 15, 2023
//
// The program will draw a 1960s television that is tuned in to the Andy Griffith
// show. 
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
// This function will draw a cube using the vertices passed in.
//---------------------------------------------------------------------------------
void drawCube(float v[]) {
    //Front Face
    glBegin(GL_TRIANGLE_FAN);
	    glNormal3i(0, 0, 1);
        //top right corner 
    	glVertex3f(v[1], v[3], v[5]);      
        //top left corner
    	glVertex3f(v[0], v[3], v[5]);       
        //bottom left corner 
    	glVertex3f(v[0], v[2], v[5]);   
        //bottom right corner
    	glVertex3f(v[1], v[2], v[5]);  
	glEnd();
    //Right Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(1, 0, 0);
        //top right corner
    	glVertex3f(v[1], v[3], v[4]); 
        //top left corner
    	glVertex3f(v[1], v[3], v[5]);     
        //bottom left corner
    	glVertex3f(v[1], v[2], v[5]);    
        //bottom right corner 
    	glVertex3f(v[1], v[2], v[4]);     
	glEnd();
    //Back Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, 0, -1);     
        //top right corner
    	glVertex3f(v[0], v[3], v[4]);        
        //top left corner
    	glVertex3f(v[1], v[3], v[4]);       
    	//bottom left corner
        glVertex3f(v[1], v[2], v[4]);    
        //bottom right corner
    	glVertex3f(v[0], v[2], v[4]);      
	glEnd();
    //Left Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(-1, 0, 0);      
        //top right corner
    	glVertex3f(v[0], v[3], v[5]);        
    	//top left corner
    	glVertex3f(v[0], v[3], v[4]);       
    	//bottom left corner
    	glVertex3f(v[0], v[2], v[4]);      
    	//bottom right corner
    	glVertex3f(v[0], v[2], v[5]);     
	glEnd();
    //Top Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, 1, 0);            
        //top right corner
    	glVertex3f(v[1], v[3], v[4]);       
    	//top left corner
        glVertex3f(v[0], v[3], v[4]);         
        //bottom left corner
    	glVertex3f(v[0], v[3], v[5]);       
        //bottom right corner
    	glVertex3f(v[1], v[3], v[5]);       
	glEnd();
    //Bottom Face
	glBegin(GL_TRIANGLE_FAN);
    	glNormal3i(0, -1, 0);     
        //top right corner
    	glVertex3f(v[1], v[2], v[5]);    
        //top left corner
    	glVertex3f(v[0], v[2], v[5]);     
        //bottom left corner
    	glVertex3f(v[0], v[2], v[4]);      
        //bottom right corner
    	glVertex3f(v[1], v[2], v[4]);    
	glEnd();
    return; 
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

	cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);  
	cameraApply();

    //the colors i will be using for my objects
    float tv[4] = { 0.63f, 0.4f, 0.18f, 1.0f };
    float leg[4] = { 0.7f, 0.5f, 0.4f, 1.0f };
    float cup[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float gray[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

    //draw tv
    glScalef(0.3f, 0.3f, 0.3f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tv);
    float tvPoints[6] = {
        0.0f, 5.0f, 1.0f, 5.0f, 0.0f, 5.0f
    };
    drawCube(tvPoints);

    //draw front left leg 
    float flLeg[6] = {
        0.0f, 1.0f, 0.0f, 1.0f, 4.0f, 5.0f
    };
    drawCube(flLeg);

    //draw front right leg 
    float frLeg[6] = {
        4.0f, 5.0f, 0.0f, 1.0f, 4.0f, 5.0f
    };
    drawCube(frLeg);

    //draw back right leg 
    float brLeg[6] = {
        4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    drawCube(brLeg);

    //draw back left leg 
    float blLeg[6] = {
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    drawCube(blLeg);

    //left button
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
    glPushMatrix();
        glTranslatef(1.5f, 1.5f, 5.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        drawPrism(200, 0.35, 0.35, 0.35, true);
    glPopMatrix();

    //right button
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
    glPushMatrix();
        glTranslatef(3.5f, 1.5f, 5.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        drawPrism(200, 0.35, 0.35, 0.35, true);
    glPopMatrix();

    //Draw tv screen 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_FAN);
	    glNormal3i(0, 0, 1);
        //top right corner 
        glTexCoord2d(1.0, 0.0);      
    	glVertex3f(4.0f, 4.0f, 5.1f);
        //top left corner
    	glTexCoord2d(0.0, 0.0);       
    	glVertex3i(1.0f, 4.0f, 5.1f);
        //bottom left corner 
    	glTexCoord2d(0.0, 0.73);
    	glVertex3i(1.0f, 2.0f, 5.1f);
        //bottom right corner
    	glTexCoord2d(1.0, 0.73);
    	glVertex3i(4.0f, 2.0f, 5.1f);
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
    //Load andy griffith image 
    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("andy_griffith.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
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
    glutCreateWindow("You ain't seen the last of Ernest T. Bass!");
    glutDisplayFunc(display);
	init();
    glutMainLoop();
    return 0;
}