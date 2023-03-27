#include"fun.h"

// 查询杂志
void MagazineFun::queryMagazinePage()
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
	outtextxy(420, 60, _T("查询杂志"));
	vector<Magazine> magazineList;
	while (true)
	{
		// 绘制功能选项
		settextstyle(30, 0, _T("黑体"));
		outtextxy(130, 200, _T("0.返回上级菜单"));
		outtextxy(130, 300, _T("1.查询所有杂志"));
		outtextxy(130, 400, _T("2.按杂志名查询"));

		if (MouseHit()) // 检测鼠标事件
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
			{
				if (msg.x > 130 && msg.x < 380 && msg.y > 200 && msg.y < 220) // 选择0
				{
					break;
				}
				else if (msg.x > 130 && msg.x < 380 && msg.y > 300 && msg.y < 320) // 选择1
				{
					magazineList = MagazineFun::GetInstance()->queryAllMagazine();
					MagazineFun::display(magazineList);
					break;
				}
				else if (msg.x > 130 && msg.x < 380 && msg.y > 400 && msg.y < 420) // 选择2
				{
					string magname;

					wchar_t mn[20];
					InputBox(mn, 20, L"请输入杂志名：");
					Wchar_tToString(magname, mn);

					Magazine magazine;
					magazine.magname = magname;
					magazineList = MagazineFun::GetInstance()->queryMagazine(magazine, 1);
					MagazineFun::display(magazineList);
					break;
				}
			}
		}
	}
	
}

// 查询全部杂志
vector<Magazine> MagazineFun::queryAllMagazine()
{
	vector<Magazine> magazineList;

	char sql[1024];
	sprintf(sql, "SELECT * FROM magazine");

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		Magazine magazine;
		magazine.magid = atoi(row[0]);		// 将字符串转化为int类型变量
		magazine.magname = row[1];
		magazine.magtotal = atoi(row[2]);
		magazine.magprice = atof(row[3]);	// 将字符串转化为double类型变量

		magazineList.push_back(magazine);

	}
	return magazineList;
}

// 按杂志名或ID查询杂志
vector<Magazine> MagazineFun::queryMagazine(Magazine magazine, int queryMode)
{
	vector<Magazine> magazineList;

	char sql[1024];
	switch (queryMode)
	{
	case 1:
	{
		sprintf(sql, "SELECT * FROM magazine WHERE magname like '%%%s%%'", magazine.magname.c_str());		

		if (mysql_query(con, sql))
		{
			fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
			return {};
		}
		break;
	}

	case 2:
	{
		sprintf(sql, "SELECT * FROM magazine WHERE magid = %d", magazine.magid);		

		if (mysql_query(con, sql))
		{
			fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
			return {};
		}
		break;
	}
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);

	//Magazine magazine;
	magazine.magid = atoi(row[0]);		// 将字符串转化为int类型变量
	magazine.magname = row[1];
	magazine.magtotal = atoi(row[2]);
	magazine.magprice = atof(row[3]);	// 将字符串转化为double类型变量

	magazineList.push_back(magazine);

	return magazineList;
}



void MagazineFun::addMagazine()
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
	outtextxy(420, 70, _T("添加杂志"));
	vector<Magazine> magazineList;

	string magname;
	int magtotal;
	double magprice;

	wchar_t mn[20];
	InputBox(mn, 20, L"请输入杂志名：");
	Wchar_tToString(magname, mn);

	wchar_t mt[10];
	InputBox(mt, 10, L"请输入杂志数量：");
	magtotal = _wtoi(mt);

	wchar_t mp[10];
	InputBox(mp, 10, L"请输入杂志单价：");
	magprice = _wtof(mp);

	Magazine magazine;
	magazine.magname = magname;
	magazine.magtotal = magtotal;
	magazine.magprice = magprice;

	char sql[1024];
	sprintf(sql, "INSERT INTO magazine (magname, magtotal, magprice) VALUES ('%s', '%d', '%.2f')", magname.c_str(), magtotal, magprice);

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to add data : Error:%s\n", mysql_error(con));
	}

	MessageBox(NULL, _T("添加成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；

}

void MagazineFun::modifyMagazine()
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
	outtextxy(420, 70, _T("修改杂志"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// 绘制标题
	settextcolor(BLACK);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(130, 140, _T("杂志ID        杂志名字        杂志数量        杂志单价"));

	// 输出杂志信息
	settextcolor(BLACK);
	settextstyle(25, 0, _T("楷体"));

	//int magid_ret;

	while(true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// 打印信息
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // 检测鼠标事件
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // 判断鼠标位置是否在某一杂志的位置内
						{
							//magid_ret = magazine.magid;
							MessageBox(NULL, _T("如果不想修改某项，无需输入内容直接确定即可"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；

							string magname;
							//int magtotal;
							//double magprice;

							wchar_t mn[20];
							InputBox(mn, 20, L"请输入新的杂志名：");
							if (wcslen(mn) != 0)
							{
								Wchar_tToString(magname, mn);
								magazine.magname = magname;
							}
							

							wchar_t mt[10];
							InputBox(mt, 10, L"请输入新的杂志数量：");
							if (wcslen(mt) != 0)
							{
								magazine.magtotal = _wtoi(mt);
							}
							

							wchar_t mp[10];
							InputBox(mp, 10, L"请输入新的杂志单价：");
							if (wcslen(mp) != 0)
							{
								magazine.magprice = _wtof(mp);
							}
							
							/*magid_ret = magazine.magid;*/
							char sql[1024];
							sprintf(sql, "UPDATE magazine SET magname ='%s',magtotal = '%d',magprice ='%.2f'"
								"WHERE magid = %d", magazine.magname.c_str(), magazine.magtotal, magazine.magprice, magazine.magid);

							if (mysql_query(con, sql))
							{
								fprintf(stderr, "Failed to update data : Error:%s\n", mysql_error(con));
							}
							break;
						}
					}
					break;
				}
			}
		}

	}

	MessageBox(NULL, _T("修改成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
}


void MagazineFun::deleteMagazine()
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
	outtextxy(420, 70, _T("删除杂志"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// 绘制标题
	settextcolor(BLACK);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(130, 140, _T("杂志ID        杂志名字        杂志数量        杂志单价"));

	// 输出杂志信息
	settextcolor(BLACK);
	settextstyle(25, 0, _T("楷体"));

	//int magid_ret;

	while (true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// 打印信息
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // 检测鼠标事件
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // 判断鼠标位置是否在某一杂志的位置内
						{
							int ret = MessageBox(NULL, _T("是否确认删除？"), _T("提示"), MB_OKCANCEL);		// MB_OKCANCEL：有确定和取消两个按钮
							if (ret == IDOK)
							{
								char sql[1024];
								sprintf(sql, "DELETE FROM magazine WHERE magid = %d", magazine.magid);

								if (mysql_query(con, sql))
								{
									fprintf(stderr, "Failed to delete data : Error:%s\n", mysql_error(con));
								}
								MessageBox(NULL, _T("删除成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
							}
							break;
						}
					}
					break;
				}
			}
		}

	}

}

User UserFun::queryUser(string username, string password)
{
	User user;
	char sql[1024];
	sprintf(sql, "SELECT * FROM user WHERE username = '%s' AND userpassword = '%s'", username.c_str(), password.c_str());

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == NULL) {
		user.userid = 0;
		user.userpassword = "";
		user.userpower = 0;
		user.username = "";
		user.useridcard = "";
	}
	else
	{
		user.userid = atoi(row[0]);
		user.userpassword = row[1];
		user.userpower = atoi(row[2]);
		user.username = row[3];
		user.useridcard = row[4];
	}
	return user;
}

int UserFun::CheckisExistUser(string username, string password)
{
	User user;
	char sql[1024];
	sprintf(sql, "SELECT * FROM user WHERE username = '%s' AND userpassword = '%s'", username.c_str(), password.c_str());

	mysql_query(con, sql);
	MYSQL_RES* res = mysql_store_result(con);
	//MYSQL_RES* res = mysql_use_result(con);
	if (mysql_num_rows(res) > 0)
	{
		return 1;
	}
	return 0;
	//MYSQL_ROW row = mysql_fetch_row(res);

}


User UserFun::registerUser(string username, string password, string useridcard)
{
	User user;
	if (CheckisExistUser(username, password))
	{
		user = queryUser(username, password);
		MessageBox(NULL, _T("该账号已存在，将直接登录"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
		// Sleep(2000);    // 等待2秒钟
	}
	else
	{
		char sql[1024];
		sprintf(sql, "INSERT INTO user (username, userpassword, useridcard) VALUES ('%s', '%s', '%s')", username.c_str(), password.c_str(), useridcard.c_str());

		if (mysql_query(con, sql))
		{
			fprintf(stderr, "Failed to insert data : Error:%s\n", mysql_error(con));
			return {};
		}

		user.username = username;
		user.userpassword = password;
		user.useridcard = useridcard;

		MessageBox(NULL, _T("注册成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；

	}
	return user;
}


int UserFun::loginoutUser(string username, string password)
{
	//User user;
	if (CheckisExistUser(username, password))
	{
		int ret = MessageBox(NULL, _T("确认注销吗？"), _T("提示"), MB_OKCANCEL);		// MB_OKCANCEL：有确定和取消两个按钮
		if (ret == IDOK)
		{
			char sql[1024];
			sprintf(sql, "DELETE FROM user WHERE username = '%s' AND userpassword = '%s'", username.c_str(), password.c_str());

			if (mysql_query(con, sql))
			{
				fprintf(stderr, "Failed to delete data : Error:%s\n", mysql_error(con));
			}

			MessageBox(NULL, _T("注销成功！"), _T("提示"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("取消注销！"), _T("提示"), MB_OK);
			return 1;
		}

	}
	else
	{
		MessageBox(NULL, _T("账号或密码有误！"), _T("错误"), MB_OK);
		return 2;
	}
}

Magazine SubscribeFun::queryAvailableMagazine(string magname)
{
	char sql[1024];

	sprintf(sql, "SELECT * FROM magazine WHERE magname like '%%%s%%'", magname.c_str());		// 似乎有bug

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);

	Magazine magazine;
	magazine.magid = atoi(row[0]);		// 将字符串转化为int类型变量
	magazine.magname = row[1];
	magazine.magtotal = atoi(row[2]);
	magazine.magprice = atof(row[3]);	// 将字符串转化为double类型变量

	return magazine;

}

void SubscribeFun::decreaseMagazineNumber(Magazine magazine, int number)
{
	char sql[1024];
	sprintf(sql, "UPDATE magazine SET magtotal = magtotal - %d WHERE magid = %d", number, magazine.magid);

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to update data : Error:%s\n", mysql_error(con));
	}
}



void SubscribeFun::addSubscribe(Subscribe subscribe)
{
	char sql[1024];
	sprintf(sql, "INSERT INTO subscribe (magid, userid, subdate, subnumber, subtotal) VALUES (%d, %d, '%s', %d, '%lf')", subscribe.magid, subscribe.userid, subscribe.subdate.c_str(), subscribe.subnumber, subscribe.subtotal);

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to add data : Error:%s\n", mysql_error(con));
	}

	//cout << "订阅信息已成功添加到数据库！" << endl;

}

void SubscribeFun::subscribeMagazine(User user) {

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
	outtextxy(420, 70, _T("订阅杂志"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// 绘制标题
	settextcolor(BLACK);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(130, 140, _T("杂志ID        杂志名字        杂志数量        杂志单价"));

	// 输出杂志信息
	settextcolor(BLACK);
	settextstyle(25, 0, _T("楷体"));

	//int magid_ret;

	while (true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// 打印信息
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // 检测鼠标事件
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // 判断鼠标位置是否在某一杂志的位置内
						{
							//magid_ret = magazine.magid;
							if (magazine.magtotal == 0)
							{
								MessageBox(NULL, _T("这本杂志没有库存了哦~"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
								continue;
							}

							MessageBox(NULL, _T("如果不想订阅，无需输入内容直接确定即可"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；

							int subnum;

							wchar_t mt[10];
							InputBox(mt, 10, L"请输入订阅数量：");
							if (wcslen(mt) != 0)
							{
								subnum = _wtoi(mt);
								// 减少数量
								decreaseMagazineNumber(magazine, subnum);				// 添加订阅记录


								auto date_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
								char buffer[80];
								struct tm* parts = localtime(&date_time);
								strftime(buffer, sizeof(buffer), "%Y-%m-%d", parts);
								string subdate(buffer);

								Subscribe subscribe;
								subscribe.magid = magazine.magid;
								subscribe.userid = user.userid;
								subscribe.subdate = subdate;
								subscribe.subnumber = subnum;
								subscribe.subtotal = subnum * magazine.magprice;
								SubscribeFun::addSubscribe(subscribe);
								
								MessageBox(NULL, _T("订阅成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；

							}
							break;
						}
						settextcolor(BLACK);
						settextstyle(30, 0, _T("黑体"));
						outtextxy(130, 600, _T("返回"));
						if (msg.x > 130 && msg.x < 175 && msg.y > 600 && msg.y < 630) // 返回
						{
							break;
						}
					}
					break;
				}
			}
		}

	}

	//MessageBox(NULL, _T("修改成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；


}

void SubscribeFun::querysubscribeRecord(User user)
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
	outtextxy(420, 70, _T("订阅记录"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// 绘制标题
	settextcolor(BLACK);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(130, 140, _T("订阅ID   杂志ID   用户ID    订阅日期    订阅数量   小计"));

	// 输出杂志信息
	settextcolor(BLACK);
	settextstyle(25, 0, _T("楷体"));

	//int magid_ret;


	vector<Subscribe> subscribeRecord;

	char sql[1024];
	sprintf(sql, "SELECT * FROM subscribe WHERE userid = %d", user.userid);

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
	}

	MYSQL_RES* res = mysql_store_result(con);

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		Subscribe subscribe;
		subscribe.subid = atoi(row[0]);
		subscribe.magid = atoi(row[1]);
		subscribe.userid = atoi(row[2]);
		subscribe.subdate = row[3];
		subscribe.subnumber = atoi(row[4]);
		subscribe.subtotal = atof(row[5]);
		subscribeRecord.push_back(subscribe);
	}

	if (!subscribeRecord.empty())
	{
		for (int i = 0; i < subscribeRecord.size(); i++)
		{
			//SubscribeFun::display(subscribeRecord);
			Subscribe subscribe = subscribeRecord[i];

			TCHAR subid[5];
			_stprintf(subid, _T("%d"), subscribe.subid);
			outtextxy(170, 190 + i * 30, subid);

			TCHAR magid[5];
			_stprintf(magid, _T("%d"), subscribe.magid);
			outtextxy(310, 190 + i * 30, magid);

			TCHAR userid[5];
			_stprintf(userid, _T("%d"), subscribe.userid);
			outtextxy(440, 190 + i * 30, userid);

			string ssd = subscribe.subdate;
			TCHAR t_ssd[256];
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)ssd.c_str(), -1, t_ssd, 256);
			outtextxy(550, 190 + i * 30, t_ssd);

			TCHAR subnumber[5];
			_stprintf(subnumber, _T("%d"), subscribe.subnumber);
			outtextxy(780, 190 + i * 30, subnumber);

			TCHAR subtotal[10];
			_stprintf(subtotal, _T("%.2f"), subscribe.subtotal);
			outtextxy(890, 190 + i * 30, subtotal);
		}
	}

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