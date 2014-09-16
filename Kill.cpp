// Kill.cpp: implementation of the CKill class.
//
//////////////////////////////////////////////////////////////////////

#include "Kill.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKill::CKill()
{
	memset(chessdata,0,sizeof(chessdata));
	baseaddress = 0;
}

CKill::~CKill()
{

}

Point CKill::BFS(byte path[11][19],Point ptstart)
{
	byte boolpath[11][19] = {0};//访问标记 防止转圈
	Point dection[4] = {{0,1},{-1,0},{0,-1},{1,0}};//定义四个方向
    Point pdefau = {-1,-1};//如果不通返回（-1，-1）
	deque<Point> queue;//广度优先搜索所用队列
	queue.push_back(ptstart);//起点入队列
	int n = 0;//防止起点找起点
	int i = 0,j = 0,k = 0;
	/* 以下为图的广度优先搜索*/
	while(!queue.empty())
	{
		Point ptemp = queue.front();
        queue.pop_front();
        boolpath[ptemp.x][ptemp.y] = true;
		if(0 != n && path[ptstart.x][ptstart.y] == path[ptemp.x][ptemp.y])//如果找到了目标点 直接返回
			return ptemp;
		else
		{
			for(i = 0;i<4;i++)//把它的周围4个点放入队列
			{
                if(ptemp.x+dection[i].x>=0 && ptemp.x+dection[i].x<11 &&
                     ptemp.y+dection[i].y >=0 && ptemp.y+dection[i].y<19)//判定是否越界
                {
					Point temp1 = {ptemp.x+dection[i].x,ptemp.y+dection[i].y};
					if((0 == path[temp1.x][temp1.y]  && false == boolpath[temp1.x][temp1.y])||
							  path[temp1.x][temp1.y] == path[ptstart.x][ptstart.y] &&
							  false == boolpath[temp1.x][temp1.y])//如果没有走过  并且可以走
					{
							  queue.push_back(temp1);//入队列
							  boolpath[temp1.x][temp1.y] = true;//流下走过的痕迹
					}
                }
			}               
		}
        n++;
	}
	return pdefau;
}
void CKill::OnKill()
{
     // TODO: 在此添加控件通知处理程序代码

	 const PCHAR gameCaption="QQ游戏 - 连连看角色版";
	 extern int baseadress;
	 LPCVOID pbase=(LPCVOID)this->baseaddress; //棋盘数据基址
	 LPVOID  nbuffer=(LPVOID)&chessdata;   //存放棋盘数据
	 HANDLE processH;
	 DWORD byread;
	 DWORD processid;
	 HWND gameh=::FindWindow(NULL,gameCaption);
	 int num = 5;
	 while(num--)
	 {
		 //获取窗口进程ID
		 ::GetWindowThreadProcessId(gameh,&processid);
		 //打开指定进程
		 processH=::OpenProcess(PROCESS_ALL_ACCESS,false,processid);
		 //读指定进程 内存数据 
		 if(!::ReadProcessMemory(processH,pbase,nbuffer,11*19,&byread))
		 {
			 printf("不能读取内存数据\n");
			 return ;
		 }
    

		  int i = 0,j = 0,k = 0;
		  int x = 22,y = 187;//固定数据不要改变  否则无法实现点击
		  int  lparam = 0;//表示指定格	

		  //对于每一个棋子广度优先搜索
		  for(i = 0;i<11;i++)
		  {
			  for(j = 0;j<19;j++)
			  {
					if(0 != chessdata[i][j])
					{
						 Point ptstart = {i,j},ptend = {0,0};//把要找的棋子的起点传给搜索函数 函数可以到达的那个点
						 ptend = this->BFS(chessdata,ptstart);//接受终点坐标
						 if(ptend.x != -1 && ptend.y != -1)//如果找到了
						 {                              
							  /*以下六行位发送点击两个点的消息 不必深究 用就可以*/
							  //表示指定的格 固定公式 不要改动
							  lparam = ((y+(35*ptstart.x))<<16)+x+31*(ptstart.y);
							  ::SendMessage(gameh,WM_LBUTTONDOWN,0,lparam);//
							  ::SendMessage(gameh,WM_LBUTTONUP,0,lparam);  // 

							  lparam = ((y+(35*ptend.x))<<16)+x+31*(ptend.y);
							  ::SendMessage(gameh,WM_LBUTTONDOWN,0,lparam);//
							  ::SendMessage(gameh,WM_LBUTTONUP,0,lparam);  // 
							  //消去之后就成了通道  所以两个点数据更新为0
							  chessdata[ptend.x][ptend.y] = chessdata[ptstart.x][ptstart.y] = 0;
						 }
					}
			  }			  
		  }
	 }
}