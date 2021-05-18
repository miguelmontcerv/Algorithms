//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADArbolBin.h"
#include "tiempo.h"
#include <pthread.h>

void *busqueda(void*);

int x, encon1=0, encon2=0;

//Función principal
int main(int argc, char *argv[])
{
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i, n; //Variables del algoritmo
	arbol_bin a, b;	//arbol binario
	elemento e;	//Elemento e
	posicion p, q;	//Posiciones
	pthread_t h1, h2;	//Hilos

	//Si no se recibe el argumento, se cierra el programa
	if(argc!=3) 
		exit(1);
	
	//Numero elementos en el arreglo
	n=atoi(argv[1]);
	x=atoi(argv[2]);

	printf("\nx = %i\nn = %i\n",x,n);
	
	//Se inicializa el arbol y el primer valor será la raiz
	Initialize(&a);
	Initialize(&b);		
	scanf("%i",&e.d);
	Insertion(&a,p,e);
	p=Root(&a); //asignamos la posición p en la raiz de nuestro arbol a
	Insertion(&b,q,e);
	q=Root(&b); //asignamos la posición p en la raiz de nuestro arbol b

	//Se guardan todos los numeros
	for(i=1;i<n-1;i++)
	{
		scanf("%i",&e.d);
		//Se mete la mitad en un arbol y la mitad en otra
		if(i%2==0)
			Insertion(&a,p,e);
		else
			Insertion(&b,q,e);
	}
	
	//Definimos y q como las raices
	p=Root(&a);
	q=Root(&b);

	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	//Se busca el número x en los árboles, uo con cada hilo
	pthread_create (&h1, NULL, busqueda, (void*)&p);
	pthread_create (&h2, NULL, busqueda, (void*)&q);
	pthread_join (h1, NULL);
	pthread_join (h2, NULL);
	(encon1==1)?printf("Y\n"):printf("N\n");
	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	//Cálculo del tiempo de ejecución del programa
	printf("\nTiempo = %.10f s\n\n",  wtime1 - wtime0);
	//******************************************************************

	Destroy(&a);

	for(i=0;i<27;i++)
		printf("*");

	printf("\n");
	
	return 0;
}

//Funciones para buscar x en los arboles
void *busqueda(void *p){
	posicion p1=(posicion)p;
	//printf("H1\n");
	if(Busqueda(p1, x) != NULL)
		encon1=1;
}