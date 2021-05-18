#include<stdio.h>
#include <math.h>
int main(){
	float temperatura1=0, tempF, tempC;
	char c; 
	printf("Teclee la temperatura de acuerdo al formato <numero><letra>,(letra debe ser c o f)\n");
	scanf("%f%c",&temperatura1,&c);

	tempF=(temperatura1*9/5)+32;	
	tempC=(temperatura1-32)*(0.555556);	
	
	(c=='c')? printf("Temperatura 1 esta en Celsius: %.2f",tempF): printf("Temperatura 1 esta Farenheit: %.2f",tempC);
}