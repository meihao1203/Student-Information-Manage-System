 ///
 /// @file    main.c
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2017-12-22 08:49:35
 ///
#include<stdio.h>
#include<stdlib.h>
int main()
{
	char *s = "../conf/configure.txt";
	FILE *fp = fopen(s,"r");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char str[1024];
	fgets(str,sizeof(str),fp);
	printf("%s\n",str);
	fclose(fp);
	return 0;
}
