#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
//prototipos de la funcion
double utime0, stime0, wtime0,utime1, stime1, wtime1;


//Funcion de inserccion
void Inserccion(int *A, int n){
    int j, i, temp=0;
    for(i=0; i<=n-1;i++){
        j=i;
        temp=(int)A[i];
        while((j>0) && (temp<(int)A[j-1])){
            A[j]=A[j-1];
            j--;
        }
        A[j]=temp;
    }
}

//Librerias para medir el tiempo

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


//funcion para imprimir tiempos en linux
void ImprimirTiempos(double utime0,double stime0,double wtime0,double utime1,double stime1,double wtime1){
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
}


int main(int argc, char *argv[]){
	
	
    int *numeros=(int *)malloc(sizeof(int)*1000000);//Arreglo dinamico de aountadores a enteros
	int var; //variable que guarda los numeros leidos del archivo
	int cantidad= atoi(argv[1]);//cantidad de numeros a leer    
    int n;   

	n=atoi(argv[1]);
	
	for(int i = 0; i < n + 1; i++){
		scanf("%d",&var);
		numeros[i]=var;	
	}
	

	uswtime(&utime0, &stime0, &wtime0);
    Inserccion(numeros, cantidad);//llamada a inserccion
	uswtime(&utime1, &stime1, &wtime1);

	ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);


    return 0;
}
