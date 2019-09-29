
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

extern int tempI;
extern int temp2;

struct AA
{
	int i;
	float j;
	int m;
	int n;
	char mm[10];
	char nn[10];
};

struct AA a;

void test();

void GetBeginDate(char *begindate)
{
   struct tm tmloc;
   time_t timet;
   timet = time(NULL);
   memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
   strftime(begindate,12,"%m%d%H%M%S",&tmloc);
}

int test11()
{
	return 0;
}

int main(int argc, char** argv)
{
	char date[16] = {0};
	GetBeginDate(date);

	int i = sizeof( int);
		
	if(!test11())
	{
		printf("testsddd\n");
	}

	char arr1[10] = "helloniha";
	strcpy(arr1,"nihao");
	printf("%s\n",arr1);
	for(int i = 0;i < 10;i ++)
	{
		printf("%c\t",arr1[i]);
	}
	printf("\n");

	strncpy(arr1,"nihao",8);
	printf("%s\n",arr1);

	for(int i = 0;i < 10;i ++)
    {
        printf("%c\t",arr1[i]);
    }
    printf("\n");

	a.n = 20;
	strcpy(a.mm,"hello");
	strcpy(a.nn,"world");

	//memset(&a,0,sizeof(a));
	//memset(&a,0,sizeof(a) - sizeof(a.m) - sizeof(a.n) - sizeof(a.mm) - sizeof(a.nn));
	memset(&a,0,sizeof(a) - 11);

	printf("%d:%d:%s:%s:\n",a.m,a.n,a.mm,a.nn);
	
	printf("%s\n",date);
	printf("%.4lf",floor(2815068.495f));
	test();	
	std::cout << temp2 << '\n';
	return 0;
}
