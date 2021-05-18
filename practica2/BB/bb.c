//Busqueda Binaria
//Primero ordenaremos la entrada
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
int buscar(int*,int,int,int);
int count = 0,cuenta = 0;

int main(int argc, char const *argv[])
{	
	struct Arbol *arbol = NULL;
	int num, n, i;		
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	
	//Numero de numeros que se ordenarán
	n=atoi(argv[1]);
	int *numeros = (int*) malloc(sizeof(int)*n);	
	int bus=atoi(argv[2]);

	for(i = 0; i < n + 1; i++){
		scanf("%d",&num);
		arbol = AgregarElemento(arbol,num);	
	}			
	InOrden(arbol,numeros);
	//for (i = 0; i < n + 1; ++i) printf("%d. %d\n",i+1,*(numeros + i));
	
	uswtime(&utime0, &stime0, &wtime0);
	int encontrado = buscar(numeros,bus,n,0);
	uswtime(&utime1, &stime1, &wtime1);

	printf("\nBusqueda Binaria con %d numeros, buscando el %d: (%d)",n,bus,encontrado);
	if(encontrado == -1) printf(" %d vueltas\n",cuenta);
	else printf("\n");	
	
	
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("------------------------------------------------------\n");

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

void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1)
{
	printf("\n");
	printf("Tiempo: %.10f\n", wtime1 - wtime0);
}
int buscar(int *numeros, int bus, int tam, int inicio)
{
	cuenta = 1;
	int mid = inicio + (tam - inicio) / 2;	

	if (*(numeros + inicio) == bus)
	
	if (*(numeros + mid) == bus)
		return 1;
	if (*(numeros + tam) == bus)
		return 1;	
	
	if(*(numeros + mid) > bus)
		tam = mid - 1;
	else
		inicio = mid + 1;
	
	while(inicio <= tam)
	{	
		cuenta++;		
		mid = inicio + (tam - inicio) / 2;
		if (*(numeros + inicio) == bus)
			return 1;
		if (*(numeros + mid) == bus)
			return 1;	
		if (*(numeros + tam) == bus)
			return 1;		
		if(*(numeros + mid) > bus)
			tam = mid - 1;
		else
			inicio = mid + 1;		
	}
	return -1;
}