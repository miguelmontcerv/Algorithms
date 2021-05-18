#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[])
{
	char *archivon = (char *)malloc(sizeof(char)*20);
	archivon = (char *) argv[1];
	printf("%s\n",archivon);
		
	return 0;
}