#include <stdio.h>
#include <stdlib.h>

int SumaCuadratica3Mayores(int *a,int n);

int main(int argc, char const *argv[])
{
	printf("Introduce la longitud del arreglo: ");
	int n;
	scanf("%d",&n);

	int *a = (int *)malloc(sizeof(int)*n);
	int aux;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&aux);
		*(a + i) = aux;
	}	

	int suma = SumaCuadratica3Mayores(a,n);
	printf("La suma es: %d\n",suma);
	return 0;
}

int SumaCuadratica3Mayores(int *a,int n){
	int aux;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < n-1; ++j)
		{
			if(*(a+j) > *(a+j+1))
			{
				aux = *(a+j);
				*(a+j) = *(a+j+1);
				*(a+j+1) = aux;
			}
		}
	}
	int r = *(a+n-1) + *(a+n-2) + *(a+n-3);
	printf("\tMayores:%d %d %d\n",*(a+n-1),*(a+n-2),*(a+n-3));
	return r * r;
}