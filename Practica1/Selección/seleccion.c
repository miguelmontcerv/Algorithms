#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
//Programa principal
int main (int argc, char* argv[])
{	
	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n, i, j, k, aux, cambios=0,temp,p; 	//Variables del algoritmo
	int *A; //Apuntador para hacer el arreglo
	char true,false; //Variables booleanos

	//Si no recibe el argumento se cierra
	if (argc!=2) 
		exit(1);
	
	//Numero de numeros que se ordenarán
	n=atoi(argv[1]);
	//Creación del arreglo
	A=malloc(n*sizeof(int));
	
	//Se guardan los numeros en el arreglo
	for(i=0; i<n;i++);
		scanf("%i",&A[i]);
	
	printf("\tselecion para %i numeros\n", n);
	
	
	uswtime(&utime0, &stime0, &wtime0);
	
	//Algoritmo	
   	for(k=0;k<n-2;k++)
   	{
   		//Se recorre el arreglo
      	p=k;
      	for(i=k+1;i<n-1;i++)
      	{
      		//Por cada vez que se recorre, comparamos el actual con el minimo
      		if(A[i]<A[p])
      		{
      			p=i;
      		}
      	}
      	//Aqui ya tiene el minimo y lo guarda
      	temp = A[p];
      	A[p]=A[k];
      	A[k]= temp;
   	}

	uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("\n");
	//******************************************************************

	printf("##################################################################################################\n");

	return 0;
}