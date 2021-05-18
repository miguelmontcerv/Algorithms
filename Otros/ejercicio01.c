#include<stdio.h>
int main(int argc, char const *argv[])
{

	int i = 0, k = 0,n,j;

	printf("Favor de ingresar n: ");
	scanf("%d",&n);
	printf("\n");

	/*for(i = 10; i < n*5; i*=2)
		printf("It: %d\n",++k);*/

	for(j = n; j > 1; j/=2)
		if(j < (n/2))
			for(i = 0; i < n; i+=2)
				printf("It: %d\n",++k);


	return 0;
}