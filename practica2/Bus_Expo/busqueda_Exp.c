#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct elem{
    int *arr1;
    int n1;
    int x;
    int result;
}*Elem;

int res;

void uswtime(double *usertime, double *systime, double *walltime);



double utime0, stime0, wtime0,utime1, stime1, wtime1;

int binarySearch(int Arr[], int l, int r, int x);
//int arr[], int n, int x
void *exponentialSearch(void * arg)
{
    //printf("llego a binary %d", ((Elem)arg)->n1);
    //((Elem)arg)->n1=50;
    
    int min=0;
    // If x is present at firt location itself
    if (((Elem)arg)->arr1[0] == ((Elem)arg)->x)
        return 0;
 
    // Find range for binary search by
    // repeated doubling
    int i = 1;
    while (i < ((Elem)arg)->n1 && ((Elem)arg)->arr1[i] <= ((Elem)arg)->x)
        i = i*2;
    
    if(i<=((Elem)arg)->n1-1) min=i;
    else min=((Elem)arg)->n1-1;
    
    
    //  Call binary search for the found range.
    //encargar a dos hilos de la busqeuda L - C -R
    uswtime(&utime0, &stime0, &wtime0);
    ((Elem)arg)->result=binarySearch(((Elem)arg)->arr1, i/2, min, ((Elem)arg)->x);
    uswtime(&utime1, &stime1, &wtime1);
}

int binarySearch(int arr[], int l, int r, int x)
{
    
    if (r >= l)
    {
        int mid = l + (r - l)/2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then it
        // can only be present n left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
    }
 
    // We reach here when element is not present
    // in array
    return -1;
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
	printf("Tiempo: %.10f\n", wtime1 - wtime0);
}
 


int main(int argc, char *argv[]){
    
    //int arr[]={2,3,4,10,40};
    pthread_t hilo0, hilo1, hilo2;
    Elem e1=malloc(sizeof(Elem));
    
    e1->arr1=(int *)malloc(sizeof(int)*10000000);
    //e1->n1=sizeof(e1->arr1)/sizeof(e1->arr1[0]);
    
    int cantidad=atoi(argv[1]);//cantidad de numeros a leer
    //int *arr=(int *)malloc(sizeof(int)*10000000);
   // int n = sizeof(arr)/sizeof(arr[0]);
    int var=0;
    e1->n1=cantidad;

    for(int j = 0; j < cantidad ; j++){
		scanf("%d",&var);
		e1->arr1[j]=var;	
    }
    //7772647
    e1->x=119847072;

    //****************************
    //Lamada al hilo y funciones de tiempo
    //*************************

    //uswtime(&utime0, &stime0, &wtime0);
    //int result = exponentialSearch(e1->arr1, e1->n1, x);
    pthread_create(&hilo0, NULL, exponentialSearch, e1);
    //uswtime(&utime1, &stime1, &wtime1);
    
    pthread_join(hilo0, NULL);
    
    //printf("Soy el chafa\n");
    printf("\n%d", e1->result);
    (e1->result == -1)? printf(" Elemento %d isnt in array\n", e1->x)
                    : printf(" Element %d is at %d index \n",e1->x, e1->result);


    ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
    

    return 0;
}


