#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"sims.h"
void system_init(pUSER_ACCOUNT *user_list,pSTUDENT *stu_list,char *str1,char *str2)
{
	FILE *fp1 = fopen(str1,"r+");
	FILE *fp2 = fopen(str2,"r+");
	//fseek(fp1,0,SEEK_SET);
	//fseek(fp2,0,SEEK_SET);
	USER_ACCOUNT *user_head = (pUSER_ACCOUNT)calloc(1,sizeof(USER_ACCOUNT));
	STUDENT *stu_head = (pSTUDENT)calloc(1,sizeof(STUDENT));
	USER_ACCOUNT *puser = NULL,*user_tail=user_head,tmp_user;
	STUDENT *pstu = NULL,*stu_tail=stu_head,*pre=NULL,*pcur=NULL,tmp_stu;
	STUDENT *pvisit = NULL;
	int i;
	*user_list = user_head;
	*stu_list = stu_head;
	memset(&tmp_user,0,sizeof(USER_ACCOUNT));
	memset(&tmp_stu,0,sizeof(STUDENT));
	if(fp1 != NULL)
	{
		while( ( fscanf(fp1,"%s%s%d",&tmp_user.user_name,&tmp_user.user_password,&tmp_user.users_limit)) != EOF )
		{
			puser = (pUSER_ACCOUNT)calloc(1,sizeof(USER_ACCOUNT));
			strcpy(puser->user_name,tmp_user.user_name);
			strcpy(puser->user_password,tmp_user.user_password);
			puser->users_limit = tmp_user.users_limit;
			if(NULL == user_head->next)
			{
				puser->next = user_head->next;
				user_head->next = puser;
				user_tail=puser;
			}
			else
			{
				user_tail->next = puser;
				user_tail=puser;
			}
		}
		fclose(fp1);
	}
	else
	{
		perror("fopen:user_account.txt");
	}
	if(fp2 != NULL)
	{
		while( ( fscanf(fp2,"%d%s",&tmp_stu.stu_id,&tmp_stu.stu_name) ) != EOF )
		{
			pstu = (pSTUDENT)calloc(1,sizeof(STUDENT));
			pstu->stu_id = tmp_stu.stu_id;
			strcpy(pstu->stu_name,tmp_stu.stu_name);		
			for(i=0;i<COURSE_NUM;i++)
			{
				fscanf(fp2,"%d%lf",&pstu->course[i].course_id,&pstu->course[i].course_score);
			}
			if(NULL == stu_head->next)
			{
				pstu->next=stu_head->next;
				stu_head->next=pstu;
				stu_tail=pstu;
			}
			else
			{
				pre = stu_head;
				pcur=stu_head->next;
				while( NULL != pcur )
				{
					if(pcur->stu_id>pstu->stu_id)
					{
						pstu->next=pcur;
						pre->next=pstu;
						break;
					}
					else 
					{
						pcur=pcur->next;
						pre=pre->next;
					}
				}
				if(NULL == pcur)
				{
					stu_tail->next=pstu;
					stu_tail=pstu;
				}
			}
		}
		fclose(fp2);
	}
	else
		perror("fopen:student.txt");
}

void interface_init()
{
	printf("welcome to SIMS");
	printf("\nPlease select your account level:\n\n");
	printf("[0] You are a teacher\n");
	printf("[1] You are a student\n");
	printf("[2] Exit\n\n");
}

void GetPassword(char *password)
{
	int index = 0;
	char ch;
	while( (ch=_getch()) != '\r' )
	{
		if(ch!='\b')
		{
			printf("*");
			password[index++]=ch;
		}
		else
		{
			printf("\b \b");
			index--;
		}
		password[index]='\0';
	}
}

int check_user_account(pUSER_ACCOUNT user_list,USER_ACCOUNT user)
{
	while(user_list->next != NULL)
	{
		if(!strcmp(user_list->next->user_name,user.user_name)&&!strcmp(user_list->next->user_password,user.user_password))
		{
			return 1;
		}
		user_list->next = user_list->next->next;
	}
	return 0;
}

void admin_account(pUSER_ACCOUNT *user_list,pSTUDENT *stu_list,char *str1,char *str2)
{
	char button;
	while(1)
	{
		system("cls");
		admin_interface_init();
		printf("select a number:");
		fflush(stdin);
		scanf("%c", &button);
		switch(button)
		{
		case '1':search_student_information(*stu_list, ADMIN);   break;
		case '2':add_student_information(stu_list,str2); break;
		case '3':update_student_information(stu_list,str2);break;
		case '4':delete_student_information(stu_list,str2);break;
		case '5':search_user_account(*user_list);break;
		case '6':add_user_account(user_list,str1);break;
		case '7':update_user_account(user_list,str1);break;
		case '8':delete_user_account(user_list,str1);break;
		case '9':system_exit();break;
		default:
			fflush(stdin);
			printf("Input Error!\nPress any key to select again");
			_getch();
		}
	}
}

void guest_account(pSTUDENT stu_list)
{
	char button;
	while(1)
	{
		system("cls");
		guest_interface_init();
		printf("select a number:");
		fflush(stdin);
		scanf("%c",&button);
		switch(button)
		{
		case '1':search_student_information(stu_list,GUEST);break;
		case '2':system_exit();break;
		default:
			fflush(stdin);
			printf("Input Error!\nPress any key to select again");
			_getch();

		}
	}
}

void admin_interface_init()
{
	printf("[1] %-8s student information\n", "search");
	printf("[2] %-8s student information\n", "add");
	printf("[3] %-8s student information\n", "update");
	printf("[4] %-8s student information\n", "delete");
	printf("[5] %-8s user acount\n", "search");
	printf("[6] %-8s user acount\n", "add");
	printf("[7] %-8s user acount\n", "update");
	printf("[8] %-8s user acount\n", "delete");
	printf("[9] exit\n\n");
}

void guest_interface_init()
{
	printf("[1] search student information\n");
	printf("[2] exit\n");
}

void search_student_information(pSTUDENT stu_list, int limit)
{
	char button;
	while(1)
	{
		search_init(limit);
		printf("select a number:");
		fflush(stdin);
		scanf("%c", &button);
		switch(button)
		{
		case '1': search_by_id(stu_list);break;
		case '2': search_by_name(stu_list);break;
		case '3': return; break;
		case '0': 
			if(limit == ADMIN)
			{
				search_all(stu_list);
			}
			break;
		default:
			fflush(stdin);
			printf("Input Error!\nPress any key to select again");
			_getch();
		}
	}
}

void search_init(int limit)
{
	system("cls");
	if(limit == ADMIN)
	{
		printf("[0] search all\n");
	}
	printf("[1] search by ID\n");
	printf("[2] search by name\n");
	printf("[3] return\n\n");

}

void search_by_id(pSTUDENT stu_list)
{
	pSTUDENT p = stu_list->next;
	int id,i;
	int flag=0;
	system("cls");
	printf("Input ID:");
	scanf("%d",&id);
	while(p != NULL)
	{
		if(p->stu_id == id)
		{
			printf("%4d  %-8s",p->stu_id,p->stu_name);
			for(i=0;i<COURSE_NUM;i++)
			{
				printf("%5d  %-7.2f",p->course[i].course_id,p->course[i].course_score);
			}
			printf("\n");
			flag=1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(0 == flag)
	{
		printf("Not found");
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void add_student_information(pSTUDENT *stu_list,char *str2)
{
	pSTUDENT p = (pSTUDENT)calloc(1,sizeof(STUDENT));
	pSTUDENT pre=NULL,pcur=NULL;
	int flag,i;
	while(1)
	{
		flag = 1;
		system("cls");
		printf("Please input a student's information to add.\n");
		printf("The fomation is [id name] and %d course information [CourseId CourseScore]\n", COURSE_NUM);
		fflush(stdin);
		scanf("%d%s",&p->stu_id,&p->stu_name);
		for(i=0;i<COURSE_NUM;i++)
		{
			scanf("%d%lf",&p->course[i].course_id,&p->course[i].course_score);
		}
		if(NULL == (*stu_list)->next)
		{
			p->next=(*stu_list)->next;
			(*stu_list)->next=p;
		}
		else
		{
			pre = (*stu_list);
			pcur=(*stu_list)->next;
			while( NULL != pcur )
			{
				if(pcur->stu_id>p->stu_id)
				{
					p->next=pcur;
					pre->next=p;
					break;
				}
				else if(pcur->stu_id == p->stu_id)
				{
					flag = 0;
					break;
				}
				else 
				{
					pcur=pcur->next;
					pre=pre->next;
				}
			}
			if(NULL == pcur)
			{
				pre->next=p;
			}
		}
		if(flag)
		{
			printf("Insert success!\n");
			update_student_database(stu_list,str2);
		}
		else
		{
			printf("Error!\nThis student's ID has existed in database.\n");
		}
		printf("\nPress y to continue add,or any key else to return:");
		fflush(stdin);
		if (_getch() != 'y')
		{
			break;
		}
	}
}

void update_student_database(pSTUDENT *stu_list,char *str2)
{
	FILE *fp = fopen(str2,"w");
	pSTUDENT p = (*stu_list)->next;
	int i;
	if(NULL != fp)
	{
		while(NULL != p)
		{
			fprintf(fp,"%4d  %-10s",p->stu_id,p->stu_name);
			for(i=0;i<COURSE_NUM;i++)
			{
				fprintf(fp,"%5d  %-7.2f",p->course[i].course_id,p->course[i].course_score);
			}
			fprintf(fp,"\n");
			p = p->next;
		}
		fclose(fp);
	}
	else 
	{
		perror("Update student.txt failed");
	}
}

void update_student_information(pSTUDENT *stu_list,char *str2)
{
	pSTUDENT p = (*stu_list)->next;
	int flag = 0,id,i;
	system("cls");
	printf("Input ID:");
	scanf("%d",&id);
	while(p != NULL)
	{
		if(p->stu_id == id)
		{
			printf("Please update the student's information.\n");
			printf("The fomation is [ID Name] and %d course information [CourseId CourseScore]\n", COURSE_NUM);
			scanf("%d%s",&p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM; i++)
				scanf("%d%lf", &p->course[i].course_id, &p->course[i].course_score);
			flag = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if(0 == flag)
	{
		printf("Not found\n");
	}
	else
	{
		printf("Update Success!");
		update_student_database(stu_list,str2);
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void delete_student_information(pSTUDENT *stu_list,char *str2)
{
	pSTUDENT pre = *stu_list;
	pSTUDENT pcur =(*stu_list)->next;
	int id,flag=0;
	system("cls");
	printf("Input the deleted ID:");
	scanf("%d",&id);
	while(NULL != pcur)
	{
		if(pcur->stu_id == id)
		{
			pre->next = pcur->next;
			free(pcur);
			pcur = NULL;
			flag = 1;
			break;
		}
		else
		{
			pcur = pcur->next;
			pre = pre->next;
		}
	}
	if(0 == flag)
	{
		printf("Not found\n");
	}
	else
	{
		printf("Delete Success!");
		update_student_database(stu_list,str2);
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void search_user_account(pUSER_ACCOUNT user_list)
{
	char button;
	while(1)
	{
		search_account_init();
		printf("select a number:");
		fflush(stdin);
		scanf("%c",&button);
		switch(button)
		{
		case '0':search_user_all(user_list); break;
		case '1':search_by_userlevel(user_list); break;
		case '2':search_by_username(user_list); break;
		case '3':return; break;
		default:
			fflush(stdin);
			printf("Input Error!\nPress any key to select again");
			_getch();
		}
	}
}

void search_account_init()
{
	system("cls");
	printf("[0] search all\n");
	printf("[1] search by level\n");
	printf("[2] search by name\n");
	printf("[3] return\n\n");
}

void search_user_all(pUSER_ACCOUNT user_list)
{
	pUSER_ACCOUNT p = user_list->next;
	system("cls");
	while(NULL != p)
	{
		if(p->users_limit == ADMIN)
		{
			printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name,p->user_password,"ADMIN");
			p = p->next;
		}
		else
		{
			printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name,p->user_password,"GUEST");
			p = p->next;
		}
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void search_by_userlevel(pUSER_ACCOUNT user_list)
{
	pUSER_ACCOUNT p = user_list;
	int i;
	system("cls");
	printf("Input level:  [0:admin,1:guest]\n");
	scanf("%d",&i);
	if(i!= 0 && i != 1)
	{
		system("cls");
		printf("Input level:  [0:admin,1:guest]\n");
	}
	else
	{
		p = user_list->next;
		while(NULL != p)
		{
			if(p->users_limit == i && i == 0)
			{
				printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name, p->user_password, "ADMIN");
				p = p->next;
			}
			else if(p->users_limit == i && i == 1)
			{
				printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name, p->user_password, "GUEST");
				p = p->next;
			}
			else
			{
				p = p->next;
			}
		}
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void search_by_username(pUSER_ACCOUNT user_list)
{
	pUSER_ACCOUNT p = user_list->next;
	char name[USER_NAME_LEN+1]="";
	int i,flag = 0;
	system("cls");
	printf("Input name:");
	scanf("%s", name);
	while(NULL != p)
	{
		if(strcmp(p->user_name,name) == 0)
		{
			if(p->users_limit ==0)
			{
				printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name, p->user_password, "ADMIN");
				flag = 1;
				break;
			}
			else
			{
				printf("Username:%-15s Password:%-10s Userlevel:%s\n", p->user_name, p->user_password, "GUEST");
				flag = 1;
				break;
			}
		}
		else
		{
			p = p->next;
		}
	}
	if( 0 == flag )
	{
		printf("Not found\n");
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void add_user_account(pUSER_ACCOUNT *user_list,char *str1)
{
	pUSER_ACCOUNT p = (pUSER_ACCOUNT)calloc(1,sizeof(USER_ACCOUNT));
	pUSER_ACCOUNT pcur = (*user_list)->next;
	int i ;
	while(1)
	{
		system("cls");
		printf("Please input a user's information to add.\n");
		printf("The fomation is [Username] [Password] [Level]\n");
		printf("The level rank: [0:admin, 1:guest]\n");
		fflush(stdin);
		scanf("%s%s%d", &p->user_name, &p->user_password,&p->users_limit);
		while(NULL != pcur)
		{
			if(strcmp(pcur->user_name,p->user_name) == 0)
			{
				printf("Error!\nThis user has existed in database.\n");	
				goto SELECT;
			}
			pcur = pcur->next;
		}
		p->next = (*user_list)->next;
		(*user_list)->next = p;
SELECT:
		printf("\nPress y to continue add,or any key else to return:");
		fflush(stdin);
		if (_getch() != 'y')
			break;
	}
	update_userdatabase(user_list,str1);
}

void update_user_account(pUSER_ACCOUNT *user_list,char *str1)
{
	pUSER_ACCOUNT p = (*user_list)->next;
	char name[USER_NAME_LEN + 1]="";
	int i,flag = 0;
	system("cls");
	printf("Input name:");
	scanf("%s",name);
	while(NULL != p)
	{
		if(strcmp(p->user_name,name) == 0)
		{
			printf("Please update the user's information.\n\n");
			printf("The fomation is [Username] [Password] [Level]\n");
			printf("The level rank: [0:admin, 1:guest]\n");
			flag = 1;
			fflush(stdin);
			scanf("%s%s%d", &p->user_name, &p->user_password, &p->users_limit);
			break;
		}
		else 
		{
			p = p->next;
		}
	}
	if( 0 == flag )
	{
		printf("Not found\n");
	}
	else
	{
		printf("Update success!\n");
		update_userdatabase(user_list,str1);
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();

}

void update_userdatabase(pUSER_ACCOUNT *user_list,char *str1)
{
	FILE *fp = fopen(str1,"w");
	pUSER_ACCOUNT p = (*user_list)->next;
	if(NULL != fp)
	{
		while(NULL != p)
		{
			fprintf(fp, "%-15s %-10s %d\n", p->user_name, p->user_password, p->users_limit);
			p = p->next;
		}
	}
	else
	{
		perror("Update user_account.txt failed");
	}
}

void delete_user_account(pUSER_ACCOUNT *user_list,char *str1)
{
	pUSER_ACCOUNT pre = (*user_list);
	pUSER_ACCOUNT pcur = (*user_list)->next;
	char name[USER_NAME_LEN + 1];
	int i,flag = 0;
	system("cls");
	printf("Input name:");
	scanf("%s",name);
	while(NULL != pcur)
	{
		if(strcmp(pcur->user_name,name) == 0)
		{
			pre->next = pcur->next;
			free(pre);
			pre = NULL;
			flag = 1;
			break;
		}
		else
		{
			pcur = pcur->next;
			pre = pre->next;
		}
	}
	if(0 == flag)
	{
		printf("Not found\n");
	}
	else
	{
		printf("Delete success!\n");
		update_userdatabase(user_list,str1);
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void search_by_name(pSTUDENT stu_list)
{
	pSTUDENT p = stu_list->next;
	int i;
	char name[USER_NAME_LEN + 1];
	int flag = 0;
	system("cls");
	printf("Input name:");
	scanf("%s", name);
	while(NULL != p)
	{
		if(strcmp(p->stu_name,name) == 0)
		{
			printf("%04d  %-8s ", p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM; i++)
			{
				printf("%05d %-8.2f", p->course[i].course_id, p->course[i].course_score);
			}
			printf("\n");
			flag = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if(0 == flag)
	{
		printf("Not found");
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void search_all(pSTUDENT stu_list)
{
	pSTUDENT p = stu_list->next;
	int i;
	system("cls");
	while(NULL != p)
	{
		printf("%4d  %-8s ", p->stu_id, p->stu_name);
		for (i = 0; i < COURSE_NUM; i++)
		{
			printf("%5d %-8.2f", p->course[i].course_id, p->course[i].course_score);
		}
		printf("\n");
		p = p->next;
	}
	printf("\nPress any key to continue\n");
	fflush(stdin);
	_getch();
}

void system_exit()
{
	system("cls");
	printf("Thank you for you use !\n");
	system("pause");
	exit(1);
}
