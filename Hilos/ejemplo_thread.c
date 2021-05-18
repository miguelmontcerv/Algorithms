// Hilos en C
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1);
void uswtime(double *usertime, double *systime, double *walltime);

int NumThreads;			//Número de threads
int N;

//COMPORTAMIENTO DE LOS THREADS

//1 Saludar 
void* saludar(void* id)
{
	printf("\nHola desde Saludar\tSoy el thread %d",(int)id);
}

//2 Realizar un procesamiento

void* procesar(void* id)
{	
	int n_thread=(int)id;
	int inicio,fin,i,a;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*N)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=N;
	else
		fin=((n_thread+1)*N)/NumThreads-1;

	printf("\nHola desde procesar\tSoy el thread %d\t\tInicio %d\t\tTermino %d",n_thread,inicio,fin);
	for(i=inicio;i<=fin;i++)
		a=i*i;		
		//printf("\nProcesando dato %d",i);

	printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}

//PROGRAMA PRINCIPAL 
int main (int argc, char *argv[])
{	
	int i,j,k; 	//Variables auxiliares para loops
	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	double utime0, stime0, wtime0,utime1, stime1, wtime1;
	uswtime(&utime0, &stime0, &wtime0);
	
	//Obtener el número de threads a usar y el arreglo para la identificacion de los mismos
	pthread_t *thread;
	if (argc<2) 
	{
		printf("Indique el número de threads - \tEjemplo: [user@equipo]$ %s 4\n\n",argv[0]);
		exit(-1);
	}  
	NumThreads=atoi(argv[1]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	
	//Saber cuál es el tamaño del problema N
	//Si no se introduce correctamente N
	if (argc!=3) 
	{
		printf("\nIndique el tamaño de N - \nEjemplo: [user@equipo]$ %s %s 1000\n",argv[0],argv[1]);
		exit(-1);
	}
	N=atoi(argv[2]);

	//1 Saludar desde cada hilo "saludar"

	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, saludar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	
	//El main ejecuta el thread 0
	saludar(0);
	
	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);
					
	//2 Procesar desde cada hilo "procesar"

	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	
	//El main ejecuta el thread 0
	procesar(0);
	
	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);
	
	//Evaluar los tiempos de ejecución 
	uswtime(&utime1, &stime1, &wtime1);
	//Cálculo del tiempo de ejecución del programa
	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
	
	//Terminar programa normalmente	
	exit (0);	
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