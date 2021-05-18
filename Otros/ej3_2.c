//Ejercicio 3, programa 2: Maximo Comun Divisor
#include <stdlib.h>
#include <stdio.h>

int MaximoComunDivisor(int m, int n);
int max(int m,int n);
int min(int m,int n);

int main(int argc, char const *argv[])
{
	int m,n;
	printf("Ingrese el primer número: ");
	scanf("%d",&m);
	printf("Ingrese el segundo número: ");
	scanf("%d",&n);
	int mcd = MaximoComunDivisor(m,n);
	printf("El Maximo Comun Divisor es: %d\n",mcd);
	return 0;
}

int MaximoComunDivisor(int m, int n)
{
	int a = max(n,m);
	int b = min(n,m);

	int residuo = 1;
	while(residuo > 0)
	{
		residuo = a % b;
		a = b;
		b = residuo;
	}
	int mcd = a;
	return mcd;
}

int max(int a,int b){
	if(a > b)
		return a;
	else
		return b;
}
int min(int a,int b){
	if(a < b)
		return a;
	else
		return b;
}