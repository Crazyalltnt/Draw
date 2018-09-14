#include <cmath>
#include <cstring>
#include <cstdio>

#include "ccc_msw.h"
#include "fig.h"
using namespace std;

const double DEFAULT_XMIN = -10;
const double DEFAULT_YMIN = 10;
const double DEFAULT_XMAX = 10;
const double DEFAULT_YMAX = -10;

GraphicWindow cwin;
extern int ccc_win_main(int); 

void mclock(void);
void DrawPic(HWND hwnd, HDC mainwin_hdc);

long FAR PASCAL ccc_win_proc(HWND hwnd, UINT message, UINT wParam, LONG lParam)
{  
   static int menuId=0;
   PAINTSTRUCT ps;
   HDC mainwin_hdc;
  
   int wmId, wmEvent;
   switch (message)
   {  
    case WM_CREATE:
		  SetTimer(hwnd,1,1000,NULL);
		  break;
	  
	case WM_TIMER:
	      InvalidateRect(hwnd,NULL,TRUE);
		  break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		switch (wmId)
		{
		case IDM_FIG1:
			menuId=IDM_FIG1;
			InvalidateRect(hwnd,NULL,TRUE);
			break;

		case IDM_FIG2:
			menuId=IDM_FIG2;
			InvalidateRect(hwnd,NULL,TRUE);
			break;

		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;		
		}
		break;

	case WM_PAINT:
        mainwin_hdc = BeginPaint(hwnd, &ps);

        if (menuId)
        {             
		   cwin.open(hwnd, mainwin_hdc);		   
		   switch (menuId)
		   {
		   case IDM_FIG1:
			   mclock(); // 绘制时钟
			   break;
		   case IDM_FIG2:
			   DrawPic(hwnd, mainwin_hdc); // 绘制台灯
			   break;
		   }
        }        

        EndPaint(hwnd, &ps);
        break;

	case WM_DESTROY:
       	KillTimer(hwnd,1); 
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
   }
   return 0;
}

/*-------------------------------------------------------------------------*/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR, int nShowCmd)
{  
   MSG msg;
   WNDCLASS wndclass;
 
   if (!hPrevInstance)
   {  
      wndclass.style = CS_HREDRAW | CS_VREDRAW;
      wndclass.lpfnWndProc = ccc_win_proc;
      wndclass.cbClsExtra = 0;
      wndclass.cbWndExtra = 0;
      wndclass.hInstance = hInstance;
      wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
      wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
      wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
      wndclass.lpszMenuName =MAKEINTRESOURCE(IDC_TEST2);
      wndclass.lpszClassName = "CCC_WIN";

      RegisterClass (&wndclass);
   }

   char title[80]="绘图程序-Draw";
   
   HWND hwnd = CreateWindow("CCC_WIN",
      title,
      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
      GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
      NULL,
      NULL,
      hInstance,
      0);

   ShowWindow(hwnd, nShowCmd);
   UpdateWindow(hwnd);

   while (GetMessage(&msg, NULL, 0, 0))
   {  
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return msg.wParam;
}

/*-------------------------------------------------------------------------*/

GraphicWindow::GraphicWindow()
:  _user_xmin(DEFAULT_XMIN),
   _user_ymin(DEFAULT_YMIN),
   _user_xmax(DEFAULT_XMAX),
   _user_ymax(DEFAULT_YMAX)
{    
}

void GraphicWindow::open(HWND hwnd, HDC mainwin_hdc)
{ 
   RECT rect;   
   
   //获取窗口客户区的坐标
   GetClientRect(hwnd, &rect);
   _disp_xmax = rect.right - 1;
   _disp_ymax = rect.bottom - 1;

   _hdc = mainwin_hdc; 

   LOGBRUSH logBrush;  
   logBrush.lbStyle = BS_HATCHED;
   logBrush.lbColor = RGB(0, 192, 192);
   logBrush.lbHatch = HS_CROSS;

   // 获得预定义的笔、画刷或字体
   SelectObject(_hdc, GetStockObject(BLACK_BRUSH));
   //SelectObject(_hdc, CreateBrushIndirect(&logBrush));
   SelectObject(_hdc, GetStockObject(BLACK_PEN));  
   SelectObject(_hdc, GetStockObject(SYSTEM_FONT));
 
   // 获取hwnd设备环境
   HDC hdc = GetDC(hwnd);      
   
   // 释放设备上下文环境（DC）
   ReleaseDC(hwnd, hdc);

   clear();
}

void GraphicWindow::clear()
{  
   // 用背景色（白色）将位图清除干净
   COLORREF color = RGB(255, 255, 255);
   
   //实心刷子：系统用来绘制要填充图形的内部区域的位图
   HBRUSH brush = CreateSolidBrush(color); 
   
   // 选择对象到设备环境
   HBRUSH saved_brush = (HBRUSH)SelectObject(_hdc, brush);

   //用选入设备环境中的刷子绘制给定的矩形区域
   PatBlt(_hdc, 0, 0, _disp_xmax, _disp_ymax, PATCOPY);

   // 恢复原来画刷
   SelectObject(_hdc, saved_brush);
 
   DeleteObject(brush);
}

void GraphicWindow::coord(double xmin, double ymin,
   double xmax, double ymax)
{  
   _user_xmin = xmin;
   _user_xmax = xmax;
   _user_ymin = ymin;
   _user_ymax = ymax;
}

int GraphicWindow::user_to_disp_x(double x) const
{  
   return (int) ((x - _user_xmin) * _disp_xmax / (_user_xmax - _user_xmin));
}

int GraphicWindow::user_to_disp_y(double y) const
{  
   return (int) ((y - _user_ymin) * _disp_ymax / (_user_ymax - _user_ymin));
}

double GraphicWindow::disp_to_user_x(int x) const
{  
   return (double)x * (_user_xmax - _user_xmin) / _disp_xmax + _user_xmin;
}

double GraphicWindow::disp_to_user_y(int y) const
{  
   return (double)y * (_user_ymax - _user_ymin) / _disp_ymax + _user_ymin;
}

void GraphicWindow::point(double x, double y,COLORREF mColor)
{  
   const int POINT_RADIUS = 3;
   int disp_x = user_to_disp_x(x);
   int disp_y = user_to_disp_y(y);
   SelectObject(_hdc, CreatePen(PS_SOLID,1,mColor));
   Ellipse(_hdc, disp_x - POINT_RADIUS, disp_y - POINT_RADIUS,
      disp_x + POINT_RADIUS, disp_y + POINT_RADIUS);
}

void GraphicWindow::ellipse(double x, double y, double ra, double rb,COLORREF mColor)
{
   SelectObject(_hdc, CreatePen(PS_SOLID,1,mColor));
   Ellipse(_hdc, user_to_disp_x(x - ra), user_to_disp_y(y - rb),
      user_to_disp_x(x + ra),user_to_disp_y(y + rb));
}

void GraphicWindow::line(double xfrom,double yfrom,double xto,double yto,COLORREF mColor)
{  
   SelectObject(_hdc, CreatePen(PS_SOLID,2,mColor));
   MoveToEx(_hdc, user_to_disp_x(xfrom), user_to_disp_y(yfrom), 0);
   LineTo(_hdc,user_to_disp_x(xto), user_to_disp_y(yto));
}

void GraphicWindow::text(string s,double x,double y)
{  
   const char* t = s.c_str();
   SetBkMode(_hdc,TRANSPARENT);
   TextOut(_hdc, user_to_disp_x(x), user_to_disp_y(y), t, lstrlen(t));
}

GraphicWindow& GraphicWindow::operator<<(Point p)
{  
	point(p.get_x(), p.get_y(),p.get_color());
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Circle c)
{  
	ellipse(c.get_center().get_x(), c.get_center().get_y(), c.get_radius(), c.get_radius(),c.get_color());
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Line s)
{  
	line(s.get_start().get_x(), s.get_start().get_y(), s.get_end().get_x(), s.get_end().get_y(),s.get_color());
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Message t)
{  
   text(t.get_text(), t.get_start().get_x(), t.get_start().get_y());
   return *this;
}
