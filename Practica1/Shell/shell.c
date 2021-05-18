//Algoritmo de Shell
//Equipo:
//Martinez Partida Jair Fabian
//Martinez Rodriguez Alejandro
//Monteros Cervantes Miguel Angel
//Ramirez Cotonieto Luis Fernando

//Inicio de librerias//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tiempo.h"

//Fin de librerias//

//Programa Principal//
void main (int args, char *argv[]){
  //Variables para medir tiempo
  double utime0, stime0, wtime0, utime1, wtime1;

  //Numeros que se ordenasn
  if(argc!=2)
    exit(1);

    //Variables
    int n=atoi(argv[1]);
    int b,i,temp;
    int k=trunc(n/2); // Dividimos entre 2 para conocer los saltos
                     // Se trunca el entero para la exactitud
    printf("Proceso de shell en %i digitos\n",n);

    //Creacion de arreglo de forma dinamica
    int *A;
    A= (int*)malloc(n*sizeof(int));
    //Para obtener datos
    for(i=0; i<n; i++)
        scanf("%d",&A[i]);
    //Inicio de conteo de tiempo
    uswtime(&utime0, &stime0, &wtime0);
    //Fin de conteo de tiempo

  //Algoritmo de shell propuesto
  while(k>=1){ //Mientras k sea igual o mayor a 1, el proceso se llevara a cabo
    b=1;
    while (b!=0) {
      b=0; //Cuando ya no haya nada que ordenar, continua con k/2
      for (i=k; i<n-1;i++)
      {
        if(A[k-1]>A[i]){//Se compara dependiendo el salto, cmabia si el del
          //la derecha es menor
          temp=A[i];
          A[i]=A[i-k];
          A[i-k]=temp;
          b++;
        }
      }
    }
    k=trunc(k/2);
    //Si k=1 se realiza un ordenamiento de insercion
  }
  //Tiempos de ejecucion
  uswtime(&utime1, &stime1, &wtime1);
  //Calculo de tiempo de ejecucion
  printf("-----------:)----------\n");
  printf("Tiempo real %.10f s\n", wtime1 - wtime0);
  printf("Tiempo de procesamiento %.10fs\n", utime1 - utime0);
  printf("Tiempo en acciónes de sistema (E/S) %.10fs\n", stime1 - stime0);
  printf("CPU/Wall %.10f%% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtim e0));
  printf("-----------:)----------\n");
  //tiempos de manera exponencial
  printf("-----------:)----------\n");
  printf("Tiempo real %.10e s\n", wtime1 - wtime0);
  printf("Tiempo de procesamiento %.10es\n", utime1 - utime0);
  printf("Tiempo en acciónes de sistema (E/S) %.10es\n", stime1 - stime0);
  printf("CPU/Wall %.10f%% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtim e0));
  printf("-----------:)----------\n");
  //
  for(i=0;i<27;i++)
    printf("\n");

    exit(0);
}
