#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<graphics.h>
#include<iostream>
#include<stdlib.h>	//��׼��ͷ�ļ�
#include<mysql.h>	//mysql�ļ�
#include<vector>	
#include<chrono>	// ʱ���
#include<Windows.h>

using namespace std;

// ��־��Ϣ
typedef struct Magazine
{
	int magid;			// ��־ID
	string magname;		// ��־����
	int magtotal;		// ��־����
	double magprice;	// ��־����
}Magazine;


class MagazineFun
{
	MagazineFun()
	{
		con = mysql_init(NULL);
		//�����ַ�����
		mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

		if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
		{
			std::cout << "Failed to conncet" << std::endl;
			exit(1);
		}
	}

	~MagazineFun()
	{
		mysql_close(con);
	}
public:

	static MagazineFun* GetInstance()
	{
		static MagazineFun magazineFun;
		return &magazineFun;
	}

	

	vector<Magazine> queryAllMagazine();

	vector<Magazine> queryMagazine(Magazine magazine, int queryMode);

	void queryMagazinePage();
	void addMagazine();
	void modifyMagazine();
	void deleteMagazine();


	static void display(vector<Magazine>& MagazineList)
	{
		initgraph(1080, 720); // ��ʼ������
		IMAGE img;
		loadimage(&img, _T("������.jpg"));
		putimage(0, 0, &img);
		setbkcolor(WHITE); // ���ñ�����ɫ
		setbkmode(TRANSPARENT); // �������ֱ���͸��
		//cleardevice(); // ��մ���

		// ���ƻ�ӭ����
		settextcolor(BLACK);
		settextstyle(55, 0, _T("����"));
		outtextxy(420, 70, _T("��־��Ϣ"));

		// ���Ʊ���
		settextcolor(BLACK);
		settextstyle(30, 0, _T("����"));
		outtextxy(130, 140, _T("��־ID        ��־����        ��־����        ��־����"));

		// �����־��Ϣ
		settextcolor(BLACK);
		settextstyle(25, 0, _T("����"));

		if (!MagazineList.empty())
		{
			for (int i = 0; i < MagazineList.size(); i++)
			{
				Magazine magazine = MagazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

				// ����1�������ã�
				// ��string���͵�magazine.magnameת��Ϊwchar_t���͵�magname��Ȼ���������Ļ��
				//TCHAR magname[20];
				//string mmn = magazine.magname.c_str();
				//std::wstring wmmn = std::wstring(mmn.begin(), mmn.end());
				//const wchar_t* wcmmn = wmmn.c_str();
				//_stprintf(magname, _T("%s"), wcmmn);
				//outtextxy(360, 170 + i * 30, magname);
				
				// ����2�������ã�
				//TCHAR wc[MAX_PATH];
				//#ifdef UNICODE
				//_stprintf_s(wc, MAX_PATH, _T("%S"), mmn.c_str());//%S���ַ�
				//#else
				//_stprintf_s(wc, MAX_PATH, _T("%s"), mmn.c_str());//%s���ַ�
				//#endif

				string mmn = magazine.magname;
				TCHAR t_mmn[256];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)mmn.c_str(), -1, t_mmn, 256);
				//outtextxy(370, 190 + i * 30, t_mmn);

				// ����Ļ��������ַ���
				RECT r = { 250, 190 + i * 30, 550, 215 + i * 30 };
				drawtext(t_mmn, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	// �ھ�����ˮƽ������ʾ����


				TCHAR magtotal[5];
				_stprintf(magtotal, _T("%d"), magazine.magtotal);
				outtextxy(630, 190 + i * 30, magtotal);

				TCHAR magprice[10];
				_stprintf(magprice, _T("%.2f"), magazine.magprice);
				outtextxy(855, 190 + i * 30, magprice);

			}
		}
		//system("pause");
		//_getch();
		settextcolor(BLACK);
		settextstyle(30, 0, _T("����"));
		outtextxy(130, 600, _T("����"));
		while (true)
		{
			if (MouseHit()) // �������¼�
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // ����������
				{
					if (msg.x > 130 && msg.x < 175 && msg.y > 600 && msg.y < 630) // ����
					{
						break;
					}
				}
			}
		}
	}

	static void display(Magazine magazine)
	{
		initgraph(1080, 720); // ��ʼ������
		IMAGE img;
		loadimage(&img, _T("������.jpg"));
		putimage(0, 0, &img);
		setbkcolor(WHITE); // ���ñ�����ɫ
		setbkmode(TRANSPARENT); // �������ֱ���͸��
		//cleardevice(); // ��մ���

		// ���ƻ�ӭ����
		settextcolor(BLACK);
		settextstyle(55, 0, _T("����"));
		outtextxy(360, 60, _T("��־��Ϣ"));

		// ���Ʊ���
		settextcolor(BLACK);
		settextstyle(30, 0, _T("����"));
		outtextxy(130, 150, _T("��־ID\t��־����\t��־����\t��־����"));

		// �����־��Ϣ
		settextcolor(BLACK);
		settextstyle(20, 0, _T("����"));

		TCHAR magid[5];
		_stprintf(magid, _T("%d"), magazine.magid);
		outtextxy(130, 170, magid);

		// ��string���͵�magazine.magnameת��Ϊwchar_t���͵�magname��Ȼ���������Ļ��
		TCHAR magname[20];
		string mmn = magazine.magname.c_str();
		wstring wmmn = wstring(mmn.begin(), mmn.end());
		const wchar_t* wcmmn = wmmn.c_str();
		_stprintf(magname, _T("%s"), wcmmn);
		outtextxy(330, 170, magname);

		TCHAR magtotal[5];
		_stprintf(magtotal, _T("%d"), magazine.magtotal);
		outtextxy(530, 170, magtotal);

		TCHAR magprice[10];
		_stprintf(magprice, _T("%lf"), magazine.magprice);
		outtextxy(530, 170, magprice);
	}

private:
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "sa";
	const char* database_name = "magasys";
	const int port = 3306;
};


// �û���Ϣ
typedef struct User
{
	int userid;			// �û�ID
	string userpassword;// �û�����
	int userpower;		// �û�Ȩ��
	string username;	// �û���
	string useridcard;	// �û����֤
}User;

class UserFun
{
	UserFun()
	{
		con = mysql_init(NULL);
		//�����ַ�����
		mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

		if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
		{
			std::cout << "Failed to conncet" << std::endl;
			exit(1);
		}
	}

	~UserFun()
	{
		mysql_close(con);
	}
public:

	static UserFun* GetInstance()
	{
		static UserFun userFun;
		return &userFun;
	}

	User queryUser(string username, string password);
	int CheckisExistUser(string username, string password);
	User registerUser(string username, string password, string useridcard);
	int loginoutUser(string username, string password);

private:
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "sa";
	const char* database_name = "magasys";
	const int port = 3306;
};
// ������Ϣ
typedef struct Subscribe
{
	int subid;			// ����ID
	int magid;			// ��־ID
	int userid;			// �û�ID
	string subdate;		// ��������
	int subnumber;		// ��������
	double subtotal;	// С��
	//string substate;		// ����״̬���Զ�����/һ���ԣ�	������

}Subscribe;

class SubscribeFun
{
	SubscribeFun()
	{
		con = mysql_init(NULL);
		//�����ַ�����
		mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

		if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
		{
			std::cout << "Failed to conncet" << std::endl;
			exit(1);
		}
	}

	~SubscribeFun()
	{
		mysql_close(con);
	}
public:

	static SubscribeFun* GetInstance()
	{
		static SubscribeFun subscribeFun;
		return &subscribeFun;
	}

	void subscribeMagazine(User user);

	Magazine queryAvailableMagazine(string magname);

	void decreaseMagazineNumber(Magazine magazine, int number);
	void addSubscribe(Subscribe subscribe);
	void querysubscribeRecord(User user);
	//vector<Subscribe> querySubscribeRecordByUserId(int userid);

	//void deleteSubscribe();

private:
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "sa";
	const char* database_name = "magasys";
	const int port = 3306;
};

static User loginConsole();

//wchar_tת��Ϊstring
static void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte������
	char* psText;  // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete[]psText;// psText�����
}

