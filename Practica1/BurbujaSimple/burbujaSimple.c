#include<stdio.h>
#include<stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

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

//Funcion para Imprimir los tiempos.
void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1){
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciรณnes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciรณnes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int *numeros = (int*) malloc(sizeof(int)*10000000); //Reservar Memoria.
	int n, i, j; //Variables para los for y argumento
	int temp = 0; //variable auxiliar para el Algoritmo.
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para mediciรณn de tiempos.
	
	n = atoi(argv[1]); //Se convierte en Int el Argumento y se asigna a n.
	
	//For para poder leer las entradas.
	for(i = 0; i < n; i++){
			
		scanf("%d",&numeros[i]);

	}	
	
	uswtime(&utime0, &stime0, &wtime0); //Se llama la funcion para los tiempos.

	//COMIENZA ALGORTIMO DE BURBUJA
	for (i = 0; i <= n-2; i++)
	{
		for (j = 0; j <= (n-2)-i; j++)
		{
			if (numeros[j] > numeros[j+1])
			{
				temp = numeros[j];	 
				numeros[j] = numeros[j+1];  
				numeros[j+1] = temp;
			}
		}

	}
	//ACABA ALGORITMO DE BURBUJA

	uswtime(&utime1, &stime1, &wtime1); //Se llama la funcion para los tiempos.
	
	//Se llama a la funcion para Imprimir los tiempos.
	printf("Tamanio de N = %d", n);
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("############################## \n");
	return 0;
}