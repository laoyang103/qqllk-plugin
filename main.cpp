#include "Kill.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("**************QQ连连看秒杀外挂****************\n");
	printf("*************输入任意键开始秒杀***************\n");
	printf("******************输入n结束*******************\n");
	char n;
	CKill kill;
	int os = 0;
	printf("******首先请输入操作系统******\n\n0.Windows XP\n1.Windows 7\n");
	
	scanf("%d",&os);
	printf("*************输入任意键开始秒杀***************\n");
	if(0 == os)
		kill.baseaddress = 0x00129F78;
	else
		kill.baseaddress = 0x00129F78;
	
	while(scanf("%c",&n))
	{
		getchar();
		if('n' == n)
		{
			printf("谢谢使用！\n");
			system("pause");
			break;
		}
		else
		{
			kill.OnKill();
		}
	}
	return 0;
}