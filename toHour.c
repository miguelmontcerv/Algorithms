#include<stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int seg_totales,horas,min,seg,aux;
	scanf("%d",&seg_totales);
	horas = seg_totales / 3600;
	aux = seg_totales % 3600;
	min = aux / 60;
	seg = aux % 60;
	printf("Son %d horas, %d minutos y %d segundos\n",horas,min,seg);
	return 0;
}