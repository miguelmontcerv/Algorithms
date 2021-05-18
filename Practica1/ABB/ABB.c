//Practica 1
//Arbol binario de busqueda, recorrido inorder

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

void uswtime(double *usertime, double *systime, double *walltime);
struct Arbol *AgregarElemento(struct Arbol *,int);
void InOrden(struct Arbol *,int *);
void ImprimirTiempos(double,double,double,double,double,double);
int count = 0;

int main(int argc, char const *argv[])
{	
	struct Arbol *arbol = NULL;
	int num, n, i;	
	int *numeros = (int*) malloc(sizeof(int)*10000000);
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	
	//Numero de numeros que se ordenarán
	n=atoi(argv[1]);
	
	uswtime(&utime0, &stime0, &wtime0);
	
	for(i = 0; i < n + 1; i++){
		scanf("%d",&num);
		arbol = AgregarElemento(arbol,num);	
	}


	printf("\tArbol Binario de Busqueda con %d numeros\n",n);	

	InOrden(arbol,numeros);

	uswtime(&utime1, &stime1, &wtime1);
	
	//for (i = 0; i < 10000000; ++i) printf("%d. %d\n",i+1,*(numeros + i));
	
	
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("##################################################################################################\n");

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

void InOrden(struct Arbol *arbol, int *numeros)
{
	if(arbol == NULL)
		return;

	InOrden(arbol -> izq,numeros);
	*(numeros + count) = arbol -> dato;
	count++;
	//printf("%d\n",arbol -> dato);
	InOrden(arbol -> der,numeros);
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
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));	
	printf("\n");
}