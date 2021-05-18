#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[])
{
	int *numero = (int*) malloc(sizeof(int)*1000);
	
	
	for (int i = 0; i < 1000; ++i)
	{
		*(numero + i) = i;
	}

	for (int i = 0; i < 1000; ++i)
	{
		printf("%d\n",*(numero + i) );
	}

	return 0;
}