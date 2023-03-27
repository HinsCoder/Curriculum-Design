#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<graphics.h>
#include<iostream>
#include<stdlib.h>	//标准库头文件
#include<mysql.h>	//mysql文件
#include<vector>	
#include<chrono>	// 时间库
#include<Windows.h>

using namespace std;

// 杂志信息
typedef struct Magazine
{
	int magid;			// 杂志ID
	string magname;		// 杂志名字
	int magtotal;		// 杂志数量
	double magprice;	// 杂志单价
}Magazine;


class MagazineFun
{
	MagazineFun()
	{
		con = mysql_init(NULL);
		//设置字符编码
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
		initgraph(1080, 720); // 初始化窗口
		IMAGE img;
		loadimage(&img, _T("阅览室.jpg"));
		putimage(0, 0, &img);
		setbkcolor(WHITE); // 设置背景颜色
		setbkmode(TRANSPARENT); // 设置文字背景透明
		//cleardevice(); // 清空窗口

		// 绘制欢迎文字
		settextcolor(BLACK);
		settextstyle(55, 0, _T("黑体"));
		outtextxy(420, 70, _T("杂志信息"));

		// 绘制标题
		settextcolor(BLACK);
		settextstyle(30, 0, _T("黑体"));
		outtextxy(130, 140, _T("杂志ID        杂志名字        杂志数量        杂志单价"));

		// 输出杂志信息
		settextcolor(BLACK);
		settextstyle(25, 0, _T("楷体"));

		if (!MagazineList.empty())
		{
			for (int i = 0; i < MagazineList.size(); i++)
			{
				Magazine magazine = MagazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

				// 方法1（已弃用）
				// 将string类型的magazine.magname转化为wchar_t类型的magname，然后输出到屏幕上
				//TCHAR magname[20];
				//string mmn = magazine.magname.c_str();
				//std::wstring wmmn = std::wstring(mmn.begin(), mmn.end());
				//const wchar_t* wcmmn = wmmn.c_str();
				//_stprintf(magname, _T("%s"), wcmmn);
				//outtextxy(360, 170 + i * 30, magname);
				
				// 方法2（已弃用）
				//TCHAR wc[MAX_PATH];
				//#ifdef UNICODE
				//_stprintf_s(wc, MAX_PATH, _T("%S"), mmn.c_str());//%S宽字符
				//#else
				//_stprintf_s(wc, MAX_PATH, _T("%s"), mmn.c_str());//%s单字符
				//#endif

				string mmn = magazine.magname;
				TCHAR t_mmn[256];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)mmn.c_str(), -1, t_mmn, 256);
				//outtextxy(370, 190 + i * 30, t_mmn);

				// 在屏幕中央输出字符串
				RECT r = { 250, 190 + i * 30, 550, 215 + i * 30 };
				drawtext(t_mmn, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	// 在矩形内水平居中显示文字


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
		settextstyle(30, 0, _T("黑体"));
		outtextxy(130, 600, _T("返回"));
		while (true)
		{
			if (MouseHit()) // 检测鼠标事件
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
				{
					if (msg.x > 130 && msg.x < 175 && msg.y > 600 && msg.y < 630) // 返回
					{
						break;
					}
				}
			}
		}
	}

	static void display(Magazine magazine)
	{
		initgraph(1080, 720); // 初始化窗口
		IMAGE img;
		loadimage(&img, _T("阅览室.jpg"));
		putimage(0, 0, &img);
		setbkcolor(WHITE); // 设置背景颜色
		setbkmode(TRANSPARENT); // 设置文字背景透明
		//cleardevice(); // 清空窗口

		// 绘制欢迎文字
		settextcolor(BLACK);
		settextstyle(55, 0, _T("黑体"));
		outtextxy(360, 60, _T("杂志信息"));

		// 绘制标题
		settextcolor(BLACK);
		settextstyle(30, 0, _T("黑体"));
		outtextxy(130, 150, _T("杂志ID\t杂志名字\t杂志数量\t杂志单价"));

		// 输出杂志信息
		settextcolor(BLACK);
		settextstyle(20, 0, _T("楷体"));

		TCHAR magid[5];
		_stprintf(magid, _T("%d"), magazine.magid);
		outtextxy(130, 170, magid);

		// 将string类型的magazine.magname转化为wchar_t类型的magname，然后输出到屏幕上
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


// 用户信息
typedef struct User
{
	int userid;			// 用户ID
	string userpassword;// 用户密码
	int userpower;		// 用户权限
	string username;	// 用户名
	string useridcard;	// 用户身份证
}User;

class UserFun
{
	UserFun()
	{
		con = mysql_init(NULL);
		//设置字符编码
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
// 订阅信息
typedef struct Subscribe
{
	int subid;			// 订阅ID
	int magid;			// 杂志ID
	int userid;			// 用户ID
	string subdate;		// 订阅日期
	int subnumber;		// 订阅数量
	double subtotal;	// 小计
	//string substate;		// 订阅状态（自动续费/一次性）	待开发

}Subscribe;

class SubscribeFun
{
	SubscribeFun()
	{
		con = mysql_init(NULL);
		//设置字符编码
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

//wchar_t转化为string
static void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte的运用
	char* psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

