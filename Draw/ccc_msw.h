#ifndef CCC_MSW_H
#define CCC_MSW_H

#include "string"
#include "windows.h"
#include "ccc_shap.h"

using namespace std;

class GraphicWindow
{
public:
   /**
      Default constructor. Constructs a window with the standard 
      coordinate system with corners (-10, -10) and (10, 10).
   */
   GraphicWindow();

   /* Sets the coordinate system of this window. */
   void coord(double xmin, double ymin, double xmax, double ymax);
   
   /* Clears this window.*/
   void clear();

   GraphicWindow& operator<<(Point p);  
   GraphicWindow& operator<<(Circle c);  
   GraphicWindow& operator<<(Line s);
   GraphicWindow& operator<<(Message t);

   /* Opens the window.*/
   void open(HWND hwnd, HDC mainwin_hdc);

private:
   /* Scales an x-coordinate from user to display coordinates.  */
   int user_to_disp_x(double x) const;

   /* Scales a y-coordinate from user to display coordinates.*/
   int user_to_disp_y(double y) const;

   /* Scales an x-coordinate from display to user coordinates.*/
   double disp_to_user_x(int x) const;

   /* Scales an y-coordinate from display to user coordinates.*/
   double disp_to_user_y(int y) const;  

   /* Plots a point.*/
   void point(double x, double y,COLORREF mColor);
   
   /* Plots a line. */
   void line(double xfrom, double yfrom, double xto, double yto,COLORREF mColor);
   
   /* Plots a ellipse. */
   void ellipse(double x, double y, double ra, double rb,COLORREF mColor);
   
   /* Plots text. */
   void text(string t, double x, double y);

   double _user_xmin; // the user's window's logical window coords
   double _user_xmax;
   double _user_ymin;
   double _user_ymax;
   int _disp_xmax; // the physical window dimension (in pixels)
   int _disp_ymax;  

   HDC _hdc; // device context to the display 
};

extern GraphicWindow cwin;

#endif
