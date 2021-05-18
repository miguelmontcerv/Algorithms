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

typedef struct rangos{
    int l;
    int r;
}*Rangos;

typedef struct args{
    Elem e2;
    Rangos r1;
} *Args;


double utime0, stime0, wtime0,utime1, stime1, wtime1;

void uswtime(double *usertime, double *systime, double *walltime);

void *binarySearch(void *arg);
//int arr[], int n, int x
void *exponentialSearch(void * arg)
{
    pthread_t hilo1, hilo2;
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
    
    Args parte1=malloc(sizeof(Args));
    Args parte2=malloc(sizeof(Args));

    parte1->r1=malloc(sizeof(Rangos));
    parte2->r1=malloc(sizeof(Rangos));
    

    parte1->e2=&(*((Elem)arg));
    parte2->e2=&(*((Elem)arg));


    int div=i/2;

    int mitad= div + (min - div)/2;




    parte1->r1->l=div;
    parte1->r1->r=mitad;

    parte2->r1->l=mitad;
    parte2->r1->r=min;


    printf("intervalos [%d,%d]  [%d, %d]",div,mitad,mitad, min );
    //  Call binary search for the found range.
    //encargar a dos hilos de la busqeuda L - C -R
    // ((Elem)arg)->result=

    //hilo1
    uswtime(&utime0, &stime0, &wtime0);
    

    pthread_create(&hilo1, NULL, binarySearch, parte1);
    
    pthread_create(&hilo2, NULL, binarySearch, parte2);
    uswtime(&utime1, &stime1, &wtime1);
   //binarySearch(((Elem)arg)->arr1, i/2, min, ((Elem)arg)->x);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
}


//argumentos int arr[], int l, int r, int x
void *binarySearch(void *arg)
{
    Args aux=&(*((Args)arg));
    int mid;

    int le=aux->r1->l;
    int ri=aux->r1->r;
    while (ri >= le)
    {
         mid = le + (ri - le)/2;
 
        // If the element is present at the middle
        // itself
        if ((aux->e2->arr1[mid]) == (aux->e2->x)){
            ((Args)arg)->e2->result=mid;
            
            //printf("termine %d", mid);
            return 0;
        }
            
 
        // If element is smaller than mid, then it
        // can only be present n left subarray
        if (aux->e2->arr1[mid] > aux->e2->x){
            ri=mid-1;
            //return binarySearch(arr, l, mid-1, x);
        }
        else{
            le=mid+1;
            //return binarySearch(arr, mid+1, r, x);
        }        
    
        // Else the element can only be present
        // in right subarray

        
    }
    // We reach here when element is not present
    // in array
    return 0;
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
    pthread_t hilo0;
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

    e1->x=10406;

    //****************************
    //Lamada al hilo y funciones de tiempo
    //*************************

    //uswtime(&utime0, &stime0, &wtime0);
    //int result = exponentialSearch(e1->arr1, e1->n1, x);
    //pthread_create(&hilo0, NULL, exponentialSearch, e1);
    exponentialSearch(e1);
    //pthread_join(hilo0, NULL);

    //uswtime(&utime1, &stime1, &wtime1);
    
    
    (e1->result ==-1)? printf("Elemento %d isnt in array\n", e1->x)
                    : printf("Element %d is at %d index \n",e1->x, e1->result);

    ImprimirTiempos(utime0, stime0, wtime0,utime1, stime1, wtime1);
    

    return 0;
}


