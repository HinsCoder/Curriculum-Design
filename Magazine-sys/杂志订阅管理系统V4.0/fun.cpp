#include"fun.h"

// ��ѯ��־
void MagazineFun::queryMagazinePage()
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
	outtextxy(420, 60, _T("��ѯ��־"));
	vector<Magazine> magazineList;
	while (true)
	{
		// ���ƹ���ѡ��
		settextstyle(30, 0, _T("����"));
		outtextxy(130, 200, _T("0.�����ϼ��˵�"));
		outtextxy(130, 300, _T("1.��ѯ������־"));
		outtextxy(130, 400, _T("2.����־����ѯ"));

		if (MouseHit()) // �������¼�
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) // ����������
			{
				if (msg.x > 130 && msg.x < 380 && msg.y > 200 && msg.y < 220) // ѡ��0
				{
					break;
				}
				else if (msg.x > 130 && msg.x < 380 && msg.y > 300 && msg.y < 320) // ѡ��1
				{
					magazineList = MagazineFun::GetInstance()->queryAllMagazine();
					MagazineFun::display(magazineList);
					break;
				}
				else if (msg.x > 130 && msg.x < 380 && msg.y > 400 && msg.y < 420) // ѡ��2
				{
					string magname;

					wchar_t mn[20];
					InputBox(mn, 20, L"��������־����");
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

// ��ѯȫ����־
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
		magazine.magid = atoi(row[0]);		// ���ַ���ת��Ϊint���ͱ���
		magazine.magname = row[1];
		magazine.magtotal = atoi(row[2]);
		magazine.magprice = atof(row[3]);	// ���ַ���ת��Ϊdouble���ͱ���

		magazineList.push_back(magazine);

	}
	return magazineList;
}

// ����־����ID��ѯ��־
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
	magazine.magid = atoi(row[0]);		// ���ַ���ת��Ϊint���ͱ���
	magazine.magname = row[1];
	magazine.magtotal = atoi(row[2]);
	magazine.magprice = atof(row[3]);	// ���ַ���ת��Ϊdouble���ͱ���

	magazineList.push_back(magazine);

	return magazineList;
}



void MagazineFun::addMagazine()
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
	outtextxy(420, 70, _T("�����־"));
	vector<Magazine> magazineList;

	string magname;
	int magtotal;
	double magprice;

	wchar_t mn[20];
	InputBox(mn, 20, L"��������־����");
	Wchar_tToString(magname, mn);

	wchar_t mt[10];
	InputBox(mt, 10, L"��������־������");
	magtotal = _wtoi(mt);

	wchar_t mp[10];
	InputBox(mp, 10, L"��������־���ۣ�");
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

	MessageBox(NULL, _T("��ӳɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��

}

void MagazineFun::modifyMagazine()
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
	outtextxy(420, 70, _T("�޸���־"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// ���Ʊ���
	settextcolor(BLACK);
	settextstyle(30, 0, _T("����"));
	outtextxy(130, 140, _T("��־ID        ��־����        ��־����        ��־����"));

	// �����־��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));

	//int magid_ret;

	while(true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// ��ӡ��Ϣ
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // �������¼�
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // ����������
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // �ж����λ���Ƿ���ĳһ��־��λ����
						{
							//magid_ret = magazine.magid;
							MessageBox(NULL, _T("��������޸�ĳ�������������ֱ��ȷ������"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��

							string magname;
							//int magtotal;
							//double magprice;

							wchar_t mn[20];
							InputBox(mn, 20, L"�������µ���־����");
							if (wcslen(mn) != 0)
							{
								Wchar_tToString(magname, mn);
								magazine.magname = magname;
							}
							

							wchar_t mt[10];
							InputBox(mt, 10, L"�������µ���־������");
							if (wcslen(mt) != 0)
							{
								magazine.magtotal = _wtoi(mt);
							}
							

							wchar_t mp[10];
							InputBox(mp, 10, L"�������µ���־���ۣ�");
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

	MessageBox(NULL, _T("�޸ĳɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
}


void MagazineFun::deleteMagazine()
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
	outtextxy(420, 70, _T("ɾ����־"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// ���Ʊ���
	settextcolor(BLACK);
	settextstyle(30, 0, _T("����"));
	outtextxy(130, 140, _T("��־ID        ��־����        ��־����        ��־����"));

	// �����־��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));

	//int magid_ret;

	while (true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// ��ӡ��Ϣ
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // �������¼�
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // ����������
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // �ж����λ���Ƿ���ĳһ��־��λ����
						{
							int ret = MessageBox(NULL, _T("�Ƿ�ȷ��ɾ����"), _T("��ʾ"), MB_OKCANCEL);		// MB_OKCANCEL����ȷ����ȡ��������ť
							if (ret == IDOK)
							{
								char sql[1024];
								sprintf(sql, "DELETE FROM magazine WHERE magid = %d", magazine.magid);

								if (mysql_query(con, sql))
								{
									fprintf(stderr, "Failed to delete data : Error:%s\n", mysql_error(con));
								}
								MessageBox(NULL, _T("ɾ���ɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
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
		MessageBox(NULL, _T("���˺��Ѵ��ڣ���ֱ�ӵ�¼"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
		// Sleep(2000);    // �ȴ�2����
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

		MessageBox(NULL, _T("ע��ɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��

	}
	return user;
}


int UserFun::loginoutUser(string username, string password)
{
	//User user;
	if (CheckisExistUser(username, password))
	{
		int ret = MessageBox(NULL, _T("ȷ��ע����"), _T("��ʾ"), MB_OKCANCEL);		// MB_OKCANCEL����ȷ����ȡ��������ť
		if (ret == IDOK)
		{
			char sql[1024];
			sprintf(sql, "DELETE FROM user WHERE username = '%s' AND userpassword = '%s'", username.c_str(), password.c_str());

			if (mysql_query(con, sql))
			{
				fprintf(stderr, "Failed to delete data : Error:%s\n", mysql_error(con));
			}

			MessageBox(NULL, _T("ע���ɹ���"), _T("��ʾ"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("ȡ��ע����"), _T("��ʾ"), MB_OK);
			return 1;
		}

	}
	else
	{
		MessageBox(NULL, _T("�˺Ż���������"), _T("����"), MB_OK);
		return 2;
	}
}

Magazine SubscribeFun::queryAvailableMagazine(string magname)
{
	char sql[1024];

	sprintf(sql, "SELECT * FROM magazine WHERE magname like '%%%s%%'", magname.c_str());		// �ƺ���bug

	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Failed to select data : Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);

	Magazine magazine;
	magazine.magid = atoi(row[0]);		// ���ַ���ת��Ϊint���ͱ���
	magazine.magname = row[1];
	magazine.magtotal = atoi(row[2]);
	magazine.magprice = atof(row[3]);	// ���ַ���ת��Ϊdouble���ͱ���

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

	//cout << "������Ϣ�ѳɹ���ӵ����ݿ⣡" << endl;

}

void SubscribeFun::subscribeMagazine(User user) {

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
	outtextxy(420, 70, _T("������־"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// ���Ʊ���
	settextcolor(BLACK);
	settextstyle(30, 0, _T("����"));
	outtextxy(130, 140, _T("��־ID        ��־����        ��־����        ��־����"));

	// �����־��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));

	//int magid_ret;

	while (true)
	{
		if (!magazineList.empty())
		{
			for (int i = 0; i < magazineList.size(); i++)		// ��ӡ��Ϣ
			{
				Magazine magazine = magazineList[i];

				TCHAR magid[5];
				_stprintf(magid, _T("%d"), magazine.magid);
				outtextxy(170, 190 + i * 30, magid);

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

			if (MouseHit()) // �������¼�
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) // ����������
				{
					for (int i = 0; i < magazineList.size(); i++)
					{
						Magazine magazine = magazineList[i];

						if (msg.x > 170 && msg.x < 900 && msg.y > 190 + i * 30 && msg.y < 215 + i * 30) // �ж����λ���Ƿ���ĳһ��־��λ����
						{
							//magid_ret = magazine.magid;
							if (magazine.magtotal == 0)
							{
								MessageBox(NULL, _T("�Ȿ��־û�п����Ŷ~"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
								continue;
							}

							MessageBox(NULL, _T("������붩�ģ�������������ֱ��ȷ������"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��

							int subnum;

							wchar_t mt[10];
							InputBox(mt, 10, L"�����붩��������");
							if (wcslen(mt) != 0)
							{
								subnum = _wtoi(mt);
								// ��������
								decreaseMagazineNumber(magazine, subnum);				// ��Ӷ��ļ�¼


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
								
								MessageBox(NULL, _T("���ĳɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��

							}
							break;
						}
						settextcolor(BLACK);
						settextstyle(30, 0, _T("����"));
						outtextxy(130, 600, _T("����"));
						if (msg.x > 130 && msg.x < 175 && msg.y > 600 && msg.y < 630) // ����
						{
							break;
						}
					}
					break;
				}
			}
		}

	}

	//MessageBox(NULL, _T("�޸ĳɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��


}

void SubscribeFun::querysubscribeRecord(User user)
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
	outtextxy(420, 70, _T("���ļ�¼"));

	vector<Magazine> magazineList = MagazineFun::GetInstance()->queryAllMagazine();
	// MagazineFun::display(magazineList);

	// ���Ʊ���
	settextcolor(BLACK);
	settextstyle(30, 0, _T("����"));
	outtextxy(130, 140, _T("����ID   ��־ID   �û�ID    ��������    ��������   С��"));

	// �����־��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));

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