//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Programa principal
void main(int argc, char *argv[]){
	/* Variables para medir el tiempo */
	double utime0, stime0, wtime0,utime1, stime1, wtime1;

	//Numero de numeros que se ordenarán
	if(argc!=2) 
		exit(1);
	
	/* Variables del algoritmo */
	int n = atoi(argv[1]);
	int b,i,temp;
	/*Se divide entre 2 para saber el numero de saltos
	Se trunca el entero para que sea exacto*/
	int k = trunc(n/2);

	printf("\tShell para %i numeros\n",n);
	
	/* Crear arreglo de numeros de forma dinamica */
	int *A;
	A = (int*)malloc(n*sizeof(int));

	/* Obtener datos del archivo */
	for(i = 0; i < n; i++)
		scanf("%d",&A[i]);
	

	while(k>=1)
	{
		//Mientras k sea mayor o igual a 1 se hará el procedimiento
		b=1;
		while(b!=0)
		{
			b=0;
			/*Cuando no hay más por "ordenar en ese paso" continua con la
			siguiente k/2*/
			for (i=k;i<=n-1;i++)
			{
				/*Se compara cada uno dependiendo del salto
				y si es menor el de la derecha, se cambia*/
				if(A[i-k] > A[i])
				{
					//En caso de cumplirse, se cambian
					temp = A[i];
					A[i] = A[i-k];
					A[i-k] = temp;
					b++;
				}
			}
		}
		//Se van partiendo las distancias para hacer las comparaciones
		k=trunc(k/2);
		//Cuando k=1, se hace un ordenamiento por inserción.
	}

	for(i=0;i<27;i++)
		printf("*");

	printf("\n");


	exit(0);
}