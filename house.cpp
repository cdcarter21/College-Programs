//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3233
// Project-----Project #1
// Due---------September 11, 2023
//
// In this project, I will be drawing a simple house using the OpenGL Software.
//------------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
    #include <cmath>
#elif __linux__
    #include <GL/glut.h>
    #include <cmath>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
    #include <cmath>
#endif

//---------------------------------------------------------------------------
// drawCircle()
//---------------------------------------------------------------------------

void drawCircle(float x, float y, float radius){
	float twoPi = 2.0f * 3.14159265359;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(int i = 0; i <= 100; i++) 
			glVertex2f(x + (radius * cos(i * twoPi/100)), y + (radius * sin(i * twoPi/100)));
	glEnd();
}

//---------------------------------------------------------------------------
// display()
//---------------------------------------------------------------------------

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 

    // Enabling blending makes it possible to use the alpha component of the
    // color to control opacity.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //draws the sky
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5f, 0.8f, 0.9f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
    glEnd();

    //draws the base of the house
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.58f, 0.3f, 0.0f);
        glVertex2f(0.75f, -0.5f);
        glVertex2f(-0.75f, -0.5f);
        glVertex2f(0.75f, 0.25f);
        glVertex2f(-0.75f, 0.25f);
	glEnd();

    //draws the roof
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.75f);
        glVertex2f(-0.75f, 0.25f);
        glVertex2f(0.75f, 0.25f);
	glEnd(); 

    //draws the door
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.7f, 0.0f, 0.0f);
        glVertex2f(-0.15f, -0.5f);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(0.15f, -0.1f);
    glEnd();
    //draws the doorknob
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.07f, -0.3f, 0.025f);

    //draws the left window (I used transparency here)
    glBegin(GL_TRIANGLE_STRIP);
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glVertex2f(-0.5f, -0.10f);
        glVertex2f(-0.5f, 0.15f);
        glVertex2f(-0.25f, -0.10f);
        glVertex2f(-0.25f, 0.15f);
	glEnd(); 
    //draws the border of the left window
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.10f);
        glVertex2f(-0.25f, -0.10f);
        glVertex2f(-0.25f, 0.15f);
        glVertex2f(-0.5f, 0.15f);
    glEnd();
    //draws the lines over the window
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.25f, 0.015f);
        glVertex2f(-0.5f, 0.015f);
        glVertex2f(-0.375f, 0.15f);
        glVertex2f(-0.375f, -0.10f);
    glEnd();

    //draws the inside of the right window (I used transparency here)
    glBegin(GL_TRIANGLE_STRIP);
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glVertex2f(0.5f, -0.10f);
        glVertex2f(0.5f, 0.15f);
        glVertex2f(0.25f, -0.10f);
        glVertex2f(0.25f, 0.15f);
    glEnd();
    //draws the border of the right window
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.5f, -0.10f);
        glVertex2f(0.25f, -0.10f);
        glVertex2f(0.25f, 0.15f);
        glVertex2f(0.5f, 0.15f);
    glEnd();
    //draws the lines over the window
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.25f, 0.015f);
        glVertex2f(0.5f, 0.015f);
        glVertex2f(0.375f, 0.15f);
        glVertex2f(0.375f, -0.10f);
    glEnd();

    //draws the sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(-1.0f, 1.0f, 0.4f);

    //draws purple chimney
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5f, 0.0f, 0.5f);
        glVertex2f(0.25f, 0.38f);
        glVertex2f(0.5f, 0.38f);
        glVertex2f(0.25f, 0.75f);
        glVertex2f(0.5f, 0.75f);
    glEnd();

    //draws smoke from chimney (I use transparency here)
    glColor4f(0.5f, 0.5f, 0.5f, 0.75f);
    drawCircle(0.2f, 0.75f, 0.1f);
    drawCircle(0.2f, 0.85f, 0.1f);
    drawCircle(0.3f, 0.85f, 0.1f);
    drawCircle(0.4f, 0.85f, 0.1f);
    drawCircle(0.5f, 0.75f, 0.1f);
    drawCircle(0.35f, 0.75f, 0.1f);
    drawCircle(0.5f, 0.85f, 0.1f);
    drawCircle(0.25f, 0.95f, 0.1f);
    drawCircle(0.35f, 0.95f, 0.1f);
    drawCircle(0.45f, 0.95f, 0.1f);

    //draws left shrub
    glColor3f(0.3f, 0.82f, 0.22f);
    drawCircle(-0.3f, -0.5f, 0.1f);
    drawCircle(-0.4f, -0.4f, 0.1f);
    drawCircle(-0.5f, -0.4f, 0.1f);
    drawCircle(-0.6f, -0.5f, 0.1f);
    drawCircle(-0.45f, -0.5f, 0.1f);

    //draws right shrub
    glColor3f(0.3f, 0.82f, 0.22f);
    drawCircle(0.3f, -0.5f, 0.1f);
    drawCircle(0.4f, -0.4f, 0.1f);
    drawCircle(0.5f, -0.4f, 0.1f);
    drawCircle(0.6f, -0.5f, 0.1f);
    drawCircle(0.45f, -0.5f, 0.1f);

    glFlush();  // Render now
}

//---------------------------------------------------------------------------
// main
//---------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(500, 50);
    glutCreateWindow("Assignment #1");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}