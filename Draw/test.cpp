#include "ctime"
#include "cmath"
#include "cstdlib"
#include "fig.h"
#include "ccc_win.h"

#define PI 3.1415926
#define POINT_NUM 1000
#define DOUBLE_PI 2*3.1415926
struct pPoint
{
	int x, y;
};

void mclock()
{
	Shape *pShape;

	cwin<<Message(Point(-1,7),"会动时钟");

	/* 画表盘 */
    int radius=6;	
	Point org(0,0);
	
	pShape=&org;
	pShape->SetColor(RGB(255,255,255)); // 白色
	cwin<<org;
	
	Circle clkPlate(org,radius);
	pShape=&clkPlate;
	pShape->SetColor(RGB(0,0,255));	// 蓝色
	cwin<<clkPlate;
	
	double x,y,x_s,y_s,x_m,y_m,x_h,y_h;
	int i;
	for(i=0;i<12;i++)
	{		
		x=0.9*radius*sin(PI*i/6);
		y=0.9*radius*cos(PI*i/6);

		Point mPoint(x,y);
		pShape=&mPoint;
		pShape->SetColor((RGB(255,255,255)));
		cwin<<mPoint;
	}

	/* 画表针 */
	struct tm local;
	time_t t;
	
	// 获取系统日历时间
	t=time(NULL); 

	// 将日历时间转化为本地时间
	localtime_s(&local,&t);

	x_s=0.89*radius*sin(PI*(local.tm_sec)/30);
	y_s=0.89*radius*cos(PI*(local.tm_sec)/30);

	x_m=0.7*radius*sin(PI*(local.tm_min)/30);
	y_m=0.7*radius*cos(PI*(local.tm_min)/30);

	//x_h=0.5*radius*sin(PI*(local.tm_hour)/6);
	//y_h=0.5*radius*cos(PI*(local.tm_hour)/6);

	x_h=0.5*radius*sin(2*PI/12*(local.tm_hour)+2*PI/60*(local.tm_min/12));
	y_h=0.5*radius*cos(2*PI/12*(local.tm_hour)+2*PI/60*(local.tm_min/12));
	
	Point hEnd(x_h,y_h),mEnd(x_m,y_m),sEnd(x_s,y_s);
	Line hLine(org,hEnd),mLine(org,mEnd),sLine(org,sEnd);

	hLine.SetColor((RGB(255,0,0)));		// 红色 
	mLine.SetColor((RGB(0,255,0)));		// 绿色
	sLine.SetColor((RGB(255,255,0)));	// 黄色
	cwin<<hLine<<mLine<<sLine<<org;
}

void DrawPic(HWND hwnd, HDC hdc)
{
	// 获得客户区域
	RECT r;
	GetClientRect(hwnd, &r);

	// 设置映像模式
	SetMapMode(hdc, MM_ISOTROPIC);

	// 设置窗口坐标范围
	SetWindowExtEx(hdc, 600, 450, NULL);

	// 设置视口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);

	HBRUSH brush, BlueBrush, YellowBrush;

	Ellipse(hdc, 220, 240, 420, 344); //下底座
	SelectObject(hdc, GetStockObject(LTGRAY_BRUSH)); //选画刷
	Rectangle(hdc, 275, 99, 295, 206);	//上支架

	//褶皱
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(127, 127, 127)));
	int j = 105;
	for (int i = 0; i < 10; i++)
	{
		MoveToEx(hdc, 276, j, NULL);
		LineTo(hdc, 294, j);
		j += 5;
	}
	SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(127, 127, 127)));
	for (int i = 0; i < 6; i++)
	{
		MoveToEx(hdc, 276, j, NULL);
		LineTo(hdc, 294, j);
		j += 7;
	}
	
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Ellipse(hdc, 155, 60, 435, 100); //下灯罩
	BlueBrush = CreateSolidBrush(RGB(0, 0, 255)); //自定义蓝色画刷
	brush = (HBRUSH)SelectObject(hdc, BlueBrush);
	Ellipse(hdc, 145, 53, 445, 92);	//上灯罩
	Ellipse(hdc, 220, 235, 420, 339); //上底座
	Rectangle(hdc, 269, 206, 300, 276);	//下支架

	Rectangle(hdc, 333, 229,379, 251);	//闹钟底座
	Ellipse(hdc, 326, 170, 386, 230); //闹钟外壳
	SelectObject(hdc, brush); //恢复原来画刷
	
	SelectObject(hdc, CreateSolidBrush(RGB(255 ,255, 0)));
	Ellipse(hdc, 345, 284, 377, 306); //开关阴影

	//标签							  
	SetBkColor(hdc, RGB(0, 0, 255)); // 设置文字背景色
	SetTextColor(hdc, RGB(0, 0, 0)); // 设置文字颜色
	TextOut(hdc, 260, 290, TEXT("BUPT灯饰"), lstrlen(TEXT("BUPT灯饰"))); 

	YellowBrush = CreateSolidBrush(RGB(255, 255, 40)); //自定义黄色画刷
	brush = (HBRUSH)SelectObject(hdc, YellowBrush);
	Ellipse(hdc, 345, 283, 377, 305); //开关
	SelectObject(hdc, brush); //恢复原来画刷

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));//宽度2的黑色画笔
	Arc(hdc, 70, 198, 260, 270, 260, 265, 165, 198); //电源线

	//插头
	Rectangle(hdc, 150, 193, 165, 203);
	MoveToEx(hdc, 145, 196, NULL);
	LineTo(hdc, 150, 196);
	MoveToEx(hdc, 145, 200, NULL);
	LineTo(hdc, 150, 200);

	DeleteObject(brush);//删除画刷

	Shape *pShape;

	cwin << Message(Point(-1, 9), "我的台灯");

	/* 画表盘 */
	double radius = 0.85;
	Point org(1.65, 2.96);
	pShape = &org;
	pShape->SetColor(RGB(255, 255, 255)); // 白色
	cwin << org;

	SelectObject(hdc, CreateHatchBrush(4, RGB(147, 112, 219)));

	Circle clkPlate(org, radius);
	pShape = &clkPlate;
	pShape->SetColor(RGB(255, 255, 255));	// 白色
	cwin << clkPlate;

	double x, y, x_s, y_s, x_m, y_m, x_h, y_h;
	int i;
	for (i = 0; i<12; i++)
	{
		x = 1.65 + 0.9*radius*sin(PI*i / 6);
		y = 2.96 + 0.9*radius*cos(PI*i / 6);

		Point mPoint(x, y);
		pShape = &mPoint;
		pShape->SetColor((RGB(255, 255, 255)));
		cwin << mPoint;
	}

	/* 画表针 */
	struct tm local;
	time_t t;

	// 获取系统日历时间
	t = time(NULL);

	// 将日历时间转化为本地时间
	localtime_s(&local, &t);

	x_s = 1.65 + 0.89*radius*sin(PI*(local.tm_sec) / 30);
	y_s = 2.96 + 0.89*radius*cos(PI*(local.tm_sec) / 30);

	x_m = 1.65 + 0.7*radius*sin(PI*(local.tm_min) / 30);
	y_m = 2.96 + 0.7*radius*cos(PI*(local.tm_min) / 30);

	//x_h=0.5*radius*sin(PI*(local.tm_hour)/6);
	//y_h=0.5*radius*cos(PI*(local.tm_hour)/6);

	x_h = 1.65 + 0.5*radius*sin(2 * PI / 12 * (local.tm_hour) + 2 * PI / 60 * (local.tm_min / 12));
	y_h = 2.96 + 0.5*radius*cos(2 * PI / 12 * (local.tm_hour) + 2 * PI / 60 * (local.tm_min / 12));

	Point hEnd(x_h, y_h), mEnd(x_m, y_m), sEnd(x_s, y_s);
	Line hLine(org, hEnd), mLine(org, mEnd), sLine(org, sEnd);

	hLine.SetColor((RGB(255, 0, 0)));		// 红色 
	mLine.SetColor((RGB(0, 255, 0)));		// 绿色
	sLine.SetColor((RGB(255, 255, 0)));	// 黄色
	cwin << hLine << mLine << sLine << org;
}