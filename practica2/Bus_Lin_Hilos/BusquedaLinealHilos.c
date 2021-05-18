#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <pthread.h>

int n, x, mitad;
int *arr;
int bandera = 0;


void* procesar(void* id)
{	
	int n_thread=(int)id;	
	
	if(n_thread==1){
	
	for (int i = 0; i < mitad; i++)
        if (arr[i] == x)
 			bandera = 1;
	}
			
	else{
		for (int i = mitad; i < n; i++)
        if (arr[i] == x)
        	bandera = 1;
	}
	
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
	n = atoi(argv[1]);
	arr = (int*) malloc(sizeof(int)*n);
	
    x = atoi(argv[2]);
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para mediciรณn de tiempos.
    
    //For para poder leer las entradas.
	for(int i = 0; i < n; i++){
			
		scanf("%d",&arr[i]);

	}	
	
	pthread_t thread1;
    pthread_t thread2;
    int i = 1;
    int k = 2;
    mitad = n/2;
    
    uswtime(&utime0, &stime0, &wtime0); //Se llama la funcion para los tiempos.
    
    if (pthread_create (&thread1, NULL, procesar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
			
	if (pthread_create (&thread2, NULL, procesar,(void*)k) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
   
	//Esperar a que terminen los threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
    uswtime(&utime1, &stime1, &wtime1); //Se llama la funcion para los tiempos.
    
    if(bandera == 0)
        printf("Con %d numeros, el numero %d no esta en el arreglo \n", n, x);
    else
        printf("Con %d numeros, el numero %d esta en el arreglo \n", n , x);
        
    ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	printf("-------------------------------------------------------------------------------\n");    
        
    return 0;
}
