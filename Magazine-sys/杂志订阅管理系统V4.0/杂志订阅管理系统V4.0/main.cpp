#include "fun.h"

// ��User�Ĳ�������
User loginConsole()
{
    User user;
    initgraph(1080, 720); // ��ʼ������
    IMAGE img;
    loadimage(&img, _T("�ö���.jpg"));
    putimage(0, 0, &img);
    setbkcolor(WHITE); // ���ñ�����ɫ
    setbkmode(TRANSPARENT); // �������ֱ���͸��

    //cleardevice(); // ��մ���

    // ���ƻ�ӭ����
    settextcolor(BLACK);
    settextstyle(55, 0, _T("����"));
    outtextxy(220, 60, _T("��ӭʹ����־���Ĺ���ϵͳ"));

    // ���Ƶ�¼ѡ��
    settextstyle(30, 0, _T("����"));
    outtextxy(130, 200, _T("1.�����˺ţ����¼"));
    outtextxy(130, 300, _T("2.û���˺ţ���ע��"));
    outtextxy(130, 400, _T("3.ע���˺�"));

    // ��ȡ�û�����
    while (true)
    {
        string username;
        string password;
        string useridcard;
        if (MouseHit()) // �������¼�
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) // ����������
            {
                if (msg.x > 130 && msg.x < 380 && msg.y > 200 && msg.y < 220) // ѡ��1
                {
                    wchar_t un[20];
                    InputBox(un, 20, L"�������˺ţ�");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"���������룺");
                    Wchar_tToString(password, pw);

                    user = UserFun::GetInstance()->queryUser(username, password);

                    //break;
                }
                else if (msg.x > 130 && msg.x < 380 && msg.y > 300 && msg.y < 320) // ѡ��2
                {

                    wchar_t un[20];
                    InputBox(un, 20, L"�������˺ţ�");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"���������룺");
                    Wchar_tToString(password, pw);

                    wchar_t ic[20];
                    InputBox(ic, 20, L"���������֤�ţ�");
                    Wchar_tToString(useridcard, ic);

                    user = UserFun::GetInstance()->registerUser(username, password, useridcard);

                    break;
                }
                else if (msg.x > 130 && msg.x < 380 && msg.y > 400 && msg.y < 420) // ѡ��3
                {
                    wchar_t un[20];
                    InputBox(un, 20, L"�������˺ţ�");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"���������룺");
                    Wchar_tToString(password, pw);

                    int ret = UserFun::GetInstance()->loginoutUser(username, password);
                    if (ret)
                    {
                        continue;
                    }
                    else {
                        exit(0);
                    }
                    //break;
                }

                if (user.userid != 0)
                {
                    MessageBox(NULL, _T("��¼�ɹ���"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
                    break;
                }
                else {
                    int msg = MessageBox(NULL, _T("�˺Ż���������"), _T("����"), MB_RETRYCANCEL);   // MB_RETRYCANCEL���С����ԡ��͡�ȡ����������ť��
                    if (msg == IDRETRY)
                    {
                        continue;
                    }
                    else if (msg == IDCANCEL)
                    {
                        exit(0);
                    }
                }
            }
		}
	}
    return user;
}


int main(void)
{
    User user = loginConsole();

    while (true)
    {
        initgraph(1080, 720); // ��ʼ������
        IMAGE img;
        loadimage(&img, _T("�Ķ��ռ�.jpg"));
        putimage(0, 0, &img);
        setbkcolor(WHITE); // ���ñ�����ɫ
        setbkmode(TRANSPARENT); // �������ֱ���͸��
        //cleardevice(); // ��մ���

        // ���ƻ�ӭ����
        settextcolor(BLACK);
        settextstyle(55, 0, _T("����"));
        outtextxy(330, 60, _T("��־���Ĺ���ϵͳ"));

        // ���ƹ���ѡ��
        settextstyle(30, 0, _T("����"));
        outtextxy(130, 150, _T("1.��ѯ��־"));
        outtextxy(130, 220, _T("2.������־"));
        outtextxy(130, 280, _T("3.��ѯС��"));
        outtextxy(130, 350, _T("4.�����־"));
        outtextxy(130, 420, _T("5.�޸���־"));
        outtextxy(130, 490, _T("6.ɾ����־"));
        outtextxy(130, 560, _T("0.�˳�ϵͳ"));

        // ��ȡ�û�����
        int input = 0;
        while (true)
        {
            if (MouseHit()) // �������¼�
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) // ����������
                {
                    if (msg.x > 130 && msg.x < 270 && msg.y > 150 && msg.y < 180) // ѡ��1
                    {
                        MagazineFun::GetInstance()->queryMagazinePage();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 220 && msg.y < 250) // ѡ��2
                    {
                        SubscribeFun::GetInstance()->subscribeMagazine(user);

                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 280 && msg.y < 310) // ѡ��3
                    {
                        SubscribeFun::GetInstance()->querysubscribeRecord(user);

                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 350 && msg.y < 380) // ѡ��4
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("�����ǹ���Ա���޷����д˲�����"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
                            continue;
                        }
                        MagazineFun::GetInstance()->addMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 420 && msg.y < 450) // ѡ��5
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("�����ǹ���Ա���޷����д˲�����"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
                            continue;
                        }
                        MagazineFun::GetInstance()->modifyMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 490 && msg.y < 520) // ѡ��6
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("�����ǹ���Ա���޷����д˲�����"), _T("��ʾ"), MB_OK);         // MB_OK��ֻ��һ����ȷ������ť��
                            continue;
                        }
                        MagazineFun::GetInstance()->deleteMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 560 && msg.y < 590) // ѡ��0
                    {
                        exit(0);
                    }
                }
            }
        }

    }
    closegraph();
}
