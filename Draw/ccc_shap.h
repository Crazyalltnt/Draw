#ifndef CCC_SHAP_H
#define CCC_SHAP_H

#include "string"
#include "windows.h"
using namespace std;

class Shape
{ 
public:	 
	 virtual void move(double dx, double dy)=0;	
	 virtual void SetColor(COLORREF mColor)=0;
};

class Point:public Shape
{
public:
   Point();
   Point(double x1, double y1);
   double get_x() const;
   double get_y() const;
   COLORREF get_color() const;

   virtual void move(double dx, double dy);
   virtual void SetColor(COLORREF mColor);
private:
   double x;
   double y;
   COLORREF color;
};

class Circle:public Shape
{
public:
   Circle();
   Circle(Point p, double r);
   Point get_center() const;
   double get_radius() const;
   COLORREF get_color() const;

   virtual void move(double dx, double dy);
   virtual void SetColor(COLORREF mColor);
private:
   Point center;
   double radius;
   COLORREF color;
};

class Line:public Shape
{
public:
   Line();
   Line(Point p1, Point p2);
   Point get_start() const;
   Point get_end() const;
   COLORREF get_color() const;

   virtual void move(double dx, double dy);
   virtual void SetColor(COLORREF mColor);
private:
   Point from;
   Point to;
   COLORREF color;
};

/**
   A message that is placed at a given point in the plane.
*/
class Message
{
public:
   
   // Constructs an empty message at the origin.   
   Message();
   // Constructs a message that displays the value of a number.
   Message(Point s, double x);
   // Constructs a message that displays a string
   Message(Point s, const string& m);
   Point get_start() const;
   string get_text() const;

   virtual void move(double dx, double dy); 
private:
   Point start;
   string text;
};
#endif
