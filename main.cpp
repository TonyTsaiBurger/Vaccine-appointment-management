#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>//����ַ�
#include<graphics.h> //Easyx��ͼ�ο�ͷ�ļ�
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS //һЩ�Ϻ�������


//ԤԼ����Ϣ
typedef struct {
	char id[20];  			//���֤��
	char name[50];  		//����
	char address[100];  	//��λ����������
	int okneddle;  			//�Ѿ�ע���������
	int reservationNumber;  //ԤԼ�ɹ���
	int date1;             //ԤԼ�ɹ������� 
}Person;

//ע���ÿ���ԤԼ��Ϣ
typedef struct Node {
	Person data;
	struct Node* next;
}Node;

//����ע�����Ϣ
struct VaccinationPoint1 {
	int totalVaccines;  		//������������
	int reservedCount;  	    //��ԤԼ����
	int maxReservationNumber;   //���ԤԼ��
	Node* reservations;  	    //ԤԼ��Ϣ����ͷָ��
};

//����ע�����Ϣ
typedef struct {
	int index;  						//ע������
	char name[50];  					//ע�������
	struct VaccinationPoint1 date[10]; 	//����
	Node* reservations;  	    		//ԤԼ��Ϣ����ͷָ��
}VaccinationPoint;

//ȫ�ֱ���
VaccinationPoint vaccinationPoints[101];  //�洢ע�����Ϣ������
int vaccinationPointCount = 0;  			 //ע�������


//��������
void saveDataToFile();
void loadDataFromFile();


//ͼ�λ�����
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


//���尴ť��λ������
//������
int x1 = 560; int y1 = 210;
int x2 = 560; int y2 = 360;
int x3 = 560; int y3 = 510;

//�������
int x11 = 590; int y11 = 210;
int x12 = 590; int y12 = 360;
int x13 = 590; int y13 = 510;
int x14 = 590; int y14 = 660;
//ѡ������
int x15 = 200; int y15 = 210;
int x16 = 200; int y16 = 360;
int x17 = 200; int y17 = 510;


//ԤԼ����
int x21 = 560; int y21 = 210;
int x22 = 560; int y22 = 360;
int x23 = 560; int y23 = 510;
int x24 = 560; int y24 = 660;

//�������˵���
int xd = 400; int yd = 640;


//���尴ť�Ĵ�С����
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


//������
void menu()
{

	//������1
	ExMessage m1;
	cleardevice();

	//����ͼ
	IMAGE img;
	loadimage(NULL, _T("imag.jpg"));

	//��Բ�Ǿ��Σ��������水ť
	roundrect(r1[0], r1[1], r1[2], r1[3], 50, 50);
	roundrect(r2[0], r2[1], r2[2], r2[3], 50, 50);
	roundrect(r3[0], r3[1], r3[2], r3[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//���������λ��

	//������ѡ��λ��
	RECT R1 = { r1[0], r1[1], r1[2], r1[3] };//Բ�Ǿ���ָ��R1���������������д�֣����ü����ֵ�λ��
	RECT R2 = { r2[0], r2[1], r2[2], r2[3] };
	RECT R3 = { r3[0], r3[1], r3[2], r3[3] };

	//���ñ���
	LOGFONT f;                          //������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("����"));	//����
	f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
	settextstyle(&f);                   // ����������ʽ
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(WHITE);
	drawtext(_T("��ӭʹ������ԤԼ����!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

	//����ѡ��
	settextstyle(38, 0, _T("����"));
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(WHITE);
	drawtext(_T("����ע���(����Ա)"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("��ҪԤԼ"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("�˳�ϵͳ"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	//����������ѡ���������
	while (1)
	{
		m1 = getmessage();//��ȡ������
		//��������¡�����ע���(����Ա)��ʱ���еĲ���
		//���롰����ע���(����Ա)���Ľ���
		if (m1.x > r1[0] && m1.x < r1[2] && m1.y>r1[1] && m1.y < r1[3]) {
			setlinecolor(RED);
			roundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				char s[10];
				InputBox(s, 10, "���������Ա���룺", NULL, NULL, 0, 0, false);
				if (strcmp(s, "123456") == 0) {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "�밴ȷ��������������", "��¼�ɹ�", MB_OK);
					menu1();
				}
				else {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "������������������", "��¼ʧ��", MB_OK);
				}

			}
		}
		//���롰ԤԼ���桱
		else if (m1.x >= r2[0] && m1.x <= r2[2] && m1.y >= r2[1] && m1.y <= r2[3]) {
			setlinecolor(RED);
			roundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				menu2();
			}
		}
		//�������˵�
		else if (m1.x >= r3[0] && m1.x <= r3[2] && m1.y >= r3[1] && m1.y <= r3[3]) {
			setlinecolor(RED);
			roundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]);
			if (m1.message == WM_LBUTTONDOWN) {
				saveDataToFile();//�浵
				closegraph();//�˳�
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

//�������
void menu1()
{
	//������2
	ExMessage m2;
	cleardevice();

	//����ͼ
	IMAGE img;
	loadimage(NULL, _T("imag.jpg"));

	//��Բ�Ǿ��Σ��������水ť
	roundrect(r11[0], r11[1], r11[2], r11[3], 50, 50);
	roundrect(r12[0], r12[1], r12[2], r12[3], 50, 50);
	roundrect(r13[0], r13[1], r13[2], r13[3], 50, 50);
	roundrect(r14[0], r14[1], r14[2], r14[3], 50, 50);

	//ѡ������
	roundrect(r15[0], r15[1], r15[2], r15[3], 50, 50);
	roundrect(r16[0], r16[1], r16[2], r16[3], 50, 50);
	roundrect(r17[0], r17[1], r17[2], r17[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//����������λ��
	//������ѡ��λ��
	RECT R11 = { r11[0], r11[1], r11[2], r11[3] };//Բ�Ǿ���ָ��R11���������������д�֣����ü����ֵ�λ��
	RECT R12 = { r12[0], r12[1], r12[2], r12[3] };
	RECT R13 = { r13[0], r13[1], r13[2], r13[3] };
	RECT R14 = { r14[0], r14[1], r14[2], r14[3] };

	RECT R15 = { r15[0], r15[1], r15[2], r15[3] };
	RECT R16 = { r16[0], r16[1], r16[2], r16[3] };
	RECT R17 = { r17[0], r17[1], r17[2], r17[3] };

	//���ñ���
	LOGFONT f;                          //������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("����"));	//����
	f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
	settextstyle(&f);                   // ����������ʽ
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(WHITE);
	drawtext(_T("����ע���(����Ա)"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

	//����ѡ��
	settextstyle(36, 0, _T("����"));
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(WHITE);
	drawtext(_T("����ע���"), &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("��ѯһ������ʣ������"), &R12, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��ѯһ������ʣ������"), &R13, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("�������˵�"), &R14, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//ѡ������
	drawtext(_T("��ѯ���ܴ�ڶ������"), &R15, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("ˬԼ��¼"), &R16, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��ѯȡ����ˬԼ��¼"), &R17, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//����������ѡ���������
	while (1)
	{
		m2 = getmessage();//��ȡ������
		//��������¡�����ע���(����Ա)��ʱ���еĲ���
		//����ע���
		if (m2.x > r11[0] && m2.x < r11[2] && m2.y>r11[1] && m2.y < r11[3]) {
			setlinecolor(GREEN);
			roundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				AddMenu();
			}
		}
		//��ѯһ������ʣ������
		else if (m2.x >= r12[0] && m2.x <= r12[2] && m2.y >= r12[1] && m2.y <= r12[3]) {
			setlinecolor(GREEN);
			roundrect(r12[0], r12[1], r12[2], r12[3], r12[4], r12[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				FindWeekMenu();
			}
		}
		//��ѯһ������ʣ������
		else if (m2.x >= r13[0] && m2.x <= r13[2] && m2.y >= r13[1] && m2.y <= r13[3]) {
			setlinecolor(GREEN);
			roundrect(r13[0], r13[1], r13[2], r13[3], r13[4], r13[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindDayMenu();
			}
		}
		//�������˵�
		else if (m2.x >= r14[0] && m2.x <= r14[2] && m2.y >= r14[1] && m2.y <= r14[3]) {
			setlinecolor(GREEN);
			roundrect(r14[0], r14[1], r14[2], r14[3], r14[4], r14[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				menu();
			}
		}
		//��ѯ���ܴ�ڶ������
		else if (m2.x >= r15[0] && m2.x <= r15[2] && m2.y >= r15[1] && m2.y <= r15[3]) {
			setlinecolor(GREEN);
			roundrect(r15[0], r15[1], r15[2], r15[3], r15[4], r15[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindSecondDoseCountMenu();
			}
		}
		//ˬԼ��¼
		else if (m2.x >= r16[0] && m2.x <= r16[2] && m2.y >= r16[1] && m2.y <= r16[3]) {
			setlinecolor(GREEN);
			roundrect(r16[0], r16[1], r16[2], r16[3], r16[4], r16[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				FindAbsenteesMenu();
			}
		}
		//��ѯȡ����ˬԼ��¼
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


//����ע������
void AddMenu()
{
	// �����ַ������������������û�����
	char s[10];
	InputBox(s, 10, "������ע���������", NULL, NULL, 0, 0, false);
	// ���û�����ת��Ϊ����
	vaccinationPointCount = atoi(s);

	//��ʼ��ע������ 
	int i, j, total;
	for (i = 1; i <= vaccinationPointCount; i++) {
		vaccinationPoints[i].index = i;
	}
	//ѭ������ע�����Ϣ
	for (i = 1; i <= vaccinationPointCount; i++) {
		InputBox(vaccinationPoints[i].name, 50, "������ע�������ƣ�", NULL, NULL, 0, 0, false);
		for (j = 1; j <= 7; j++) {
			// �����ַ������������������û�����
			char s1[50];
			InputBox(s1, 50, "�밴һ�������˳�������ע���һ��ÿ�����������", NULL, NULL, 0, 0, false);
			// ���û�����ת��Ϊ����
			total = atoi(s1);
			//�����ݴ���ṹ����
			vaccinationPoints[i].date[j].totalVaccines = total;
			vaccinationPoints[i].date[j].reservedCount = 0;
			vaccinationPoints[i].date[j].maxReservationNumber = 0;
			vaccinationPoints[i].date[j].reservations = NULL;
		}
	}
	HWND hwndInput1 = GetHWnd();
	int isok = MessageBox(hwndInput1, "����ע���ɹ�", "��ʾ", MB_OK);
}

//����ĳע���ĳ��ʣ���������
void FindWeekMenu()
{
	int pointIndex, date;
	int i, sy = 0;
	int flag = 0;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "������Ҫ��ѯ��ע�����ţ�", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		InputBox(s, 101, "������Ҫ��ѯ�����ڣ�", NULL, NULL, 0, 0, false);
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
			int isok = MessageBox(hwndInput1, "���޴�ע���", "��ѯʧ��", MB_OK);
		}
		else {
			char sy1[101];
			_itoa_s(sy, sy1, 10);
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "����ȷ���鿴", "��ѯ�ɹ�", MB_OK);
			int isok1 = MessageBox(hwndInput1, sy1, "�����ע���ʣ������", MB_OK);
		}
	}
}

//����һ��ʣ���������
void FindDayMenu()
{
	int date;
	int i, j, sy;
	int p, flag;
	VaccinationPoint temp;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "������Ҫ��ѯ�����ڣ�", NULL, NULL, 0, 0, false);
		date = atoi(s);
		//��ʣ�����������Ӹߵ�������
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
		int isok = MessageBox(hwndInput1, "����ȷ���鿴", "��ѯ�ɹ�", MB_OK);

		ExMessage m3;
		cleardevice();

		//����ͼ
		IMAGE img;
		loadimage(NULL, _T("imag.jpg"));

		//�����������˵���Բ�Ǿ���
		roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

		RECT r = { 0, 0, 799, 140 };					//��ѯĳ������ʣ���������桰���⡱λ��
		RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//Բ�Ǿ���ָ��Rrd���������������д�֣����ü����ֵ�λ��

		//���ñ���
		LOGFONT f;                          //������ʽָ��
		gettextstyle(&f);					//��ȡ������ʽ
		f.lfHeight = 50;
		_tcscpy_s(f.lfFaceName, _T("����"));	//����
		f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
		settextstyle(&f);                   // ����������ʽ
		setbkmode(TRANSPARENT);             //���屳��͸��
		settextcolor(WHITE);
		drawtext(_T("��ѯ��������ע����ʣ����������"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

		//�������˵�ѡ��
		settextstyle(38, 0, _T("����"));
		setbkmode(TRANSPARENT);             //���屳��͸��
		settextcolor(WHITE);
		drawtext(_T("������һ��"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������Rrd���������֣�ˮƽ���У���ֱ���У�������ʾ

		//������ʾ�Ľ�������
		settextstyle(32, 0, _T("����"));
		setbkmode(TRANSPARENT);             //���屳��͸��
		settextcolor(WHITE);

		outtextxy(50, 150, "ע������");
		outtextxy(260, 150, "ע�������");
		outtextxy(470, 150, "����ʣ����������");

		//������ʾ��ע���
		settextstyle(32, 0, _T("����"));
		setbkmode(TRANSPARENT);             //���屳��͸��
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

		//������ʾʣ�������������
		while (1) {
			m3 = getmessage();
			if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
				setlinecolor(GREEN);
				roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
				if (m3.message == WM_LBUTTONDOWN) {
					menu1();//���ع������(��һ��)
				}
			}
			else {
				setlinecolor(WHITE);
				roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
			}
		}
	}
}

//ԤԼ����
void menu2()
{
	//������2
	ExMessage m2;
	cleardevice();

	//����ͼ
	IMAGE img;
	loadimage(NULL, _T("imag1.jpg"));

	//��Բ�Ǿ��Σ��������水ť
	roundrect(r21[0], r21[1], r21[2], r21[3], 50, 50);
	roundrect(r22[0], r22[1], r22[2], r22[3], 50, 50);
	roundrect(r23[0], r23[1], r23[2], r23[3], 50, 50);
	roundrect(r24[0], r24[1], r24[2], r24[3], 50, 50);

	RECT r = { 0, 0, 799, 140 };					//����������λ��
	//������ѡ��λ��
	RECT R21 = { r21[0], r21[1], r21[2], r21[3] };//Բ�Ǿ���ָ��R11���������������д�֣����ü����ֵ�λ��
	RECT R22 = { r22[0], r22[1], r22[2], r22[3] };
	RECT R23 = { r23[0], r23[1], r23[2], r23[3] };
	RECT R24 = { r24[0], r24[1], r24[2], r24[3] };

	//���ñ���
	LOGFONT f;                          //������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("����"));	//����
	f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
	settextstyle(&f);                   // ����������ʽ
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(BLACK);
	drawtext(_T("��ҪԤԼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

	//����ѡ��
	settextstyle(36, 0, _T("����"));
	setbkmode(TRANSPARENT);             //���屳��͸��
	settextcolor(BLACK);
	drawtext(_T("����ԤԼ"), &R21, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������R21���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("��ѯ����ԤԼ��Ϣ"), &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("ȡ������ԤԼ"), &R23, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("�������˵�"), &R24, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//����ԤԼ����ѡ���������
	while (1)
	{
		m2 = getmessage();//��ȡ������
		//��������¡�����ԤԼ��ʱ���еĲ���
		//����ԤԼ����
		if (m2.x > r21[0] && m2.x < r21[2] && m2.y>r21[1] && m2.y < r21[3]) {
			setlinecolor(GREEN);
			roundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
			if (m2.message == WM_LBUTTONDOWN)    //���롰����ע���(����Ա)���Ľ���
			{
				BookingMenu();
			}
		}
		//��ѯ����ԤԼ��Ϣ
		else if (m2.x >= r22[0] && m2.x <= r22[2] && m2.y >= r22[1] && m2.y <= r22[3]) {
			setlinecolor(GREEN);
			roundrect(r22[0], r22[1], r22[2], r22[3], r22[4], r22[5]);
			if (m2.message == WM_LBUTTONDOWN)
			{
				FindBookingMenu();
			}
		}
		//ȡ������ԤԼ��Ϣ
		else if (m2.x >= r23[0] && m2.x <= r23[2] && m2.y >= r23[1] && m2.y <= r23[3]) {
			setlinecolor(GREEN);
			roundrect(r23[0], r23[1], r23[2], r23[3], r23[4], r23[5]);
			if (m2.message == WM_LBUTTONDOWN) {
				CancelMenu();
			}
		}
		//�������˵�
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

//����ԤԼ����
void BookingMenu()
{
	int found = 0;
	int pointIndex, date;
	int i, j, reserved = 0;
	char id[20]; char name[50]; char address[100];//��λ����������
	int okneddle;//�Ѿ�ע���������
	Node* newNode;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "ԤԼʧ��", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "������ҪԤԼ��ע�����ţ�", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				found = 1;
				char s1[101];
				InputBox(s1, 101, "��������ҪԤԼ�����ڣ�", NULL, NULL, 0, 0, false);
				date = atoi(s1);
				InputBox(id, 101, "�������������֤�ţ�", NULL, NULL, 0, 0, false);
				InputBox(name, 101, "���������������", NULL, NULL, 0, 0, false);

				Node* TMP = vaccinationPoints[i].reservations;
				while (TMP != NULL) {
					if (strcmp(TMP->data.id, id) == 0) {
						HWND hwndInput1 = GetHWnd();
						int isok = MessageBox(hwndInput1, "���Ѿ�ԤԼ���ˣ������ظ�ԤԼ��", "ԤԼʧ��", MB_OK);
						return;
					}
					TMP = TMP->next;
				}
				InputBox(address, 101, "��������ĵ�λ���������ƣ�", NULL, NULL, 0, 0, false);
				char s2[101];
				InputBox(s2, 101, "���������Ѿ�ע�����������", NULL, NULL, 0, 0, false);
				okneddle = atoi(s2);
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "�������ע��㲻���ڣ�", "ԤԼʧ��", MB_OK);
		}
		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				//�����ݴ���ṹ����
				if (vaccinationPoints[i].date[date].reservedCount < vaccinationPoints[i].date[date].totalVaccines) {
					//ԤԼ��Ϊ��ǰ���ԤԼ��+1
					reserved = vaccinationPoints[i].date[date].maxReservationNumber + 1;
					vaccinationPoints[i].date[date].maxReservationNumber = reserved;
					vaccinationPoints[i].date[date].reservedCount++;
					//�����µ�ԤԼ�ڵ�
					newNode = (Node*)malloc(sizeof(Node));
					strcpy_s(newNode->data.id, id);
					strcpy_s(newNode->data.name, name);
					strcpy_s(newNode->data.address, address);
					newNode->data.okneddle = okneddle;
					newNode->data.date1 = date;
					newNode->data.reservationNumber = reserved;
					newNode->next = NULL;
					//��ԤԼ�ڵ��������β��
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
					int isok = MessageBox(hwndInput1, "����ȷ�ϲ鿴����ԤԼ��", "ԤԼ�ɹ�", MB_OK);
					//������ת��Ϊ�ַ���
					char reserved1[101];
					_itoa_s(reserved, reserved1, 10);
					int isok2 = MessageBox(hwndInput1, reserved1, "����ԤԼ����", MB_OK);
				}
				else {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "��ע��㵱��������Լ����", "ԤԼʧ��", MB_OK);
				}
				break;
			}
		}
	}
}

//��ѯ����ԤԼ��Ϣ����
void FindBookingMenu()
{
	char id[20];
	int i, j, found = 0;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		InputBox(id, 101, "�������������֤�ţ�", NULL, NULL, 0, 0, false);
		for (i = 1; i <= vaccinationPointCount; i++) {
			temp = vaccinationPoints[i].reservations;
			while (temp != NULL) {
				if (strcmp(temp->data.id, id) == 0) {
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "����ȷ���鿴", "��ѯ�ɹ�", MB_OK);
					ExMessage m3;
					cleardevice();


					//����ͼ
					IMAGE img;
					loadimage(NULL, _T("imag1.jpg"));

					//�����������˵���Բ�Ǿ���
					roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

					RECT r = { 0, 0, 799, 140 };					//��ѯĳ������ʣ���������桰���⡱λ��
					RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//Բ�Ǿ���ָ��Rrd���������������д�֣����ü����ֵ�λ��

					//���ñ���
					LOGFONT f;                          //������ʽָ��
					gettextstyle(&f);					//��ȡ������ʽ
					f.lfHeight = 50;
					_tcscpy_s(f.lfFaceName, _T("����"));	//����
					f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
					settextstyle(&f);                   // ����������ʽ
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(BLACK);
					drawtext(_T("��ѯ����ԤԼ��Ϣ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

					//�������˵�ѡ��
					settextstyle(38, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(BLACK);
					drawtext(_T("������һ��"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������Rrd���������֣�ˮƽ���У���ֱ���У�������ʾ

					//������ʾ�Ľ�������
					settextstyle(24, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(BLACK);

					outtextxy(10, 150, "ע���");
					outtextxy(100, 150, "����");
					outtextxy(180, 150, "���֤��");
					outtextxy(310, 150, "����");
					outtextxy(400, 150, "��λ������");
					outtextxy(540, 150, "��ע������");
					outtextxy(670, 150, "ԤԼ�ɹ���");

					//������ʾ��ԤԼ��
					settextstyle(24, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(RED);

					//����תΪ�ַ���
					char date1[10], okneddle1[10], reservationNumber1[101];
					_itoa_s(temp->data.date1, date1, 10);
					_itoa_s(temp->data.okneddle, okneddle1, 10);
					_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

					outtextxy(10, 60 + 150, vaccinationPoints[i].name);     //ע���
					outtextxy(100 + 18, 60 + 150, date1);					//����
					outtextxy(180, 60 + 150, temp->data.id);				//���֤��
					outtextxy(310, 60 + 150, temp->data.name);				//����
					outtextxy(400, 60 + 150, temp->data.address);			//��λ����������
					outtextxy(540 + 50, 60 + 150, okneddle1);				//�Ѿ�ע�������
					outtextxy(670 + 50, 60 + 150, reservationNumber1);		//ԤԼ�ɹ���
					found = 1;

					//������ʾԤԼ��ѯ��������
					while (1) {
						m3 = getmessage();
						if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
							setlinecolor(GREEN);
							roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
							if (m3.message == WM_LBUTTONDOWN) {
								menu2();//����ԤԼ����(��һ��)
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
			int isok = MessageBox(hwndInput1, "δ�ҵ������֤�ŵ�ԤԼ��Ϣ!", "��ѯʧ��", MB_OK);
		}
		return;
	}
}

//ȡ������ԤԼ
void CancelMenu()
{
	char id[20];
	int i, j, found = 0;
	Node* temp;
	Node* prev;

	InputBox(id, 101, "��������Ҫȡ�������֤�ţ�", NULL, NULL, 0, 0, false);

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
				int isok = MessageBox(hwndInput1, "ԤԼ�ѳɹ�ȡ��!", "ȡ���ɹ�", MB_OK);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	if (found == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "δ�ҵ������֤�ŵ�ԤԼ��Ϣ!", "ȡ��ʧ��", MB_OK);
	}
	return;
}

//��ѯĳע��㱾���ڴ�ڶ��������
void FindSecondDoseCountMenu()
{
	int pointIndex;
	int i, count = 0;
	Node* temp;
	int found = 0;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		char s[101];
		InputBox(s, 101, "������Ҫ��ѯ��ע�����ţ�", NULL, NULL, 0, 0, false);
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
			int isok = MessageBox(hwndInput1, "δ�ҵ���ע�����Ϣ!", "��ѯʧ��", MB_OK);
		}
		else
		{
			//������ת��Ϊ�ַ���
			char count1[101];
			_itoa_s(count, count1, 10);
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "����ȷ�ϲ鿴�������ڸ�ע���Ҫ��ڶ��������", "��ѯ�ɹ�", MB_OK);
			int isok1 = MessageBox(hwndInput1, count1, "�������ڸ�ע���Ҫ��ڶ��������", MB_OK);
		}
		return;
	}
}

//ˬԼ��¼
void FindAbsenteesMenu()
{
	int pointIndex, date;
	int i, found = 0;
	int j = 0;
	Node* temp;
	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		//����¼�m3
		ExMessage m3;

		char s[101], s1[101];
		InputBox(s, 101, "������Ҫ��ѯ��ע�����ţ�", NULL, NULL, 0, 0, false);
		InputBox(s1, 101, "������Ҫ��ѯ�����ڣ�", NULL, NULL, 0, 0, false);
		pointIndex = atoi(s);
		date = atoi(s1);

		for (i = 1; i <= vaccinationPointCount; i++) {
			if (vaccinationPoints[i].index == pointIndex) {
				temp = vaccinationPoints[i].reservations;
				while (temp != NULL) {
					if (temp->data.okneddle == 0 && temp->data.date1 == date) {
						//����ж��ˬԼ����Ϣ��ֻ��ʾһ�β�ѯ�ɹ����ѣ��Լ��ڵ�һ�ν��������úã�����������²��ñ�������Ϣ����
						if (j == 0) {
							HWND hwndInput1 = GetHWnd();
							int isok = MessageBox(hwndInput1, "����ȷ���鿴", "��ѯ�ɹ�", MB_OK);
							cleardevice();
							//����ͼ
							IMAGE img;
							loadimage(NULL, _T("imag.jpg"));
						}
						//�����������˵���Բ�Ǿ���
						roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

						RECT r = { 0, 0, 799, 140 };					//��ѯĳ������ʣ���������桰���⡱λ��
						RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//Բ�Ǿ���ָ��Rrd���������������д�֣����ü����ֵ�λ��

						//���ñ���
						LOGFONT f;                          //������ʽָ��
						gettextstyle(&f);					//��ȡ������ʽ
						f.lfHeight = 50;
						_tcscpy_s(f.lfFaceName, _T("����"));	//����
						f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
						settextstyle(&f);                   // ����������ʽ
						setbkmode(TRANSPARENT);             //���屳��͸��
						settextcolor(WHITE);
						drawtext(_T("��ѯ����ԤԼ��Ϣ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

						//������һ��ѡ��
						settextstyle(38, 0, _T("����"));
						setbkmode(TRANSPARENT);             //���屳��͸��
						settextcolor(WHITE);
						drawtext(_T("������һ��"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������Rrd���������֣�ˮƽ���У���ֱ���У�������ʾ

						//������ʾ�Ľ�������
						settextstyle(24, 0, _T("����"));
						setbkmode(TRANSPARENT);             //���屳��͸��
						settextcolor(WHITE);

						outtextxy(10, 150, "ע���");
						outtextxy(100, 150, "����");
						outtextxy(180, 150, "���֤��");
						outtextxy(310, 150, "����");
						outtextxy(400, 150, "��λ������");
						outtextxy(540, 150, "��ע������");
						outtextxy(670, 150, "ԤԼ�ɹ���");

						//������ʾ��ˬԼ��
						settextstyle(24, 0, _T("����"));
						setbkmode(TRANSPARENT);             //���屳��͸��
						settextcolor(RED);

						//����תΪ�ַ���
						char date1[10], okneddle1[10], reservationNumber1[101];
						_itoa_s(temp->data.date1, date1, 10);
						_itoa_s(temp->data.okneddle, okneddle1, 10);
						_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

						//��ʾˬԼ���˵���Ϣ
						outtextxy(10, 60 + 150 + (j * 60), vaccinationPoints[i].name);     //ע���
						outtextxy(100 + 18, 60 + 150 + (j * 60), date1);					//����
						outtextxy(180, 60 + 150 + (j * 60), temp->data.id);				//���֤��
						outtextxy(310, 60 + 150 + (j * 60), temp->data.name);				//����
						outtextxy(400, 60 + 150 + (j * 60), temp->data.address);			//��λ����������
						outtextxy(540 + 50, 60 + 150 + (j * 60), okneddle1);				//�Ѿ�ע�������
						outtextxy(670 + 50, 60 + 150 + (j * 60), reservationNumber1);		//ԤԼ�ɹ���

						j++;//�����ȣ�����������ȸ�ѡ����ʵ���ʾλ��

						found = 1;
					}
					temp = temp->next;
				}
				break;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "δ�ҵ�����������ˬԼ��¼!", "��ѯ���", MB_OK);
		}
		else
		{
			//������ʾˬԼ��������
			while (1) {
				m3 = getmessage();
				if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
					setlinecolor(GREEN);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
					if (m3.message == WM_LBUTTONDOWN) {
						menu1();//����ԤԼ����(��һ��)
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

//��ѯȡ����ˬԼ��¼
void FindCancelAbsenteesRecordsMenu()
{
	int i, j = 0;
	int found = 0;
	Node* temp;

	if (vaccinationPointCount == 0) {
		HWND hwndInput1 = GetHWnd();
		int isok = MessageBox(hwndInput1, "ϵͳ���������ݣ�����¼������", "��ѯʧ��", MB_OK);
	}
	else {
		//����¼�m3
		ExMessage m3;

		for (i = 1; i <= vaccinationPointCount; i++) {
			temp = vaccinationPoints[i].reservations;
			while (temp != NULL) {
				//�򵥲���
				if (temp->data.okneddle == -1) {
					//����ж��ˬԼ����Ϣ��ֻ��ʾһ�β�ѯ�ɹ����ѣ��Լ��ڵ�һ�ν��������úã�����������²��ñ�������Ϣ����
					if (j == 0) {
						HWND hwndInput1 = GetHWnd();
						int isok = MessageBox(hwndInput1, "����ȷ���鿴", "��ѯ�ɹ�", MB_OK);
						cleardevice();
						//����ͼ
						IMAGE img;
						loadimage(NULL, _T("imag.jpg"));
					}

					//�����������˵���Բ�Ǿ���
					roundrect(rd[0], rd[1], rd[2], rd[3], 50, 50);

					RECT r = { 0, 0, 799, 140 };					//��ѯĳ������ʣ���������桰���⡱λ��
					RECT Rrd = { rd[0], rd[1], rd[2], rd[3] };		//Բ�Ǿ���ָ��Rrd���������������д�֣����ü����ֵ�λ��

					//���ñ���
					LOGFONT f;                          //������ʽָ��
					gettextstyle(&f);					//��ȡ������ʽ
					f.lfHeight = 50;
					_tcscpy_s(f.lfFaceName, _T("����"));	//����
					f.lfQuality = ANTIALIASED_QUALITY;  // ����� 
					settextstyle(&f);                   // ����������ʽ
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(WHITE);
					drawtext(_T("��ѯ����ԤԼ��Ϣ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //�������

					//������һ��ѡ��
					settextstyle(38, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(WHITE);
					drawtext(_T("������һ��"), &Rrd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��Բ�Ǿ�������Rrd���������֣�ˮƽ���У���ֱ���У�������ʾ

					//������ʾ�Ľ�������
					settextstyle(24, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(WHITE);

					outtextxy(10, 150, "ע���");
					outtextxy(100, 150, "����");
					outtextxy(180, 150, "���֤��");
					outtextxy(310, 150, "����");
					outtextxy(400, 150, "��λ������");
					outtextxy(540, 150, "��ע������");
					outtextxy(670, 150, "ԤԼ�ɹ���");

					//������ʾ��ˬԼ��ȡ������
					settextstyle(24, 0, _T("����"));
					setbkmode(TRANSPARENT);             //���屳��͸��
					settextcolor(RED);

					//����תΪ�ַ���
					char date1[10], okneddle1[10], reservationNumber1[101];
					_itoa_s(temp->data.date1, date1, 10);
					_itoa_s(temp->data.okneddle, okneddle1, 10);
					_itoa_s(temp->data.reservationNumber, reservationNumber1, 10);

					//��ʾˬԼ���˵���Ϣ
					outtextxy(10, 60 + 150 + (j * 60), vaccinationPoints[i].name);     //ע���
					outtextxy(100 + 18, 60 + 150 + (j * 60), date1);					//����
					outtextxy(180, 60 + 150 + (j * 60), temp->data.id);				//���֤��
					outtextxy(310, 60 + 150 + (j * 60), temp->data.name);				//����
					outtextxy(400, 60 + 150 + (j * 60), temp->data.address);			//��λ����������
					outtextxy(540 + 50, 60 + 150 + (j * 60), okneddle1);				//�Ѿ�ע�������
					outtextxy(670 + 50, 60 + 150 + (j * 60), reservationNumber1);		//ԤԼ�ɹ���

					j++;//�����ȣ�����������ȸ�ѡ����ʵ���ʾλ��

					found = 1;
				}
				temp = temp->next;
			}
		}
		if (found == 0) {
			HWND hwndInput1 = GetHWnd();
			int isok = MessageBox(hwndInput1, "δ�ҵ�����������ȡ����ˬԼ��¼!", "��ѯ���", MB_OK);
		}
		else {
			//������ʾԤԼ��ѯ��������
			while (1) {
				m3 = getmessage();
				if (m3.x > rd[0] && m3.x < rd[2] && m3.y>rd[1] && m3.y < rd[3]) {
					setlinecolor(GREEN);
					roundrect(rd[0], rd[1], rd[2], rd[3], rd[4], rd[5]);
					if (m3.message == WM_LBUTTONDOWN) {
						menu1();//����ԤԼ����(��һ��)
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


//�浵
void saveDataToFile()
{
	int i;
	FILE* fp;
	fopen_s(&fp, "data.txt", "wb");
	if (fp == NULL) {
		return;
	}
	fwrite(&vaccinationPointCount, sizeof(int), 1, fp); //д��ע�������
	fwrite(vaccinationPoints, sizeof(VaccinationPoint), vaccinationPointCount + 1, fp); //д��ע�����Ϣ����
	//д��ԤԼ����Ϣ
	for (i = 1; i <= vaccinationPointCount; i++) {
		struct Node* current = vaccinationPoints[i].reservations;
		while (current != NULL) {
			fwrite(&current->data, sizeof(Person), 1, fp); // д��ԤԼ����Ϣ
			current = current->next;
		}
	}
	fclose(fp);
}

//����
void loadDataFromFile()
{
	int i, j;
	FILE* fp;
	fopen_s(&fp, "data.txt", "rb");
	if (fp == NULL) {
		return;
	}
	fread(&vaccinationPointCount, sizeof(int), 1, fp); //��ȡע�������
	fread(vaccinationPoints, sizeof(VaccinationPoint), vaccinationPointCount + 1, fp); //��ȡע�����Ϣ����
	for (i = 1; i <= vaccinationPointCount; i++) {
		vaccinationPoints[i].reservations = NULL; //��ʼ��ԤԼ����ͷָ��
		for (j = 1; j <= 10; j++) {
			struct Node* newNode = NULL;
			// ��ȡԤԼ����Ϣ
			while (1) {
				struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
				fread(&temp->data, sizeof(Person), 1, fp); //��ȡԤԼ����Ϣ
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
	//����
	loadDataFromFile();
	//��ͼ���ڳ�ʼ��
	initgraph(800, 730, SHOWCONSOLE);
	menu();

	//�������п���̨��������˳�
	_getch();
	closegraph();
}
