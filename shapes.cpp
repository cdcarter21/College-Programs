#include <iostream>
#include <cmath>
#include <sstream>
#include "shapes.h"
using namespace std;

//The shape constructor simply stores the parameter into the color member variable.
Shape::Shape(string c) { color = c; }
//This getter function simply returns the string in color.
string Shape::getColor() { return color; }
//This setter function simply sets the color variable to whatever the parameter is.
void Shape::setColor(string c) { color = c; }

//the Box constructor stores the color parameter using the Shape constructor and the rest of the parameters are stored in their respective member variables.
Box::Box(string c, double l, double t, double r, double b)
    : Shape(c)
{
    left = l;
    top = t;
    right = r; 
    bottom = b;
}
//these simple setter functions just set the variable in the method name to whatever the parameter is. 
void Box::setLeft(double l) { left = l; }
void Box::setRight(double r) { right = r; }
void Box::setTop(double t) { top = t; }
void Box::setBottom(double b) { bottom = b; }

//these simple getter functions just return the value of the variable in the method name. 
double Box::getLeft() { return left; }
double Box::getRight() { return right; }
double Box::getTop() { return top; }
double Box::getBottom() { return bottom; }

double Box::getArea()
{
    //since the area of a box is just width multiplied by height, I did so by multiplying 
    //the absolute value of the difference of the right and left coordinates (the width) and 
    //the absolute value of the difference of the top and bottom coordinates (the height) and returning the product.
    double area = abs(right-left) * abs(top-bottom);
    return area;
}
double Box::getPerimeter()
{
    //Since the perimeter of a box is just adding up all the sides, I find the height and width by calculating
    //the absolute value of the difference of the top and bottom coordinates for height 
    //and the absolute value of the difference of the right and left coordinates for width. 
    //I then multiplied height by 2, did the same for width, added those together, and returned the value. 
    double height = abs(top-bottom);
    double width = abs(right-left);
    double peri = (height * 2) + (width * 2);
    return peri;
}

void Box::move(double horizontal, double vertical)
{
    //Since the first parameter determines whether the box moves left or right, I add the value to the left and right variables. 
    //Since the second parameter determines whether the box moves up or down, I add the value to the top and bottom variables. 
    left += horizontal;
    right += horizontal;
    top += vertical;
    bottom += vertical;
}
void Box::render(ostream &out)
{
    //simply prints out all the points and the fill color according to the assignment format.
    out << "<rect x=\"" << left << "\" y=\"" << top << "\" width=\"" << abs(right-left) << "\" height=\"" << bottom-top << "\" fill=\"" << color << "\" />";
}

//The Circle constructor stores the color in the Shape class by calling the Shape constructor. 
//Then the rest of the parameters are stored within their respective member variables.
Circle::Circle(string c, double x, double y, double r)
    : Shape(c)
{
    centerX = x;
    centerY = y;
    radius = r;
}
//these simple setter functions just set the variable in the method name to whatever the parameter is. 
void Circle::setCenterX(double x) { centerX = x; }
void Circle::setCenterY(double y) { centerY = y; }
void Circle::setRadius(double r) { radius = r; }

//these simple getter functions return the value of the variable in the method name. 
double Circle::getCenterX() { return centerX; }
double Circle::getCenterY() { return centerY; }
double Circle::getRadius() { return radius; }

double Circle::getArea()
{
    //the area of a circle is pi * radius^2. Since we can't raise variables to an exponent in C++, I simply multiplied radius by itself
    //and multiplied that by pi, using M_PI in the <cmath> header and return the value.
    double area = M_PI * (radius * radius);
    return area;
}
double Circle::getPerimeter()
{
    //the perimeter (circumference) of a circle is 2 * pi * radius. So that is exactly what I did here by using M_PI in the <cmath> header for pi and returning the value.
    double perimeter = 2 * M_PI * radius;
    return perimeter;
}
void Circle::move(double horizontal, double vertical)
{
    //Since the first parameter determines if the circle moves left or right, I add it to the centerX variable. 
    //Since the second parameter determines if the circle moves up or down, I add it to the centerY variable.
    centerX += horizontal;
    centerY += vertical;
}
void Circle::render(ostream &out)
{
    //simply prints out all the variables according to the assignment format.
    out << "<circle cx=\"" << centerX << "\" cy=\"" << centerY << "\" r=\"" << radius << "\" fill=\"" << color << "\" />";
}

//The Triangle constructor stores the color parameter using the Shape constructor and the other parameters are stored in the x and y variables.
Triangle::Triangle(string c, double xOne, double yOne, double xTwo, double yTwo, double xThree, double yThree)
    : Shape(c)
{
    x1 = xOne;
    y1 = yOne;
    x2 = xTwo;
    y2 = yTwo;
    x3 = xThree;
    y3 = yThree;
}
//These simple setter functions just set the variable in the method name to whatever the parameter is.
void Triangle::setCornerX1(double xOne) { x1 = xOne; }
void Triangle::setCornerY1(double yOne) { y1 = yOne; }
void Triangle::setCornerX2(double xTwo) { x2 = xTwo; }
void Triangle::setCornerY2(double yTwo) { y2 = yTwo; }
void Triangle::setCornerX3(double xThree) { x3 = xThree; }
void Triangle::setCornerY3(double yThree) { y3 = yThree; }


//These simple getter functions just return the value of the variable in the method name.
double Triangle::getCornerX1() { return x1; }
double Triangle::getCornerY1() { return y1; }
double Triangle::getCornerX2() { return x2; }
double Triangle::getCornerY2() { return y2; }
double Triangle::getCornerX3() { return x3; }
double Triangle::getCornerY3() { return y3; }

double Triangle::getArea()
{
    /*A triange's area is 1/2 * base * height. So I use some if statements to figure out which y-coordinate
    is the heighest and which is the lowest in order to find the height. Once I find the heighest and lowest,
    I subtract those y-coordinates and find the absolute value to get the height.*/
    //Then I found the base by substracting the two base x coordinates and finding the absolute value.
    //Lastly, I multiplied those variables by 0.5 to find the area for this triangle.
    double heighest = 0;
    double lowest = 0;
    if (y1>y2 && y1>y3)
        heighest = y3;
    else if (y2>y1 && y2>y3)
        heighest = y2;
    else
        heighest = y3;

    if (y3<y1 && y3<y2)
        lowest = y3;
    else if (y2<y1 && y2<y3)
        lowest = y2;
    else
        lowest = y1;
    double height = abs(heighest-lowest);
    double base = abs(x2-x1);
    double area = 0.5 * base * height;
    return area; 
}

double Triangle::getPerimeter()
{
    //To find the perimeter we need to add up all the sides, but we are only given points. 
    //So I used the distance formula to find the length for each side. 
    //side1to2 is the side between x1,y1 and x2,y2. side2to3 between x2,y2 and x3,y3 and so on.
    double side1to2 = sqrt(((abs(x2-x1)) * (abs(x2-x1))) + ((abs(y2-y1)) * (abs(y2-y1))));
    double side2to3 = sqrt(((abs(x3-x2)) * (abs(x3-x2))) + ((abs(y3-y2)) * (abs(y3-y2))));
    double side3to1 = sqrt(((abs(x3-x1)) * (abs(x3-x1))) + ((abs(y3-y1)) * (abs(y3-y1))));
    double perimeter = side1to2 + side2to3 + side3to1;
    return perimeter;
}

void Triangle::move(double horizontal, double vertical)
{
    //the first parameter determines if the points move right or left, so I add that parameter to all the x variables.
    //the second parameter determines if the points move up or down, so I add that parameter to all the y variables.
    x1 += horizontal;
    x2 += horizontal;
    x3 += horizontal;
    y1 += vertical;
    y2 += vertical;
    y3 += vertical;
}

void Triangle::render(ostream &out)
{
    //simply prints out all the points and the fill color according to the assignment format.
    out << "<polygon points=\"" << x1 << "," << y1 << " " << x2 << "," << y2 << " " << x3 << "," << y3 << "\" fill=\"" << color << "\" />";
}