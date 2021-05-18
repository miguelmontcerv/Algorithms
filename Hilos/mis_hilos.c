#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *funcion(void *argumento);
int numero_hilos = 0;
int main(int argc, char const *argv[])
{
	int num_hilos, maxima_cuenta;
	/*printf("Indique el numero de hilos y el conteo max de cada uno:\n");
	scanf("%d",&num_hilos);
	scanf("%d",&maxima_cuenta);*/
	pthread_t hilo1,hilo2;	
	int argumento;

	printf("Introduce la cuenta del primer hilo\n");
	scanf("%d",&argumento);

	if(pthread_create (&hilo1, NULL, funcion,(void*)argumento) != 0 )
		{ printf("Error\n"); return -1; }

	printf("Introduce la cuenta del segundo hilo\n");
	scanf("%d",&argumento);

	if(pthread_create (&hilo2, NULL, funcion,(void*)argumento) != 0 )
		{ printf("Error\n"); return -1; }

	
	pthread_join(hilo2,NULL);
	pthread_join(hilo1,NULL);

	funcion((void*)1);

return 0;
}

void *funcion(void *argumento){
	numero_hilos ++;
	printf("Hola desde el hilo %d\n", numero_hilos);
	for (int i = 0; i < (int)argumento; ++i)
	{
		printf("\tCuenta %d\n",i);
	}
}