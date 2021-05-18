#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[])
{
	char **matriz = (char **)malloc(sizeof(char*)*2);
	matriz[0] = (char *)malloc(sizeof(char)*3); 
	matriz[1] = (char *)malloc(sizeof(char)*3);

	/*
	0 4 9
	3 5 7
	*/
	//Dentro filas, afuera columnas
	*(*(matriz+0)+0) = '0';
	*(*(matriz+0)+1) = '4';
	*(*(matriz+0)+2) = '9';

	*(*(matriz+1)+0) = '3';
	*(*(matriz+1)+1) = '5';
	*(*(matriz+1)+2) = '7';
	

	for (int i = 0; i < 2; ++i){
		for (int j = 0; j < 3; ++j)
			printf("%c ",*(*(matriz+1)+j));
		printf("\n");
	}
		
		


	return 0;
}