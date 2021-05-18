//Practica 1
//Arbol binario de busqueda, busqueda
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

struct Arbol
{
	int dato;
	struct Arbol *izq;
	struct Arbol *der;
};

void *funcion(void *arbol);
void *funcionPrimerNodo(void *arbol);
void uswtime(double *usertime, double *systime, double *walltime);
struct Arbol *AgregarElemento(struct Arbol *,int);
void BuscarElemento(struct Arbol *raiz, int dato);
void BuscarElemento_PrimerNodo(struct Arbol *raiz, int dato);
void ImprimirTiempos(double,double,double,double,double,double);
int count = 0,bus,flag;

int main(int argc, char const *argv[])
{	
	struct Arbol *arbol = NULL;
	int num, n, i;		
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	pthread_t hilo1, hilo2, hilo3;

	//Numero de numeros que se ordenarán
	n=atoi(argv[1]);
	int *numeros = (int*) malloc(sizeof(int)*n);	
		
	for(i = 0; i < n + 1; i++){
		scanf("%d",&num);
		arbol = AgregarElemento(arbol,num);	
	}

	bus = atoi(argv[2]);	
	
	printf("\tABB con %d numeros, buscando el %d",n,bus);		

	uswtime(&utime0, &stime0, &wtime0);
	if(pthread_create (&hilo1, NULL, funcionPrimerNodo,(void*)arbol) != 0 )
		{ printf("Error\n"); return -1; }
	
	if(pthread_create (&hilo2, NULL, funcion,(void*)arbol->izq) != 0 )
		{ printf("Error\n"); return -1; }

	if(pthread_create (&hilo3, NULL, funcion,(void*)arbol->der) != 0 )
		{ printf("Error\n"); return -1; }

	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	pthread_join(hilo3,NULL);
	uswtime(&utime1, &stime1, &wtime1);
	
	//for (i = 0; i < 10000000; ++i) printf("%d. %d\n",i+1,*(numeros + i));
	printf(" (%d)\n",flag);
	
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("-----------------------------------------------\n");

	return 0;
}

struct Arbol *AgregarElemento(struct Arbol *raiz, int dato)
{
	if(raiz == NULL) // Caso base
	{
		struct Arbol *nuevo = NULL;
		nuevo = (struct Arbol *) malloc(sizeof(struct Arbol));
		nuevo -> dato = dato;
		nuevo -> izq = NULL;
		nuevo -> der = NULL;
		return nuevo;
	}

	if(dato < raiz -> dato){
		raiz -> izq = AgregarElemento(raiz -> izq, dato);
	}
	else
	{
		raiz -> der = AgregarElemento(raiz -> der, dato);
	}

	return raiz;
}

void BuscarElemento(struct Arbol *raiz, int dato)
{
		struct Arbol *aux = raiz;
		flag = 0;

		while(aux != NULL && flag == 0) {
			if(dato == aux->dato)
				flag = 1;
			else if(dato < aux->dato)
				aux = aux->izq;
			else
				aux = aux->der;
		}
		
		return;		
}
void BuscarElemento_PrimerNodo(struct Arbol *raiz, int dato){

		struct Arbol *aux = raiz;
		flag = 0;

		if(aux != NULL)
			if(dato == aux->dato)
				flag = 1;
			else
				return;
	return;
}

void uswtime(double *usertime, double *systime, double *walltime)
{
	double mega = 1.0e-6;
	struct rusage buffer;
	struct timeval tp;
	struct timezone tzp;
	getrusage(RUSAGE_SELF, &buffer);
	gettimeofday(&tp, &tzp);
	*usertime = (double) buffer.ru_utime.tv_sec +1.0e-6 * buffer.ru_utime.tv_usec;
	*systime  = (double) buffer.ru_stime.tv_sec +1.0e-6 * buffer.ru_stime.tv_usec;
	*walltime = (double) tp.tv_sec + 1.0e-6 * tp.tv_usec; 
}

void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1){
	printf("\n");
	/*printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));*/
	printf("Tiempo: %.10f\n", wtime1 - wtime0);
}

void *funcion(void *arbol){
	BuscarElemento((struct Arbol *)arbol,bus);
}

void *funcionPrimerNodo(void *arbol){
	BuscarElemento_PrimerNodo((struct Arbol *)arbol,bus);
}