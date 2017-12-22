#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
#include<unistd.h>
#include"sims.h"
int main()
{
	char str[1024]="";
	char str1[1024]="";
	char str2[1024]="";
	FILE *fp = fopen("../conf/configure.txt","r");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	USER_ACCOUNT *user_list = NULL;
	STUDENT *stu_list = NULL;
	int button;
	USER_ACCOUNT user;
	memset(&user,0,sizeof(USER_ACCOUNT));

	fgets(str,sizeof(str)-1,fp);
	sscanf(str,"%s",str1);
	memset(str,0,sizeof(str));
	fgets(str,sizeof(str)-1,fp);
	sscanf(str,"%s",str2);
	system_init(&user_list,&stu_list,str1,str2);
	while(1)
	{
		system("clear");
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
			getchar();
			continue;
		}
		system("clear");
		printf("User name:");
		scanf("%s",&user.user_name);
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
			printf("Press y to login again, or any key else to exit:\n");
			if (getchar() != 'y')
				break;
		}
	}
	return 0;
}
