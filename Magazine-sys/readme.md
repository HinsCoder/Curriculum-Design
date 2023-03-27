📖 前言：听说课设月就是放假月（雾），谁想高强度了整整三周，前两周零基础Java+数据库肝课设，现在零基础C++连数据库+GUI，人麻了，浅浅记录一下这次课设叭~

![在这里插入图片描述](https://img-blog.csdnimg.cn/edf472113eeb4fcebdb3cb853569aea1.png)

___


# 🕒 1. 题目要求
对杂志订阅信息（包括：杂志代码、订阅用户名、身份证号、订阅份数、单价、小计）进行管理。功能要求：
（1）	新增			（2）	查找  （3）	更新		（4）	删除

成品效果：
![请添加图片描述](https://img-blog.csdnimg.cn/fd4fa817c7604a21a88a9ebbfa92b372.gif)

# 🕒 2. 环境准备
💡 开发环境：VS2019
💡 数据库：MySQL 5.7.24
💡 数据库管理工具：Navicat for MySQL 11.1
💡 GUI：[🔎 EasyX](https://easyx.cn/)
💡 数据库建模：[🔎 PDManer元数建模](https://gitee.com/robergroup/pdmaner) V4.5.0

MySQL免安装版安装方法如下
[video(video-JQJEPQpz-1679834752311)(type-bilibili)(url-https://player.bilibili.com/player.html?aid=379163696&page=3)(image-https://img-blog.csdnimg.cn/img_convert/8dbdf2c7b8bac0f7e127a099dfda3c70.jpeg)(title-02-MySQL安装)]

当然，使用高版本工具（如MySQL 8+Navicat for MySQL 16）也是可以滴，安装版相比绿色版（免安装版）在配置上会简单一点，但我更倾向于选择绿色版（方便卸载）。
对于数据库建模，还有PowerDesigner可选，但是我嫌弃它界面不友好，上手成本高，因此没有选择。
## 🕘 1.1 PDManer 简介

> PDManer元数建模，是一款多操作系统开源免费的桌面版关系数据库模型建模工具，相对于PowerDesigner，他具备界面简洁美观，操作简单，上手容易等特点。
> 主要功能如下：
**数据表管理**： 数据表，字段，注释，索引等基本功能
**视图管理**： 实现选择多张表多个字段后，组合一个新的视图对象，视图可生成DDL以及相关程序代码，例如Java的DTO等
**ER关系图**： 数据表可绘制ER关系图至画布，也支持概念模型等高阶抽像设计
**数据字典**： 代码映射表管理，例如1表示男，2表示女，并且实现数据字典与数据表字段的关联
**数据类型**： 系统实现了基础数据类型，基础数据类型在不同数据库下表现为不同数据库类型的方言，这是实现多数据库支持的基础，为更贴近业务，引入了PowerDesigner的数据域这一概念，用于统一同一类具有同样业务属性字段的批量设置类型，长度等。基础数据类型以及数据域，用户均可自行添加，自行定义。
**多数据库**： 内置主流常见数据库，如MySQL，PostgreSQL，SQLServer，Oracle等，并且支持用户自行添加新的数据库。
**代码生成**： 内置Java，Mybatis，MyBatisPlus等常规情况下Controller，Service，Mapper的生成，也添加了C#语言支持，可自行扩展对其他语言的支持，如Python等
**版本管理**： 实现数据表的版本管理，可生成增量DDL脚本
**生态对接**： 能够导入PowerDesigner的pdm文件，老版本的PDMan文件，也能导出为word文档，导出相关设置等

![在这里插入图片描述](https://img-blog.csdnimg.cn/de6c2192853f4b1a99ff7bd63a8a762e.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/da59d72d84d6448b95055e0c43b39bbd.png)
这样就可以抽象出数据模型，为后续建立数据库打下基础。
当然这款软件可以直接生成SQL脚本，但个人实测下来，能用但是有点小bug，因此后面还是要用Navicat微调，值得注意的是，这个软件不能设置外键（即脚本没有相关生成），关系图中可以靠连线表示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/f7a638b4617f4e10b9f06944a3589b28.png)

## 🕘 1.2 Navicat 简介
在配置好你的mysql环境之后，将你设置的账号、密码、端口号（3306）在Navicat设置连接上，就可以愉快的使用啦。

![在这里插入图片描述](https://img-blog.csdnimg.cn/a90ca17d9dcb44c1a396137977464d28.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/194e8013b27c45ac9a75c5ac9a9ba85f.png)
在设置外键的时候，删除时和更新时两列有四个值可以选择：CASCADE、NO ACTION、RESTRICT、SET NULL，它们的区别如下：
- CASCADE：父表delete、update的时候，子表会delete、update掉关联记录；
- SET NULL：父表delete、update的时候，子表会将关联记录的外键字段所在列设为null，所以注意在设计子表时外键不能设为not null；
- RESTRICT：如果想要删除父表的记录时，而在子表中有关联该父表的记录，则不允许删除父表中的记录；
- NO ACTION：同 RESTRICT，也是首先先检查外键；

## 🕘 1.3 VS2019
新建C++项目 -> 平台改为X64 -> 右键项目属性
VC++目录 -> 包含目录 -> 编辑 -> mysql安装文件中`include`文件夹路径放进去
库目录 -> 编辑 -> mysql安装文件中`lib`文件夹路径放进去

链接器 -> 常规 -> 附加库目录 -> mysql安装文件中`lib`文件夹路径放进去
输入 -> 附加依赖项 -> 将`libmysql.lib` 写入

![在这里插入图片描述](https://img-blog.csdnimg.cn/222e895e81f64c6385ed5aa30774e2de.png)

在mysql的`lib`文件夹中找到`libmysql.dll`，把它拷贝一份到`C:\Windows\System32`
依照惯例，新建`.h`、`.cpp`、`main.cpp`文件，就可以写代码啦。

## 🕘 1.4 EasyX 简介
> EasyX Graphics Library 是针对 Visual C++ 的免费绘图库，支持 VC6.0 ~ VC2022，简单易用，学习成本极低，应用领域广泛。目前已有许多大学将 EasyX 应用在教学当中。
> 
这里就简单介绍一下相关的函数

### 🕤 1.4.1 窗口
关于坐标：坐标原点在窗口的左上角，X 轴向右为正，Y 轴向下为正，度量单位是像素。
```cpp
initgraph(1080, 720); // 初始化窗口
IMAGE img;		
loadimage(&img, _T("你的图片.jpg"));		// 背景图片
putimage(0, 0, &img);		// 从x=0, y=0开始绘制
setbkcolor(WHITE); // 设置文字背景颜色（白色）
setbkmode(TRANSPARENT); // 设置文字背景透明

//cleardevice(); // 清空窗口
closegraph();		 // 关闭图形模式
```

### 🕤 1.4.2 文字处理

```cpp
 // 绘制欢迎文字
settextcolor(BLACK);			// 文字颜色
settextstyle(55, 0, _T("黑体"));		// 字体选择
outtextxy(220, 60, _T("欢迎使用杂志订阅管理系统"));		// 各参数分别为：指定高度，字符的平均宽度（逻辑单位）。如果为0，则比例自适应。

// 绘制登录选项
settextstyle(30, 0, _T("黑体"));
outtextxy(130, 200, _T("1.已有账号，请登录"));
outtextxy(130, 300, _T("2.没有账号，请注册"));
outtextxy(130, 400, _T("3.注销账号"));
```
> 参数错误，找不到对应的函数，error C2665:“outtextxy*:2个重载中没有一个可以转换所有参数类型，是由于字符集导致的，那么解决方案呢?
> 1. 在字符串前面加上大写的L
> 2. 用TEXT()把字符串包起来，_T(),原理同上
> 3. 不需要添加任何代码，进项目->属性->配置属性->常规->字符集->改为多字节字符集

字符串常见的编码有两种：MBCS 和 Unicode。VC6 新建的项目默认为 MBCS 编码，VC2008 及高版本的 VC 默认为 Unicode 编码。LPCTSTR 可以同时适应两种编码。为了适应两种编码，请使用 TCHAR 字符串及相关函数。

下面是一个从数据库接收数据并打印在窗口的实例
```cpp
Magazine magazine = magazineList[i];		// vector接收

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
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/444e02a28ce14568819065d00b6a91e8.png)



### 🕤 1.4.3 对话框/弹窗
如果需要从对话框输入文字存入变量，就需要下面的转换函数
```cpp
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
```

```cpp
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
```

弹窗提示：
```cpp
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
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/a7628919d5f04d28875875f12f837ddb.png)

更多选项可参考文档
### 🕤 1.4.4 鼠标点击
以上面的登录选项为例

```cpp
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
            {		// 把检测事件想象为一个矩形，这个矩形能刚好覆盖需要点击的文字，上面的x,y就是控制范围
				...
                break;
            }
            else if (msg.x > 130 && msg.x < 380 && msg.y > 300 && msg.y < 320) // 选择2
            {
				...
                break;
            }
            else if (msg.x > 130 && msg.x < 380 && msg.y > 400 && msg.y < 420) // 选择3
            {
                break;
            }
        }
}
```



## 🕘 1.5 辅助工具：cursor


[video(video-vQOjMMZZ-1679842080558)(type-bilibili)(url-https://player.bilibili.com/player.html?aid=993756518)(image-https://img-blog.csdnimg.cn/img_convert/798f7b6fdfc3111737aa3572189b5670.jpeg)(title-又火一个ChatGPT软件，完全免费！但问题也很明显)]

建议逻辑卡壳和某个函数用法不会时可以用用，可用性还是挺高的。





---

> 作者：HinsCoder
> 博客链接：🔎 [作者博客主页](https://blog.csdn.net/HinsCoder)

