//Ejercicio 3, programa1: Suma cuadratica de los 3 numeros mayores de un arreglo
#include<stdio.h>
#include<stdlib.h>


int SumaCuadratica3Mayores(int *a, int n);
int potencia(int num, int pot);
int main(int argc, char const *argv[])
{
	int n,aux;
	printf("Ingresa el tamaño del arreglo: ");
	scanf("%d",&n);
	int *a = (int*) malloc(sizeof(int)*n);

	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&aux);
		*(a + i) = aux;
	}	

	int r = SumaCuadratica3Mayores(a,n);

	printf("La suma cuadratica es: %d\n",r);

	return 0;
}

int SumaCuadratica3Mayores(int *a, int n){
	int m1 = 0,m2 = 0, m3 = 0;	
	
	if(*(a + 0) > *(a+1) && *(a+0) > *(a+2))
	{ 
		m1 = *(a+0);
		if(*(a+1) > *(a+2))
		{
			m2 = *(a+1);
			m3 = *(a+2);
		}
		else
		{
			m2 = *(a+2);
			m3 = *(a+1);
		}	
	}
	else if(*(a+1) > *(a+0) && *(a+1) > *(a+2))
	{
		m1 = *(a+1);
		if(*(a+0) > *(a+2))
		{
			m2 = *(a+0);
			m3 = *(a+2);
		}
		else
		{
			m2 = *(a+2);
			m3 = *(a+0);	
		}
	}
	else
	{
		m1 = *(a+2);
		if(*(a+0) > *(a+1))
		{
			m2 = *(a);
			m3 = *(a+1);
		}
		else
		{
			m2 = *(a+1);
			m3 = *(a+0);	
		}
	}

	int i = 3;
	printf("\t\tLa Creencia Mayores:%d %d %d\n",m1,m2,m3);
	while(i <= n)
	{
		if(*(a+i) > m1){
			m3 = m2;
			m2 = m1;
			m1 = *(a+i);
		}
		else if(*(a+i) > m2){
			m3 = m2;
			m2 = *(a+i);			
		}
		else if(*(a+i) > m3)
		{m3 = *(a+i);}	
		i++;		
	printf("\t\tCreencia Mayores:%d %d %d\n",m1,m2,m3);
	}

	int sum = m1+m2+m3;
	int val = potencia(sum,2);

	printf("\tMayores:%d %d %d\n",m1,m2,m3);
	return val;
}

int potencia(int num, int pot){
	if(pot < 2)
		return num;
	int i = 1;
	int aux = num;
	
	while(i <= pot){
		num = num * aux;
		i++;
	}

	return num;
}