//---------------------------------------------------------------------------------
// Developer -- Cole Carter
// Course ----- CS3233
// Project ---- Homework #8 
// Due -------- December 1, 2023
//
// The program will draw a given object from an object file and 
// add a slight rotation animation.
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std; 

//this will be the variable for the name of the object file
string fileName;

//these variables will be used in glOrtho to adapt the screen for larger objects
float largest_neg_y, largest_pos_y, largest_neg_x, largest_pos_x, largest_neg_z, largest_pos_z = 0.0f; 

//---------------------------------------------------------------------------------
// The display function is where we will be interpreting the object file and
// then drawing it.
//---------------------------------------------------------------------------------
void display() {   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //this will adapt the screen for larger objects
    glOrtho(largest_neg_x-3.0f, largest_pos_x+3.0f, largest_neg_y-3.0f, largest_pos_y+3.0f, largest_neg_z-100.0f, largest_pos_z+100.0f);
    glMatrixMode(GL_MODELVIEW);

    //slight rotation for our animation
    glRotatef(1.0f, 0.0f, 1.0f, 0.0f);

    //vectors to hold the vertices and normals from the object file
    vector<float> vertex_x, vertex_y, vertex_z;  
    vector<float> text_x, text_y;
    vector<float> normal_x, normal_y, normal_z;  

    //these vectors will hold the indices from the face lines
    vector<int> vertex_num, text_num, normal_num; 

    stringstream ss; 
    ifstream in_file(fileName);
    string line = "";  
    string prefix = "";

    //temp variables
    float temp_x, temp_y, temp_z; 
    int temp_int = 0; 

    //loop through the object file
    while (getline(in_file, line)) {
        ss.clear(); 
        ss.str(line);
        ss >> prefix; 

        if (prefix == "v") { //vertex position
            ss >> temp_x >> temp_y >> temp_z; 
            //these if statements are for the controlling of glOrtho
            if (temp_x < largest_neg_x)
                largest_neg_x = temp_x; 
            if (temp_x > largest_pos_x)
                largest_pos_x = temp_x; 
            if (temp_y < largest_neg_y)
                largest_neg_y = temp_y; 
            if (temp_y > largest_pos_y)
                largest_pos_y = temp_y; 
            if (temp_z < largest_neg_z)
                largest_neg_z = temp_z; 
            if (temp_z > largest_pos_z)
                largest_pos_z = temp_z; 
            vertex_x.push_back(temp_x); 
            vertex_y.push_back(temp_y); 
            vertex_z.push_back(temp_z); 
        }
        else if (prefix == "vt") { //texture coordinates
            ss >> temp_x >> temp_y; 
            text_x.push_back(temp_x); 
            text_y.push_back(temp_y); 
        }
        else if (prefix == "vn") { //normals
            ss >> temp_x >> temp_y >> temp_z; 
            normal_x.push_back(temp_x); 
            normal_y.push_back(temp_y); 
            normal_z.push_back(temp_z); 
        }
        else if (prefix == "f") {
            int counter = 0; 
            //loop through each number on the line
            while (ss >> temp_int) {
                //the counter variable is used to see which part of the three
                //number series we are reading in 
                if (counter == 0)
                    vertex_num.push_back(temp_int);
                else if (counter == 1)
                    text_num.push_back(temp_int);
                else if (counter == 2)
                    normal_num.push_back(temp_int);

                //ignore the slashes and spaces
                if (ss.peek() == '/') {
                    counter++; 
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ') {
                    counter++; 
                    ss.ignore(1, ' ');
                }
                //reset the counter 
                if (counter > 2) {
                    counter = 0; 
                }
            }

            float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
            glBegin(GL_TRIANGLE_FAN); 
                //draw all the vertices for the face  
                for (int i=0; i<vertex_num.size(); i++) {
                    //we grab the x, y, and z coordinates from our vectors using 
                    //the indices we put in our other vectors
                    glNormal3f(normal_x[normal_num[i]-1], normal_y[normal_num[i]-1], normal_z[normal_num[i]-1]);
                    glVertex3f(vertex_x[vertex_num[i]-1], vertex_y[vertex_num[i]-1], vertex_z[vertex_num[i]-1]);
                }
            glEnd();
            //clear the vectors to be used again for the next face 
            vertex_num.clear(); 
            normal_num.clear(); 
        }
    }
    glFlush(); 
}

//-------------------------------------------------------------------------------
// Initialize posting redisplay events.
//-------------------------------------------------------------------------------
void timer(int unused)
{
    glutPostRedisplay();
    glutTimerFunc(17, timer, 0);
}

//---------------------------------------------------------------------------------
// The init function sets up the lighting and Eck's trackball camera.
//---------------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    return;
}

//---------------------------------------------------------------------------------
// The main function to drive the program.
//---------------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Turn! Turn! Turn!");
   
    //get object file from the user 
    cout << "Object File Name: "; 
    cin >> fileName; 

    glutDisplayFunc(display);
	init();
    timer(0);
    glutMainLoop();
    return 0;
}