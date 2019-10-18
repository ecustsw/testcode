#include <cstdio>
#include <unistd.h>

bool hasPermission(char* fileName,int flags)
{
	if(access(fileName,flags))
	{
		printf("no permission\n");
		return false;
	}
	printf("has permission%x\n",flags);
	return true;
}

int main(int argc,char ** argv)
{
	if(argc < 2)
	{
		printf("bad arguments\n");
		return -1;
	}

	hasPermission(argv[1],R_OK|W_OK);

	return 0;
}