系统功能描述
	该系统管理学生的课程信息。系统提供账户的管理和学生信息的管理功能。
系统提供的功能主要有 学生信息的查询、修改、增加、删除，账户信息的查询、修改、增加、删除。

----------------------------------------------------------------------------------------

登陆运行提示：

----------------------------------------------------------------------------------------
welcome to SIMS                                                                        |
Please select your account level:                                                      |
                                                                                       |
[0] You are a teacher                                                                  |
[1] You are a student                                                                  |
[2] Exit                                                                               |
                                                                                       |
select a number:                                                                       |
----------------------------------------------------------------------------------------

登录管理系统的账户分为管理员账户和普通账户:
*普通用户只具有查询学生信息的功能:

----------------------------------------------------------------------------------------
[1] search student information
[2] exit
select a number:
----------------------------------------------------------------------------------------

*管理员用户具有系统提供的所有功能:

----------------------------------------------------------------------------------------
[1] search   student information                                                       |
[2] add      student information                                                       |
[3] update   student information                                                       |
[4] delete   student information                                                       |
[5] search   user acount                                                               |
[6] add      user acount                                                               |
[7] update   user acount                                                               |
[8] delete   user acount                                                               |
[9] exit                                                                               |
                                                                                       |
select a number:                                                                       |
----------------------------------------------------------------------------------------


系统数据主要存储在三个文件：configure.txt usr_account.txt student.txt .
usr_account.txt 主要用于存放用户账户信息,0表示管理员账户，1表示普通用户
student.txt 主要用于存放学生信息
configure.txt 主要用于存放配置信息：usr_account.txt student.txt文件的存储位置路径信息,根据这个路径信息去读这两个文件


----------------------------------------------------------------------------------------


系统在启动时会根据配置文件里的内容找到相应文件并读取出数据来加载账户信息和学生信息
SIMS 用到的结构体：
typedef struct user{
	char user_name[USER_NAME_LEN+1];  
	char user_password[USER_PASSWORD_LEN+1];
	int users_limit;
	struct user *next;
}USER_ACCOUNT,*pUSER_ACCOUNT;    //注册账户信息

typedef struct course{
	int course_id;
	double course_score;
}COURSE,*pCOURSE;     //多个课程，课程结构体

typedef struct student{
	int stu_id;
	char stu_name[USER_NAME_LEN+1];
	COURSE course[COURSE_NUM];
	struct student *next;
}STUDENT,*pSTUDENT;   //学生信息结构体


----------------------------------------------------------------------------------------
Windows 下的是在windows 10系统下的Visual Studio 2012开发的
Linux 下的是在Linux ubuntu 4.10.0-42-generic #46~16.04.1-Ubuntu SMP Mon Dec 4 15:57:59 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux下开发的


****注****
windows版本随意使用;windows版本下的configure.txt和usr_account.txt student.txt在同一目录下，
要注意configure.txt内容要相应更改成这两个文件的绝对路径。
Linux版本输入信息错误不能退格删除，只能重启;发送SIGINT信号结束进程
Linux版本提示输入信息（任意字符）继续的时候不要输入回车，其他都行;



