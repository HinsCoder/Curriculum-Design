#include "fun.h"

// 对User的操作窗口
User loginConsole()
{
    User user;
    initgraph(1080, 720); // 初始化窗口
    IMAGE img;
    loadimage(&img, _T("悦读岛.jpg"));
    putimage(0, 0, &img);
    setbkcolor(WHITE); // 设置背景颜色
    setbkmode(TRANSPARENT); // 设置文字背景透明

    //cleardevice(); // 清空窗口

    // 绘制欢迎文字
    settextcolor(BLACK);
    settextstyle(55, 0, _T("黑体"));
    outtextxy(220, 60, _T("欢迎使用杂志订阅管理系统"));

    // 绘制登录选项
    settextstyle(30, 0, _T("黑体"));
    outtextxy(130, 200, _T("1.已有账号，请登录"));
    outtextxy(130, 300, _T("2.没有账号，请注册"));
    outtextxy(130, 400, _T("3.注销账号"));

    // 获取用户输入
    while (true)
    {
        string username;
        string password;
        string useridcard;
        if (MouseHit()) // 检测鼠标事件
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
            {
                if (msg.x > 130 && msg.x < 380 && msg.y > 200 && msg.y < 220) // 选择1
                {
                    wchar_t un[20];
                    InputBox(un, 20, L"请输入账号：");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"请输入密码：");
                    Wchar_tToString(password, pw);

                    user = UserFun::GetInstance()->queryUser(username, password);

                    //break;
                }
                else if (msg.x > 130 && msg.x < 380 && msg.y > 300 && msg.y < 320) // 选择2
                {

                    wchar_t un[20];
                    InputBox(un, 20, L"请输入账号：");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"请输入密码：");
                    Wchar_tToString(password, pw);

                    wchar_t ic[20];
                    InputBox(ic, 20, L"请输入身份证号：");
                    Wchar_tToString(useridcard, ic);

                    user = UserFun::GetInstance()->registerUser(username, password, useridcard);

                    break;
                }
                else if (msg.x > 130 && msg.x < 380 && msg.y > 400 && msg.y < 420) // 选择3
                {
                    wchar_t un[20];
                    InputBox(un, 20, L"请输入账号：");
                    Wchar_tToString(username, un);

                    wchar_t pw[20];
                    InputBox(pw, 20, L"请输入密码：");
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
                    MessageBox(NULL, _T("登录成功！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
                    break;
                }
                else {
                    int msg = MessageBox(NULL, _T("账号或密码有误！"), _T("错误"), MB_RETRYCANCEL);   // MB_RETRYCANCEL：有“重试”和“取消”两个按钮；
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
        initgraph(1080, 720); // 初始化窗口
        IMAGE img;
        loadimage(&img, _T("阅读空间.jpg"));
        putimage(0, 0, &img);
        setbkcolor(WHITE); // 设置背景颜色
        setbkmode(TRANSPARENT); // 设置文字背景透明
        //cleardevice(); // 清空窗口

        // 绘制欢迎文字
        settextcolor(BLACK);
        settextstyle(55, 0, _T("黑体"));
        outtextxy(330, 60, _T("杂志订阅管理系统"));

        // 绘制功能选项
        settextstyle(30, 0, _T("黑体"));
        outtextxy(130, 150, _T("1.查询杂志"));
        outtextxy(130, 220, _T("2.订阅杂志"));
        outtextxy(130, 280, _T("3.查询小计"));
        outtextxy(130, 350, _T("4.添加杂志"));
        outtextxy(130, 420, _T("5.修改杂志"));
        outtextxy(130, 490, _T("6.删除杂志"));
        outtextxy(130, 560, _T("0.退出系统"));

        // 获取用户输入
        int input = 0;
        while (true)
        {
            if (MouseHit()) // 检测鼠标事件
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下
                {
                    if (msg.x > 130 && msg.x < 270 && msg.y > 150 && msg.y < 180) // 选择1
                    {
                        MagazineFun::GetInstance()->queryMagazinePage();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 220 && msg.y < 250) // 选择2
                    {
                        SubscribeFun::GetInstance()->subscribeMagazine(user);

                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 280 && msg.y < 310) // 选择3
                    {
                        SubscribeFun::GetInstance()->querysubscribeRecord(user);

                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 350 && msg.y < 380) // 选择4
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("您不是管理员，无法进行此操作！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
                            continue;
                        }
                        MagazineFun::GetInstance()->addMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 420 && msg.y < 450) // 选择5
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("您不是管理员，无法进行此操作！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
                            continue;
                        }
                        MagazineFun::GetInstance()->modifyMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 490 && msg.y < 520) // 选择6
                    {
                        if (user.userpower != 1)
                        {
                            MessageBox(NULL, _T("您不是管理员，无法进行此操作！"), _T("提示"), MB_OK);         // MB_OK：只有一个“确定”按钮；
                            continue;
                        }
                        MagazineFun::GetInstance()->deleteMagazine();
                        break;
                    }
                    else if (msg.x > 130 && msg.x < 270 && msg.y > 560 && msg.y < 590) // 选择0
                    {
                        exit(0);
                    }
                }
            }
        }

    }
    closegraph();
}
