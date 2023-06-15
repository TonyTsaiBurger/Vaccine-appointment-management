#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>//检测字符
#include<graphics.h> //Easyx的图形库头文件
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS //一些老函数报错


//预约者信息
typedef struct {
	char id[20];  			//身份证号
	char name[50];  		//姓名
	char address[100];  	//单位或社区名称
	int okneddle;  			//已经注射过的针数
	int reservationNumber;  //预约成功号
	int date1;             //预约成功的天数 
}Person;

//注射点每天的预约信息
typedef struct Node {
	Person data;
	struct Node* next;
}Node;

//单个注射点信息
struct VaccinationPoint1 {
	int totalVaccines;  		//当日总疫苗数
	int reservedCount;  	    //已预约人数
	int maxReservationNumber;   //最大预约号
	Node* reservations;  	    //预约信息链表头指针
};

//单个注射点信息
typedef struct {
	int index;  						//注射点序号
	char name[50];  					//注射点名称
	struct VaccinationPoint1 date[10]; 	//日期
	Node* reservations;  	    		//预约信息链表头指针
}VaccinationPoint;

//全局变量
VaccinationPoint vaccinationPoints[101];  //存储注射点信息的数组
int vaccinationPointCount = 0;  			 //注射点数量


//函数声明
void saveDataToFile();
void loadDataFromFile();


//图形化函数
void menu1();
void AddMenu();
void FindWeekMenu();
void FindDayMenu();
void menu2();
void BookingMenu();
void FindBookingMenu();
void CancelMenu();
void FindSecondDoseCountMenu();
void FindAbsenteesMenu();
void FindCancelAbsenteesRecordsMenu();


//定义按钮的位置坐标
//主界面
int x1 = 560; int y1 = 210;
int x2 = 560; int y2 = 360;
int x3 = 560; int y3 = 510;

//管理界面
int x11 = 590; int y11 = 210;
int x12 = 590; int y12 = 360;
int x13 = 590; int y13 = 510;
int x14 = 590; int y14 = 660;
//选做界面
int x15 = 200; int y15 = 210;
int x16 = 200; int y16 = 360;
int x17 = 200; int y17 = 510;


//预约界面
int x21 = 560; int y21 = 210;
int x22 = 560; int y22 = 360;
int x23 = 560; int y23 = 510;
int x24 = 560; int y24 = 660;

//返回主菜单键
int xd = 400; int yd = 640;


//定义按钮的大小数组
int r1[] = { x1 - 180, y1 - 40, x1 + 180, y1 + 40, 50, 50 };
int r2[] = { x2 - 180, y2 - 40, x2 + 180, y2 + 40, 50, 50 };
int r3[] = { x3 - 180, y3 - 40, x3 + 180, y3 + 40, 50, 50 };

int r11[] = { x11 - 180, y11 - 40, x11 + 180, y11 + 40, 50, 50 };
int r12[] = { x12 - 180, y12 - 40, x12 + 180, y12 + 40, 50, 50 };
int r13[] = { x13 - 180, y13 - 40, x13 + 180, y13 + 40, 50, 50 };
int r14[] = { x14 - 180, y14 - 40, x14 + 180, y14 + 40, 50, 50 };

int r21[] = { x21 - 180, y21 - 40, x21 + 180, y21 + 40, 50, 50 };
int r22[] = { x22 - 180, y22 - 40, x22 + 180, y22 + 40, 50, 50 };
int r23[] = { x23 - 180, y23 - 40, x23 + 180, y23 + 40, 50, 50 };
int r24[] = { x24 - 180, y24 - 40, x24 + 180, y24 + 40, 50, 50 };


int r15[] = { x15 - 180, y15 - 40, x15 + 180, y15 + 40, 50, 50 };
int r16[] = { x16 - 180, y16 - 40, x16 + 180, y16 + 40, 50, 50 };
int r17[] = { x17 - 180, y17 - 40, x17 + 180, y17 + 40, 50, 50 };

int rd[] = { xd - 140,yd - 40,xd + 140,yd + 40 ,50,50 };


//主界面
void menu()
{

	//鼠标操作1
	ExMessage m1;
	cleardevice();

	//背景图
	IMAGE img;
	loadimage(NULL, _T("imag.jpg"));

	//画圆角矩形，即主界面按钮
	roundrect(r1[0], r1[1], r1[2], r1[3], 50, 50);
	roundrect(r2[0], r2[1], r2[2], r2[3], 50, 50);
	roundrect(r3[0], r3[1], r3[2], r3[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//主界面标题位置

	//主界面选项位置
	RECT R1 = { r1[0], r1[1], r1[2], r1[3] };//圆角矩形指针R1，方便后面在里面写字，不用计算字的位置
	RECT R2 = { r2[0], r2[1], r2[2], r2[3] };
	RECT R3 = { r3[0], r3[1], r3[2], r3[3] };

	//设置标题
	LOGFONT f;                          //字体样式指针
	gettextstyle(&f);					//获取字体样式
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
	f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
	settextstyle(&f);                   // 设置字体样式
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(WHITE);
	drawtext(_T("欢迎使用疫苗预约管理!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

	//设置选项
	settextstyle(38, 0, _T("楷体"));
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(WHITE);
	drawtext(_T("管理注射点(管理员)"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("我要预约"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("退出系统"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	//进入主界面选项操作界面
	while (1)
	{
		m1 = getmessage();//获取鼠标操作
		//当左键按下“管理注射点(管理员)”时进行的操作
		//进入“管理注射点(管理员)”的界面
		if (m1.x > r1[0] && m1.x < r1[2] && m1.y>r1[1] && m1.y < r1[3]) {
			setlinecolor(RED);
			roundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				char s[10];
				InputBox(s, 10, "请输入管理员密码：", NULL, NULL, 0, 0, false);
				if (strcmp(s, "123456") == 0) {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "请按确定键进入管理界面", "登录成功", MB_OK);
					menu1();
				}
				else {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "密码有误，请重新输入", "登录失败", MB_OK);
				}

			}
		}
		//进入“预约界面”
		else if (m1.x >= r2[0] && m1.x <= r2[2] && m1.y >= r2[1] && m1.y <= r2[3]) {
			setlinecolor(RED);
			roundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				menu2();
			}
		}
		//返回主菜单
		else if (m1.x >= r3[0] && m1.x <= r3[2] && m1.y >= r3[1] && m1.y <= r3[3]) {
			setlinecolor(RED);
			roundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]);
			if (m1.message == WM_LBUTTONDOWN) {
				saveDataToFile();//存档
				closegraph();//退出
				exit(0);
			}
		}
		else {
			setlinecolor(WHITE);
			roundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]);
			roundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
			roundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]);
		}
	}

}

//管理界面
void menu1()
{
	//鼠标操作2
	ExMessage m2;
	cleardevice();

	//背景图
	IMAGE img;
	loadimage(NULL, _T("imag.jpg"));

	//画圆角矩形，即主界面按钮
	roundrect(r11[0], r11[1], r11[2], r11[3], 50, 50);
	roundrect(r12[0], r12[1], r12[2], r12[3], 50, 50);
	roundrect(r13[0], r13[1], r13[2], r13[3], 50, 50);
	roundrect(r14[0], r14[1], r14[2], r14[3], 50, 50);

	//选做操作
	roundrect(r15[0], r15[1], r15[2], r15[3], 50, 50);
	roundrect(r16[0], r16[1], r16[2], r16[3], 50, 50);
	roundrect(r17[0], r17[1], r17[2], r17[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//管理界面标题位置
	//主界面选项位置
	RECT R11 = { r11[0], r11[1], r11[2], r11[3] };//圆角矩形指针R11，方便后面在里面写字，不用计算字的位置
	RECT R12 = { r12[0], r12[1], r12[2], r12[3] };
	RECT R13 = { r13[0], r13[1], r13[2], r13[3] };
	RECT R14 = { r14[0], r14[1], r14[2], r14[3] };

	RECT R15 = { r15[0], r15[1], r15[2], r15[3] };
	RECT R16 = { r16[0], r16[1], r16[2], r16[3] };
	RECT R17 = { r17[0], r17[1], r17[2], r17[3] };

	//设置标题
	LOGFONT f;                          //字体样式指针
	gettextstyle(&f);					//获取字体样式
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
	f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
	settextstyle(&f);                   // 设置字体样式
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(WHITE);
	drawtext(_T("管理注射点(管理员)"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

	//设置选项
	settextstyle(36, 0, _T("楷体"));
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(WHITE);
	drawtext(_T("新增注射点"), &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("查询一周疫苗剩余数量"), &R12, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("查询一天疫苗剩余数量"), &R13, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("返回主菜单"), &R14, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//选做操作
	drawtext(_T("查询本周打第二针的人"), &R15, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("爽约记录"), &R16, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("查询取消或爽约记录"), &R17, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//进入管理界面选项操作界面
	while (1)
	{
		m2 = getmessage();//获取鼠标操作
		//当左键按下“管理注射点(管理员)”时进行的操作
		//新增注射点
		if (m2.x > r11[0] && m2.x < r11[2] && m2.y>r11[1] && m2.y < r11[3]) {
			setlinecolor(GREEN);
			roundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				AddMenu();
			}
		}
		//查询一周疫苗剩余数量
		else if (m2.x >= r12[0] && m2.x <= r12[2] && m2.y >= r12[1] && m2.y <= r12[3]) {
			setlinecolor(GREEN);
			roundrect(r12[0], r12[1], r12[2], r12[3], r12[4], r12[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				FindWeekMenu();
			}
		}
		//查询一天疫苗剩余数量
		else if (m2.x >= r13[0] && m2.x <= r13[2] && m2.y >= r13[1] && m2.y <= r13[3]) {
			setlinecolor(GREEN);
			roundrect(r13[0], r13[1], r13[2], r13[3], r13[4], r13[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindDayMenu();
			}
		}
		//返回主菜单
		else if (m2.x >= r14[0] && m2.x <= r14[2] && m2.y >= r14[1] && m2.y <= r14[3]) {
			setlinecolor(GREEN);
			roundrect(r14[0], r14[1], r14[2], r14[3], r14[4], r14[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				menu();
			}
		}
		//查询本周打第二针的人
		else if (m2.x >= r15[0] && m2.x <= r15[2] && m2.y >= r15[1] && m2.y <= r15[3]) {
			setlinecolor(GREEN);
			roundrect(r15[0], r15[1], r15[2], r15[3], r15[4], r15[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindSecondDoseCountMenu();
			}
		}
		//爽约记录
		else if (m2.x >= r16[0] && m2.x <= r16[2] && m2.y >= r16[1] && m2.y <= r16[3]) {
			setlinecolor(GREEN);
			roundrect(r16[0], r16[1], r16[2], r16[3], r16[4], r16[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindAbsenteesMenu();
			}
		}
		//查询取消或爽约记录
		else if (m2.x >= r17[0] && m2.x <= r17[2] && m2.y >= r17[1] && m2.y <= r17[3]) {
			setlinecolor(GREEN);
			roundrect(r17[0], r17[1], r17[2], r17[3], r17[4], r17[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindCancelAbsenteesRecordsMenu();
			}
		}
		else {
			setlinecolor(WHITE);
			roundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]);
			roundrect(r12[0], r12[1], r12[2], r12[3], r12[4], r12[5]);
			roundrect(r13[0], r13[1], r13[2], r13[3], r13[4], r13[5]);
			roundrect(r14[0], r14[1], r14[2], r14[3], r14[4], r14[5]);
			roundrect(r15[0], r15[1], r15[2], r15[3], r15[4], r15[5]);
			roundrect(r16[0], r16[1], r16[2], r16[3], r16[4], r16[5]);
			roundrect(r17[0], r17[1], r17[2], r17[3], r17[4], r17[5]);
		}
	}
}


//新增注射点界面
void AddMenu()
{
	// 定义字符串缓冲区，并接收用户输入
	char s[10];
	InputBox(s, 10, "请输入注射点数量：", NULL, NULL, 0, 0, false);
	// 将用户输入转换为数字
	vaccinationPointCount = atoi(s);

	//初始化注射点序号 
	int i, j, total;
	for (i = 1; i <= vaccinationPointCount; i++) {
		vaccinationPoints[i].index = i;
	}
	//循环输入注射点信息
	for (i = 1; i <= vaccinationPointCount; i++) {
		InputBox(vaccinationPoints[i].name, 50, "请输入注射点的名称：", NULL, NULL, 0, 0, false);
		for (j = 1; j <= 7; j++) {
			// 定义字符串缓冲区，并接收用户输入
			char s1[50];
			InputBox(s1, 50, "请按一周七天的顺序输入该注射点一周每天的疫苗量：", NULL, NULL, 0, 0, false);
			// 将用户输入转换为数字
			total = atoi(s1);
			//将数据存入结构体中
			vaccinationPoints[i].date[j].totalVaccines = total;
			vaccinationPoints[i].date[j].reservedCount = 0;
			vaccinationPoints[i].date[j].maxReservationNumber = 0;
			vaccinationPoints[i].date[j].reservations = NULL;
		}
	}
	HWND hwndInput1 = GetHWnd();
	int isok = MessageBox(hwndInput1, "新增注射点成功", "提示", MB_OK);
}

//查找某注射点某天剩余疫苗界面
void FindWeekMenu()
{
	int pointIndex, date;
	int i, sy = 0;
	int flag = 0;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "请输入要查询的注射点序号：", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		InputBox(s, 101, "请输入要查询的日期：", NULL, NULL, 0, 0, false);
		date = atoi(s);
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				flag = 1;
				sy = vaccinationPoints[i].date[date].totalVaccines - vaccinationPoints[i].date[date].reservedCount;
				break;
			}
		}
		if (flag == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "查无此注射点", "查询失败", MB_OK);
		}
		else {
			char sy1[101];
			_itoa_s(sy, sy1, 10);
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "请点击确定查看", "查询成功", MB_OK);
			int isok1 = MessageBox(hwndInput1, sy1, "当天该注射点剩余数量", MB_OK);
		}
	}
}

//查找一天剩余疫苗界面
void FindDayMenu()
{
	int date;
	int i, j, sy;
	int p, flag;
	VaccinationPoint temp;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "请输入要查询的日期：", NULL, NULL, 0, 0, false);
		date = atoi(s);
		//按剩余疫苗数量从高到低排序
		for (p = vaccinationPointCount; p >= 1; p--) {
			flag = 0;
			for (i = 1; i <= p; i++) {
				if (vaccinationPoints[i].date[date].totalVaccines - vaccinationPoints[i].date[date].reservedCount < vaccinationPoints[i + 1].date[date].totalVaccines - vaccinationPoints[i + 1].date[date].reservedCount) {
					temp = vaccinationPoints[i];
					vaccinationPoints[i] = vaccinationPoints[i + 1];
					vaccinationPoints[i + 1] = temp;
					flag = 1;
				}
			}
			if (flag == 0) {
				break;
			}
		}
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "请点击确定查看", "查询成功", MB_OK);

		ExMessage m3;
		cleardevice();

		//背景图
		IMAGE img;
		loadimage(NULL, _T("imag.jpg"));

		//画出返回主菜单的圆角矩形
		roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

		RECT r = { 0, 0, 799, 140 };					//查询某天疫苗剩余数量界面“标题”位置
		RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//圆角矩形指针Rrd，方便后面在里面写字，不用计算字的位置

		//设置标题
		LOGFONT f;                          //字体样式指针
		gettextstyle(&f);					//获取字体样式
		f.lfHeight = 50;
		_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
		f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
		settextstyle(&f);                   // 设置字体样式
		setbkmode(TRANSPARENT);             //字体背景透明
		settextcolor(WHITE);
		drawtext(_T("查询该天所有注射点的剩余疫苗数量"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

		//返回主菜单选项
		settextstyle(38, 0, _T("楷体"));
		setbkmode(TRANSPARENT);             //字体背景透明
		settextcolor(WHITE);
		drawtext(_T("返回上一级"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域Rrd内输入文字，水平居中，垂直居中，单行显示

		//设置显示的界面文字
		settextstyle(32, 0, _T("楷体"));
		setbkmode(TRANSPARENT);             //字体背景透明
		settextcolor(WHITE);

		outtextxy(50, 150, "注射点序号");
		outtextxy(260, 150, "注射点名称");
		outtextxy(470, 150, "该天剩余疫苗数量");

		//设置显示的注射点
		settextstyle(32, 0, _T("黑体"));
		setbkmode(TRANSPARENT);             //字体背景透明
		settextcolor(RED);

		sy = vaccinationPoints[1].date[date].totalVaccines - vaccinationPoints[1].date[date].reservedCount;
		char sy0[101], index0[101];
		_itoa_s(sy, sy0, 10);
		_itoa_s(vaccinationPoints[1].index, index0, 10);
		outtextxy(50 + 70, 60 + 150, index0);
		outtextxy(260 + 10, 60 + 150, vaccinationPoints[1].name);
		outtextxy(470 + 110, 60 + 150, sy0);

		for (i = 2; i <= vaccinationPointCount; i++) {
			sy = vaccinationPoints[i].date[date].totalVaccines - vaccinationPoints[i].date[date].reservedCount;
			char sy1[101], index1[101];
			_itoa_s(sy, sy1, 10);
			_itoa_s(vaccinationPoints[i].index, index1, 10);
			outtextxy(50 + 70, 210 + (i - 1) * 60, index1);
			outtextxy(260 + 10, 210 + (i - 1) * 60, vaccinationPoints[i].name);
			outtextxy(470 + 110, 210 + (i - 1) * 60, sy1);
		}

		//进入显示剩余疫苗操作界面
		while (1) {
			m3 = getmessage();
			if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
				setlinecolor(GREEN);
				roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
				if (m3.message == WM_LBUTTONDOWN) {
					menu1();//返回管理界面(上一级)
				}
			}
			else {
				setlinecolor(WHITE);
				roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
			}
		}
	}
}

//预约界面
void menu2()
{
	//鼠标操作2
	ExMessage m2;
	cleardevice();

	//背景图
	IMAGE img;
	loadimage(NULL, _T("imag1.jpg"));

	//画圆角矩形，即主界面按钮
	roundrect(r21[0], r21[1], r21[2], r21[3], 50, 50);
	roundrect(r22[0], r22[1], r22[2], r22[3], 50, 50);
	roundrect(r23[0], r23[1], r23[2], r23[3], 50, 50);
	roundrect(r24[0], r24[1], r24[2], r24[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//管理界面标题位置
	//主界面选项位置
	RECT R21 = { r21[0], r21[1], r21[2], r21[3] };//圆角矩形指针R11，方便后面在里面写字，不用计算字的位置
	RECT R22 = { r22[0], r22[1], r22[2], r22[3] };
	RECT R23 = { r23[0], r23[1], r23[2], r23[3] };
	RECT R24 = { r24[0], r24[1], r24[2], r24[3] };

	//设置标题
	LOGFONT f;                          //字体样式指针
	gettextstyle(&f);					//获取字体样式
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
	f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
	settextstyle(&f);                   // 设置字体样式
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(BLACK);
	drawtext(_T("我要预约"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

	//设置选项
	settextstyle(36, 0, _T("楷体"));
	setbkmode(TRANSPARENT);             //字体背景透明
	settextcolor(BLACK);
	drawtext(_T("个人预约"), &R21, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域R21内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("查询个人预约信息"), &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("取消个人预约"), &R23, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("返回主菜单"), &R24, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//进入预约界面选项操作界面
	while (1)
	{
		m2 = getmessage();//获取鼠标操作
		//当左键按下“个人预约”时进行的操作
		//个人预约界面
		if (m2.x > r21[0] && m2.x < r21[2] && m2.y>r21[1] && m2.y < r21[3]) {
			setlinecolor(GREEN);
			roundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
			if (m2.message == WM_LBUTTONDOWN)    //进入“管理注射点(管理员)”的界面
			{
				BookingMenu();
			}
		}
		//查询个人预约信息
		else if (m2.x >= r22[0] && m2.x <= r22[2] && m2.y >= r22[1] && m2.y <= r22[3]) {
			setlinecolor(GREEN);
			roundrect(r22[0], r22[1], r22[2], r22[3], r22[4], r22[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				FindBookingMenu();
			}
		}
		//取消个人预约信息
		else if (m2.x >= r23[0] && m2.x <= r23[2] && m2.y >= r23[1] && m2.y <= r23[3]) {
			setlinecolor(GREEN);
			roundrect(r23[0], r23[1], r23[2], r23[3], r23[4], r23[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				CancelMenu();
			}
		}
		//返回主菜单
		else if (m2.x >= r24[0] && m2.x <= r24[2] && m2.y >= r24[1] && m2.y <= r24[3]) {
			setlinecolor(GREEN);
			roundrect(r24[0], r24[1], r24[2], r24[3], r24[4], r24[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				menu();
			}
		}
		else {
			setlinecolor(BLACK);
			roundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
			roundrect(r22[0], r22[1], r22[2], r22[3], r22[4], r22[5]);
			roundrect(r23[0], r23[1], r23[2], r23[3], r23[4], r23[5]);
			roundrect(r24[0], r24[1], r24[2], r24[3], r24[4], r24[5]);
		}
	}
}

//个人预约界面
void BookingMenu()
{
	int found = 0;
	int pointIndex, date;
	int i, j, reserved = 0;
	char id[20]; char name[50]; char address[100];//单位或社区名称
	int okneddle;//已经注射过的针数
	Node* newNode;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "预约失败", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "请输入要预约的注射点序号：", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				found = 1;
				char s1[101];
				InputBox(s1, 101, "请输入你要预约的日期：", NULL, NULL, 0, 0, false);
				date = atoi(s1);
				InputBox(id, 101, "请输入您的身份证号：", NULL, NULL, 0, 0, false);
				InputBox(name, 101, "请输入你的姓名：", NULL, NULL, 0, 0, false);

				Node* TMP = vaccinationPoints[i].reservations;
				while (TMP != NULL) {
					if (strcmp(TMP->data.id, id) == 0) {
						HWND hwndInput1 = GetHWnd();
						int isok = MessageBox(hwndInput1, "你已经预约过了，请勿重复预约！", "预约失败", MB_OK);
						return;
					}
					TMP = TMP->next;
				}
				InputBox(address, 101, "请输入你的单位或社区名称：", NULL, NULL, 0, 0, false);
				char s2[101];
				InputBox(s2, 101, "请输入你已经注射过的针数：", NULL, NULL, 0, 0, false);
				okneddle = atoi(s2);
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "您输入的注射点不存在！", "预约失败", MB_OK);
		}
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				//将数据传入结构体中
				if (vaccinationPoints[i].date[date].reservedCount < vaccinationPoints[i].date[date].totalVaccines) {
					//预约号为当前最大预约号+1
					reserved = vaccinationPoints[i].date[date].maxReservationNumber + 1;
					vaccinationPoints[i].date[date].maxReservationNumber = reserved;
					vaccinationPoints[i].date[date].reservedCount++;
					//创建新的预约节点
					newNode = (Node*)malloc(sizeof(Node));
					strcpy_s(newNode->data.id, id);
					strcpy_s(newNode->data.name, name);
					strcpy_s(newNode->data.address, address);
					newNode->data.okneddle = okneddle;
					newNode->data.date1 = date;
					newNode->data.reservationNumber = reserved;
					newNode->next = NULL;
					//将预约节点插入链表尾部
					if (vaccinationPoints[i].reservations == NULL) {
						vaccinationPoints[i].reservations = newNode;
					}
					else {
						temp = vaccinationPoints[i].reservations;
						while (temp->next != NULL) {
							temp = temp->next;
						}
						temp->next = newNode;
					}
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "请点击确认查看您的预约号", "预约成功", MB_OK);
					//将整型转换为字符串
					char reserved1[101];
					_itoa_s(reserved, reserved1, 10);
					int isok2 = MessageBox(hwndInput1, reserved1, "您的预约号是", MB_OK);
				}
				else {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "该注射点当日疫苗已约满！", "预约失败", MB_OK);
				}
				break;
			}
		}
	}
}

//查询个人预约信息界面
void FindBookingMenu()
{
	char id[20];
	int i, j, found = 0;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		InputBox(id, 101, "请输入您的身份证号：", NULL, NULL, 0, 0, false);
		for (i = 1; i <= vaccinationPointCount; i++) {
			temp = vaccinationPoints[i].reservations;
			while (temp != NULL) {
				if (strcmp(temp->data.id, id) == 0) {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "请点击确定查看", "查询成功", MB_OK);
					ExMessage m3;
					cleardevice();


					//背景图
					IMAGE img;
					loadimage(NULL, _T("imag1.jpg"));

					//画出返回主菜单的圆角矩形
					roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

					RECT r = { 0, 0, 799, 140 };					//查询某天疫苗剩余数量界面“标题”位置
					RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//圆角矩形指针Rrd，方便后面在里面写字，不用计算字的位置

					//设置标题
					LOGFONT f;                          //字体样式指针
					gettextstyle(&f);					//获取字体样式
					f.lfHeight = 50;
					_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
					f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
					settextstyle(&f);                   // 设置字体样式
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(BLACK);
					drawtext(_T("查询个人预约信息"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

					//返回主菜单选项
					settextstyle(38, 0, _T("楷体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(BLACK);
					drawtext(_T("返回上一级"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域Rrd内输入文字，水平居中，垂直居中，单行显示

					//设置显示的界面文字
					settextstyle(24, 0, _T("楷体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(BLACK);

					outtextxy(10, 150, "注射点");
					outtextxy(100, 150, "日期");
					outtextxy(180, 150, "身份证号");
					outtextxy(310, 150, "姓名");
					outtextxy(400, 150, "单位或社区");
					outtextxy(540, 150, "已注射针数");
					outtextxy(670, 150, "预约成功号");

					//设置显示的预约人
					settextstyle(24, 0, _T("黑体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(RED);

					//整型转为字符串
					char date1[10], okneddle1[10], reservationNumber1[101];
					_itoa_s(temp->data.date1, date1, 10);
					_itoa_s(temp->data.okneddle, okneddle1, 10);
					_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

					outtextxy(10, 60 + 150, vaccinationPoints[i].name);     //注射点
					outtextxy(100 + 18, 60 + 150, date1);					//日期
					outtextxy(180, 60 + 150, temp->data.id);				//身份证号
					outtextxy(310, 60 + 150, temp->data.name);				//名字
					outtextxy(400, 60 + 150, temp->data.address);			//单位或社区名称
					outtextxy(540 + 50, 60 + 150, okneddle1);				//已经注射的针数
					outtextxy(670 + 50, 60 + 150, reservationNumber1);		//预约成功号
					found = 1;

					//进入显示预约查询操作界面
					while (1) {
						m3 = getmessage();
						if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
							setlinecolor(GREEN);
							roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
							if (m3.message == WM_LBUTTONDOWN) {
								menu2();//返回预约界面(上一级)
							}
						}
						else {
							setlinecolor(BLACK);
							roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
						}
					}
				}
				temp = temp->next;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "未找到该身份证号的预约信息!", "查询失败", MB_OK);
		}
		return;
	}
}

//取消个人预约
void CancelMenu()
{
	char id[20];
	int i, j, found = 0;
	Node* temp;
	Node* prev;

	InputBox(id, 101, "请输入您要取消的身份证号：", NULL, NULL, 0, 0, false);

	for (i = 1; i <= vaccinationPointCount; i++) {
		temp = vaccinationPoints[i].reservations;
		prev = NULL;
		while (temp != NULL) {
			if (strcmp(temp->data.id, id) == 0) {
				if (prev == NULL) {
					vaccinationPoints[i].reservations = temp->next;
				}
				else {
					prev->next = temp->next;
				}
				free(temp);
				found = 1;
				HWND hwndInput1 = GetHWnd();
				int isok = MessageBox(hwndInput1, "预约已成功取消!", "取消成功", MB_OK);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	if (found == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "未找到该身份证号的预约信息!", "取消失败", MB_OK);
	}
	return;
}

//查询某注射点本周内打第二针的人数
void FindSecondDoseCountMenu()
{
	int pointIndex;
	int i, count = 0;
	Node* temp;
	int found = 0;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "请输入要查询的注射点序号：", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				found = 1;
				temp = vaccinationPoints[i].reservations;
				while (temp != NULL) {
					if (temp->data.okneddle == 1) {
						count++;
					}
					temp = temp->next;
				}
				break;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "未找到该注射点信息!", "查询失败", MB_OK);
		}
		else
		{
			//将整型转换为字符串
			char count1[101];
			_itoa_s(count, count1, 10);
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "请点击确认查看本周内在该注射点要打第二针的人数", "查询成功", MB_OK);
			int isok1 = MessageBox(hwndInput1, count1, "本周内在该注射点要打第二针的人数", MB_OK);
		}
		return;
	}
}

//爽约记录
void FindAbsenteesMenu()
{
	int pointIndex, date;
	int i, found = 0;
	int j = 0;
	Node* temp;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		//鼠标事件m3
		ExMessage m3;

		char s[101], s1[101];
		InputBox(s, 101, "请输入要查询的注射点序号：", NULL, NULL, 0, 0, false);
		InputBox(s1, 101, "请输入要查询的日期：", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		date = atoi(s1);

		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				temp = vaccinationPoints[i].reservations;
				while (temp != NULL) {
					if (temp->data.okneddle == 0 && temp->data.date1 == date) {
						//如果有多个爽约人信息，只显示一次查询成功提醒，以及在第一次将背景布置好，避免后面重新布置背景将信息覆盖
						if (j == 0) {
							HWND hwndInput1 = GetHWnd();
							int isok = MessageBox(hwndInput1, "请点击确定查看", "查询成功", MB_OK);
							cleardevice();
							//背景图
							IMAGE img;
							loadimage(NULL, _T("imag.jpg"));
						}
						//画出返回主菜单的圆角矩形
						roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

						RECT r = { 0, 0, 799, 140 };					//查询某天疫苗剩余数量界面“标题”位置
						RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//圆角矩形指针Rrd，方便后面在里面写字，不用计算字的位置

						//设置标题
						LOGFONT f;                          //字体样式指针
						gettextstyle(&f);					//获取字体样式
						f.lfHeight = 50;
						_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
						f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
						settextstyle(&f);                   // 设置字体样式
						setbkmode(TRANSPARENT);             //字体背景透明
						settextcolor(WHITE);
						drawtext(_T("查询个人预约信息"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

						//返回上一级选项
						settextstyle(38, 0, _T("楷体"));
						setbkmode(TRANSPARENT);             //字体背景透明
						settextcolor(WHITE);
						drawtext(_T("返回上一级"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域Rrd内输入文字，水平居中，垂直居中，单行显示

						//设置显示的界面文字
						settextstyle(24, 0, _T("楷体"));
						setbkmode(TRANSPARENT);             //字体背景透明
						settextcolor(WHITE);

						outtextxy(10, 150, "注射点");
						outtextxy(100, 150, "日期");
						outtextxy(180, 150, "身份证号");
						outtextxy(310, 150, "姓名");
						outtextxy(400, 150, "单位或社区");
						outtextxy(540, 150, "已注射针数");
						outtextxy(670, 150, "预约成功号");

						//设置显示的爽约人
						settextstyle(24, 0, _T("黑体"));
						setbkmode(TRANSPARENT);             //字体背景透明
						settextcolor(RED);

						//整型转为字符串
						char date1[10], okneddle1[10], reservationNumber1[101];
						_itoa_s(temp->data.date1, date1, 10);
						_itoa_s(temp->data.okneddle, okneddle1, 10);
						_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

						//显示爽约的人的信息
						outtextxy(10, 60 + 150 + (j * 60), vaccinationPoints[i].name);     //注射点
						outtextxy(100 + 18, 60 + 150 + (j * 60), date1);					//日期
						outtextxy(180, 60 + 150 + (j * 60), temp->data.id);				//身份证号
						outtextxy(310, 60 + 150 + (j * 60), temp->data.name);				//名字
						outtextxy(400, 60 + 150 + (j * 60), temp->data.address);			//单位或社区名称
						outtextxy(540 + 50, 60 + 150 + (j * 60), okneddle1);				//已经注射的针数
						outtextxy(670 + 50, 60 + 150 + (j * 60), reservationNumber1);		//预约成功号

						j++;//链表长度，根据这个长度给选择合适的显示位置

						found = 1;
					}
					temp = temp->next;
				}
				break;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "未找到符合条件的爽约记录!", "查询完毕", MB_OK);
		}
		else
		{
			//进入显示爽约操作界面
			while (1) {
				m3 = getmessage();
				if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
					setlinecolor(GREEN);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
					if (m3.message == WM_LBUTTONDOWN) {
						menu1();//返回预约界面(上一级)
					}
				}
				else {
					setlinecolor(BLACK);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
				}
			}
		}
		return;
	}

}

//查询取消或爽约记录
void FindCancelAbsenteesRecordsMenu()
{
	int i, j = 0;
	int found = 0;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "系统里暂无数据！请先录入数据", "查询失败", MB_OK);
	}
	else {
		//鼠标事件m3
		ExMessage m3;

		for (i = 1; i <= vaccinationPointCount; i++) {
			temp = vaccinationPoints[i].reservations;
			while (temp != NULL) {
				//简单操作
				if (temp->data.okneddle == -1) {
					//如果有多个爽约人信息，只显示一次查询成功提醒，以及在第一次将背景布置好，避免后面重新布置背景将信息覆盖
					if (j == 0) {
						HWND hwndInput1 = GetHWnd();
						int isok = MessageBox(hwndInput1, "请点击确定查看", "查询成功", MB_OK);
						cleardevice();
						//背景图
						IMAGE img;
						loadimage(NULL, _T("imag.jpg"));
					}

					//画出返回主菜单的圆角矩形
					roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

					RECT r = { 0, 0, 799, 140 };					//查询某天疫苗剩余数量界面“标题”位置
					RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//圆角矩形指针Rrd，方便后面在里面写字，不用计算字的位置

					//设置标题
					LOGFONT f;                          //字体样式指针
					gettextstyle(&f);					//获取字体样式
					f.lfHeight = 50;
					_tcscpy_s(f.lfFaceName, _T("楷体"));	//楷体
					f.lfQuality = ANTIALIASED_QUALITY;  // 抗锯齿 
					settextstyle(&f);                   // 设置字体样式
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(WHITE);
					drawtext(_T("查询个人预约信息"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //输出标题

					//返回上一级选项
					settextstyle(38, 0, _T("楷体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(WHITE);
					drawtext(_T("返回上一级"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在圆角矩形区域Rrd内输入文字，水平居中，垂直居中，单行显示

					//设置显示的界面文字
					settextstyle(24, 0, _T("楷体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(WHITE);

					outtextxy(10, 150, "注射点");
					outtextxy(100, 150, "日期");
					outtextxy(180, 150, "身份证号");
					outtextxy(310, 150, "姓名");
					outtextxy(400, 150, "单位或社区");
					outtextxy(540, 150, "已注射针数");
					outtextxy(670, 150, "预约成功号");

					//设置显示的爽约或取消的人
					settextstyle(24, 0, _T("黑体"));
					setbkmode(TRANSPARENT);             //字体背景透明
					settextcolor(RED);

					//整型转为字符串
					char date1[10], okneddle1[10], reservationNumber1[101];
					_itoa_s(temp->data.date1, date1, 10);
					_itoa_s(temp->data.okneddle, okneddle1, 10);
					_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

					//显示爽约的人的信息
					outtextxy(10, 60 + 150 + (j * 60), vaccinationPoints[i].name);     //注射点
					outtextxy(100 + 18, 60 + 150 + (j * 60), date1);					//日期
					outtextxy(180, 60 + 150 + (j * 60), temp->data.id);				//身份证号
					outtextxy(310, 60 + 150 + (j * 60), temp->data.name);				//名字
					outtextxy(400, 60 + 150 + (j * 60), temp->data.address);			//单位或社区名称
					outtextxy(540 + 50, 60 + 150 + (j * 60), okneddle1);				//已经注射的针数
					outtextxy(670 + 50, 60 + 150 + (j * 60), reservationNumber1);		//预约成功号

					j++;//链表长度，根据这个长度给选择合适的显示位置

					found = 1;
				}
				temp = temp->next;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "未找到符合条件的取消或爽约记录!", "查询完毕", MB_OK);
		}
		else {
			//进入显示预约查询操作界面
			while (1) {
				m3 = getmessage();
				if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
					setlinecolor(GREEN);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
					if (m3.message == WM_LBUTTONDOWN) {
						menu1();//返回预约界面(上一级)
					}
				}
				else {
					setlinecolor(BLACK);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
				}
			}
		}
		return;
	}
}


//存档
void saveDataToFile()
{
	int i;
	FILE* fp;
	fopen_s(&fp, "data.txt", "wb");
	if (fp == NULL) {
		return;
	}
	fwrite(&vaccinationPointCount, sizeof(int), 1, fp); //写入注射点数量
	fwrite(vaccinationPoints, sizeof(VaccinationPoint), vaccinationPointCount + 1, fp); //写入注射点信息数组
	//写入预约者信息
	for (i = 1; i <= vaccinationPointCount; i++) {
		struct Node* current = vaccinationPoints[i].reservations;
		while (current != NULL) {
			fwrite(&current->data, sizeof(Person), 1, fp); // 写入预约者信息
			current = current->next;
		}
	}
	fclose(fp);
}

//读档
void loadDataFromFile()
{
	int i, j;
	FILE* fp;
	fopen_s(&fp, "data.txt", "rb");
	if (fp == NULL) {
		return;
	}
	fread(&vaccinationPointCount, sizeof(int), 1, fp); //读取注射点数量
	fread(vaccinationPoints, sizeof(VaccinationPoint), vaccinationPointCount + 1, fp); //读取注射点信息数组
	for (i = 1; i <= vaccinationPointCount; i++) {
		vaccinationPoints[i].reservations = NULL; //初始化预约链表头指针
		for (j = 1; j <= 10; j++) {
			struct Node* newNode = NULL;
			// 读取预约者信息
			while (1) {
				struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
				fread(&temp->data, sizeof(Person), 1, fp); //读取预约者信息
				if (feof(fp)) {
					free(temp);
					break;
				}
				temp->next = NULL;
				if (newNode == NULL) {
					newNode = temp;
					vaccinationPoints[i].reservations = newNode;
				}
				else {
					newNode->next = temp;
					newNode = newNode->next;
				}
			}
		}
	}
	fclose(fp);
}


int main()
{
	//读档
	loadDataFromFile();
	//绘图窗口初始化
	initgraph(800, 730, SHOWCONSOLE);
	menu();

	//在命令行控制台按任意键退出
	_getch();
	closegraph();
}
