//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3233
// Project-----Project #2
// Due---------September 20, 2023
//
// In this project, I use matrix multiplication to represent the transformation
// of an (x, y) coordinate. 
//------------------------------------------------------------------------------

#include <cmath>
#include <iostream>
using namespace std; 

void transform(float matrix[0][3], float vector[0][1]) {
    float resultant[3][1]; 
    resultant[0][0] = (matrix[0][0] * vector[0][0]) + (matrix[0][1] * vector[1][0]) + (matrix[0][2] * vector[2][0]);
    resultant[1][0] = (matrix[1][0] * vector[0][0]) + (matrix[1][1] * vector[1][0]) + (matrix[1][2] * vector[2][0]);
    resultant[2][0] = (matrix[2][0] * vector[0][0]) + (matrix[2][1] * vector[1][0]) + (matrix[2][2] * vector[2][0]);

    cout << endl << "Your new (x, y) coordinate is: " << resultant[0][0] << ", " << resultant[1][0] << endl; 
}

void translate(float x, float y, float e, float f) {
    float matrix[3][3] = {0};
    matrix[0][0] = 1;
    matrix[0][2] = e; 
    matrix[1][1] = 1; 
    matrix[1][2] = f;
    matrix[2][2] = 1; 

    float vector[3][1];
    vector[0][0] = x; 
    vector[1][0] = y; 
    vector[2][0] = 1; 

    transform(matrix, vector);
}

void rotate(float x, float y, float degrees) {
    float radians = degrees*(3.14159265359/180);
    float matrix[3][3] = {0};
    matrix[0][0] = cos(radians);
    matrix[0][1] = -sin(radians);
    matrix[1][0] = sin(radians); 
    matrix[1][1] = matrix[0][0];
    matrix[2][2] = 1; 

    float vector[3][1];
    vector[0][0] = x; 
    vector[1][0] = y; 
    vector[2][0] = 1; 

    transform(matrix, vector);
}

void scale(float x, float y, float a, float d) {
    float matrix[3][3] = {0};
    matrix[0][0] = a;
    matrix[1][1] = d; 
    matrix[2][2] = 1; 

    float vector[3][1];
    vector[0][0] = x; 
    vector[1][0] = y; 
    vector[2][0] = 1; 

    transform(matrix, vector);
}

int main()
{
    float x, y, scaleX, scaleY, degrees; 
    string transform; 
    cout << "Please enter the x coordinate: ";
    cin >> x;
    cout << "Please enter the y coordinate: ";
    cin >> y; 
    cout << endl << "Would you like to translate, rotate, or scale your point? ";
    cin >> transform; 
    if (transform == "rotate") {
        cout << endl << "What degrees would you like to rotate your point? ";
        cin >> degrees; 
        cout << endl; 
        rotate(x, y, degrees);
    }
    else if (transform == "translate") {
        cout << endl << "How far would you like to translate x? ";
        cin >> scaleX;
        cout << "How far would you like to translate y? ";
        cin >> scaleY;
        translate(x, y, scaleX, scaleY);
    }
    else if (transform == "scale") {
        cout << endl << "What is the scaling factor for x? ";
        cin >> scaleX;
        cout << "What is the scaling factor for y? ";
        cin >> scaleY;
        scale(x, y, scaleX, scaleY);
    }    
    else
        cout << "Invalid Input. Please try again." << endl; 
}