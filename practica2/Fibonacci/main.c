
//Compilación: "gcc main.c tiempo.c
//Ejecución: "./script.sh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

//Constantes del programa
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

//Funciones
int busquedaFibonacci(int A[], int n, int x);

//Programa Principal
int main(int argc, char *argv[])
{
	//Variables 
	int n;  //n determina el tamaño del algorito dado por argumento al ejecutar
	int i, j, bandera = 0; //Variables para loops
	int *A;
	int numeros[20] = {322468, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 129539003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
	n = atoi(argv[1]);

	int encontrados;
	
	//Recepción y decodificación de argumentos
	A = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
	}

	//Algoritmo
	for (i = 0; i < 20; i++)
	{
		double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
		uswtime(&utime0, &stime0, &wtime0);
		encontrados = busquedaFibonacci(A, n - 1, numeros[i]);

		if (encontrados != -1)
		{
			printf("Se encontro el numero %d\n", numeros[i]);
		}
		else
		{
			printf("No se encontro %d", numeros[i]);
		}


		//Evaluar los tiempos de ejecución
		uswtime(&utime1, &stime1, &wtime1);

		//Cálculo del tiempo de ejecución del programa
		printf("\nTiempo: %.10f\n", wtime1 - wtime0);
		printf("--------------------------------------------------------------------------------------\n");
		//Terminar programa normalmente
	}

	return 0;
}


//Busqueda Fibonacci, busca el valor de x en el arreglo

int busquedaFibonacci(int A[], int n, int x)
{
	// Inicializamos los numeros de fibonacci
	int fibMMm2 = 0;			  // (m-2)'th número de fibonacci
	int fibMMm1 = 1;			  // (m-1)'th número de fibonacci
	int fibM = fibMMm2 + fibMMm1; // m número de fibonacci

	// fibM Almacenara el menor número de fib.
	while (fibM < n)
	{
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}

	// se marca el rango de eliminacion.
	int offset = -1;

	// Cuando fibM se convierte en 1, fibMm2 se convierte en 0 
	while (fibM > 1)
	{
		// Busca ubicacion valida
		int i = MIN(offset + fibMMm2, n - 1);

		// Comprueba si fibMm2 es valido
		if (A[i] < x)
		{
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}

		// si x es mayor que el indice de fibMm2,se corta el subarreglo i+1 
		else if (A[i] > x)
		{
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}

		// elemento encontrado, retorna indice
		else
			return i;
	}

	// compara el último elemento con x
	if (fibMMm1 && A[offset + 1] == x)
		return offset + 1;

	// Si no encuentra el elemento retorna -1
	return -1;
}
