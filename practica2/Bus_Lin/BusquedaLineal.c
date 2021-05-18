#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
 
int search(int arr[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
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

//Funcion para Imprimir los tiempos.
void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1){
	printf("\n");
	/*printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));*/
	printf("Tiempo: %.10f\n", wtime1 - wtime0);
}


int main(int argc, char const *argv[])
{
	
	//Numero de numeros que se ordenarán
	int n = atoi(argv[1]);
	int *arr = (int*) malloc(sizeof(int)*n);
	
    int x = atoi(argv[2]);
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para mediciรณn de tiempos.
    
    //For para poder leer las entradas.
	for(int i = 0; i < n; i++){
			
		scanf("%d",&arr[i]);

	}	
    	
   
    uswtime(&utime0, &stime0, &wtime0); //Se llama la funcion para los tiempos.
    
    int result = search(arr, n, x); //LLAMADA A LA FUNCION DEL ALGORITMO.
    
    
    uswtime(&utime1, &stime1, &wtime1); //Se llama la funcion para los tiempos.
    if(result == -1)
        printf("Con %d numeros, el numero %d no esta en el arreglo \n", n, x);
    else
        printf("Con %d numeros, el numero %d esta en el lugar %d \n", n , x, result);
        
    ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("-------------------------------------------------------------------------------\n");    
        
    return 0;
}
