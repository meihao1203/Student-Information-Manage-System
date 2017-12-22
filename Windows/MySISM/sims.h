#define USER_NAME_LEN 20
#define USER_PASSWORD_LEN 8
#define COURSE_NUM 3
enum {ADMIN,GUEST};

typedef struct user{
	char user_name[USER_NAME_LEN+1];  
	char user_password[USER_PASSWORD_LEN+1];
	int users_limit;
	struct user *next;
}USER_ACCOUNT,*pUSER_ACCOUNT;

typedef struct course{
	int course_id;
	double course_score;
}COURSE,*pCOURSE;

typedef struct student{
	int stu_id;
	char stu_name[USER_NAME_LEN+1];
	COURSE course[COURSE_NUM];
	struct student *next;
}STUDENT,*pSTUDENT;

void system_init(pUSER_ACCOUNT *user_list,pSTUDENT *stu_list,char *str1,char *str2);

void interface_init();

void GetPassword(char *password);

int check_user_account(pUSER_ACCOUNT ,USER_ACCOUNT);

void admin_account(pUSER_ACCOUNT *,pSTUDENT *,char *,char *);

void guest_account(pSTUDENT);

void admin_interface_init();

void search_student_information(pSTUDENT , int);

void search_init(int);

void search_by_id(pSTUDENT);

void add_student_information(pSTUDENT *,char *);

void update_student_database(pSTUDENT *,char *);

void update_student_information(pSTUDENT *,char *);

void delete_student_information(pSTUDENT *,char *);

void search_user_account(pUSER_ACCOUNT);

void search_account_init();

void search_user_all(pUSER_ACCOUNT);

void search_by_userlevel(pUSER_ACCOUNT);

void search_by_username(pUSER_ACCOUNT); 

void add_user_account(pUSER_ACCOUNT *,char *);

void update_user_account(pUSER_ACCOUNT *,char *);

void update_userdatabase(pUSER_ACCOUNT *,char *);

void delete_user_account(pUSER_ACCOUNT *,char *);

void guest_interface_init();

void search_by_name(pSTUDENT);

void search_all(pSTUDENT);

void system_exit();