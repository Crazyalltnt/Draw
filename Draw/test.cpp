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

	cwin<<Message(Point(-1,7),"�ᶯʱ��");

	/* ������ */
    int radius=6;	
	Point org(0,0);
	
	pShape=&org;
	pShape->SetColor(RGB(255,255,255)); // ��ɫ
	cwin<<org;
	
	Circle clkPlate(org,radius);
	pShape=&clkPlate;
	pShape->SetColor(RGB(0,0,255));	// ��ɫ
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

	/* ������ */
	struct tm local;
	time_t t;
	
	// ��ȡϵͳ����ʱ��
	t=time(NULL); 

	// ������ʱ��ת��Ϊ����ʱ��
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

	hLine.SetColor((RGB(255,0,0)));		// ��ɫ 
	mLine.SetColor((RGB(0,255,0)));		// ��ɫ
	sLine.SetColor((RGB(255,255,0)));	// ��ɫ
	cwin<<hLine<<mLine<<sLine<<org;
}

void DrawPic(HWND hwnd, HDC hdc)
{
	// ��ÿͻ�����
	RECT r;
	GetClientRect(hwnd, &r);

	// ����ӳ��ģʽ
	SetMapMode(hdc, MM_ISOTROPIC);

	// ���ô������귶Χ
	SetWindowExtEx(hdc, 600, 450, NULL);

	// �����ӿ����귶Χ
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);

	HBRUSH brush, BlueBrush, YellowBrush;

	Ellipse(hdc, 220, 240, 420, 344); //�µ���
	SelectObject(hdc, GetStockObject(LTGRAY_BRUSH)); //ѡ��ˢ
	Rectangle(hdc, 275, 99, 295, 206);	//��֧��

	//����
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
	Ellipse(hdc, 155, 60, 435, 100); //�µ���
	BlueBrush = CreateSolidBrush(RGB(0, 0, 255)); //�Զ�����ɫ��ˢ
	brush = (HBRUSH)SelectObject(hdc, BlueBrush);
	Ellipse(hdc, 145, 53, 445, 92);	//�ϵ���
	Ellipse(hdc, 220, 235, 420, 339); //�ϵ���
	Rectangle(hdc, 269, 206, 300, 276);	//��֧��

	Rectangle(hdc, 333, 229,379, 251);	//���ӵ���
	Ellipse(hdc, 326, 170, 386, 230); //�������
	SelectObject(hdc, brush); //�ָ�ԭ����ˢ
	
	SelectObject(hdc, CreateSolidBrush(RGB(255 ,255, 0)));
	Ellipse(hdc, 345, 284, 377, 306); //������Ӱ

	//��ǩ							  
	SetBkColor(hdc, RGB(0, 0, 255)); // �������ֱ���ɫ
	SetTextColor(hdc, RGB(0, 0, 0)); // ����������ɫ
	TextOut(hdc, 260, 290, TEXT("BUPT����"), lstrlen(TEXT("BUPT����"))); 

	YellowBrush = CreateSolidBrush(RGB(255, 255, 40)); //�Զ����ɫ��ˢ
	brush = (HBRUSH)SelectObject(hdc, YellowBrush);
	Ellipse(hdc, 345, 283, 377, 305); //����
	SelectObject(hdc, brush); //�ָ�ԭ����ˢ

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));//���2�ĺ�ɫ����
	Arc(hdc, 70, 198, 260, 270, 260, 265, 165, 198); //��Դ��

	//��ͷ
	Rectangle(hdc, 150, 193, 165, 203);
	MoveToEx(hdc, 145, 196, NULL);
	LineTo(hdc, 150, 196);
	MoveToEx(hdc, 145, 200, NULL);
	LineTo(hdc, 150, 200);

	DeleteObject(brush);//ɾ����ˢ

	Shape *pShape;

	cwin << Message(Point(-1, 9), "�ҵ�̨��");

	/* ������ */
	double radius = 0.85;
	Point org(1.65, 2.96);
	pShape = &org;
	pShape->SetColor(RGB(255, 255, 255)); // ��ɫ
	cwin << org;

	SelectObject(hdc, CreateHatchBrush(4, RGB(147, 112, 219)));

	Circle clkPlate(org, radius);
	pShape = &clkPlate;
	pShape->SetColor(RGB(255, 255, 255));	// ��ɫ
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

	/* ������ */
	struct tm local;
	time_t t;

	// ��ȡϵͳ����ʱ��
	t = time(NULL);

	// ������ʱ��ת��Ϊ����ʱ��
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

	hLine.SetColor((RGB(255, 0, 0)));		// ��ɫ 
	mLine.SetColor((RGB(0, 255, 0)));		// ��ɫ
	sLine.SetColor((RGB(255, 255, 0)));	// ��ɫ
	cwin << hLine << mLine << sLine << org;
}