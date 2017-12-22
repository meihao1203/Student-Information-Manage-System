#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"sims.h"
int main()
{
	char str[1024]="";
	char str1[1024]="";
	char str2[1024]="";
	FILE *fp = fopen("configure.txt","r");

	USER_ACCOUNT *user_list = NULL;
	STUDENT *stu_list = NULL;
	int button;
	USER_ACCOUNT user;
	memset(&user,0,sizeof(USER_ACCOUNT));

	fgets(str,sizeof(str)-1,fp);
	strncpy(str1,str,strlen(str)-1);  //去掉结尾换行
	memset(str,0,sizeof(str));
	fgets(str,sizeof(str)-1,fp);
	if(str[strlen(str)]=='\n')    //配置文件只读两行，判断第二行有没有换行在末尾
	{
		strncpy(str2,str,strlen(str)-1);
	}
	else
	{
		strncpy(str2,str,strlen(str));
	}
	system_init(&user_list,&stu_list,str1,str2);
	while(1)
	{
		system("cls");
		interface_init();
		printf("select a number: ");
		button = getchar()-'0';
		if(2 == button)
		{
			system_exit();
			return 0;
		}
		else if(ADMIN == button || GUEST == button)
			user.users_limit = button;
		else
		{
			fflush(stdin);
			printf("Input Error!\nPress any key to select again");
			_getch();
			continue;
		}
		system("cls");
		printf("Username:");
		scanf("%s",&user.user_name);
		printf("Password:");
		fflush(stdin);
        GetPassword(user.user_password);
		if(check_user_account(user_list,user))
		{
			if( user.users_limit == ADMIN )
			{
				admin_account(&user_list,&stu_list,str1,str2);
			}
			else if( user.users_limit == GUEST )
			{
				guest_account(stu_list);
			}
			break;
		}
		else
		{
			printf("\nNot Found!\n");
			fflush(stdin);
			printf("Press y to login again, or any key else to exit:");
			if (_getch() != 'y')
				break;
		}
		
	}
	return 0;
}