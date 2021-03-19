#include<stdio.h>
#include<graphics.h>  
#include<conio.h> 
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
int a1[9] = { 0 };
int a2[3][3] = { 0 };
IMAGE img, blank,bg;
struct point
{
	int i;
	int j;
}thispoint;
/*
查找blank图片位置
*/
struct point search(int a2[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a2[i][j] == 8)
			{
				thispoint.i = i;
				thispoint.j = j;
				return thispoint;
			}
		}
	}
}
/*
菜单栏
*/
void meau()
{
	initgraph(600, 600);
	setbkcolor(RGB(150, 50, 50));
	cleardevice();//刷新页面
	setfillcolor(RED);
	fillrectangle(200, 120, 400, 200);
	fillrectangle(200, 300, 400, 380);

	setbkmode(TRANSPARENT);
	settextstyle(35,22,"");
	outtextxy(200 + 10,120 + 23,"开始游戏");
	outtextxy(200 + 10, 300 + 23, "退出游戏");
	settextstyle(50, 32, "");
	settextcolor(RGB(0,0,0));
	outtextxy(140 + 10, 450 + 23, "晗哥制作！！");
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x>=200&&m.x<=400&&m.y>=120&&m.y<=200)
		{
			setlinecolor(BLACKONWHITE);
			rectangle(200 - 5, 120-5, 400+5, 200+5);
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				break;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 380)
		{
			setlinecolor(BLACKONWHITE);
			rectangle(200 - 5, 300 - 5, 400 + 5, 380+ 5);
			if (m.uMsg==WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		else
		{
			setlinecolor(YELLOW);
			rectangle(200 - 5, 300 - 5, 400 + 5, 380 + 5);
			rectangle(200 - 5, 120 - 5, 400 + 5, 200 + 5);
		}
	}
	closegraph();

}
/*
加载图片
*/
void loadingsource()
{
	/*
	随机打乱拼图的顺序
	*/
	int i=0, n, a[9],count=0;
	srand(time(0));
	while (1)
	{
		n = rand() % 9 ; //从0到8随机
		if (a[n] != -1)
		{
			a1[i] = n;
			a[n] = -1; //用数组做标记
			if ((++i) == 9)break; //取到几个数就停止
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a2[i][j] = a1[count];
			count++;
		}
	}
	loadimage(&img, "123456.jpg", 600, 600);
	loadimage(&blank, "123.png", 200, 200);
	//a2[1][2] = 2;
	//a2[0][2] = 5;
	//a2[1][1] = 1;
	//a2[0][1] = 4;
	//a2[2][2] = 3;
	//a2[1][0] = 8;
}
/*
画图片
*/
void drawmap()
{
	for (int i= 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int x = j * 200;
			int y = i * 200;
			switch (a2[i][j])
			{
			case 0:
			case 1:
			case 2:
				putimage(x, y,200,200, &img, a2[i][j] * 200, 0);
				break;
			case 3:
			case 4:
			case 5:
				putimage(x, y, 200, 200, &img, (a2[i][j]-3) * 200, 200);
				break;
			case 6:
			case 7:
				putimage(x, y, 200, 200, &img, (a2[i][j]-6) * 200, 400);
				break;
			case 8:
				putimage(x, y, 200, 200, &blank, 0,0);
				break;
			default:
				printf("程序数据出错，请勿擅自更改程序内容");
				break;
			}
		}
	}
}
/*
游戏程序
*/
void playgame()
{
	MOUSEMSG m;
	while (1)
	{
		drawmap();
		int i, j = 0;
		int mousei, mousej;
		search(a2);
		i = thispoint.i;
		j = thispoint.j;
		m = GetMouseMsg();
		if (m.uMsg== WM_LBUTTONDOWN)
		{
			mousei=m.y / 200;
			mousej= m.x / 200;
			/*if (mousei == i + 1 && mousej == j|| mousei == i -1 && mousej == j || mousei == i && mousej == j+1 || mousei == i && mousej == j-1)*/
			a2[i][j] = a2[mousei][mousej];
			a2[mousei][mousej] = 8;
			if (a2[0][0] == 0 && a2[0][1] == 1 && a2[0][2] ==2 && a2[1][0] == 3 && a2[1][1] == 4 && a2[1][2] == 5&& a2[2][0] == 6 && a2[2][1] == 7 && a2[2][2] == 8)
			{
				drawmap();
				MessageBox(NULL, TEXT("点赞投币评论关注这个可爱的up主就可能在梦里得到我哟！"), TEXT("人家都被你看到了!"), MB_OK | MB_SETFOREGROUND);
				break;
			}

		}
	}
}
/*
主界面
*/
void mainmeau()
{
	initgraph(600, 600);
	setbkcolor(WHITE);
	loadingsource();
	playgame();
	closegraph();
}
/*
主语句入口
*/
int main()
{
	while (true)
	{
	PlaySound("王小姐.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	meau();
	mainmeau();
    }
	return 0;
}
