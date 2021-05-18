#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

struct Nodo
{
	char caracter;
	int frecuencia;
	struct Nodo *izq;
	struct Nodo *der;
};

char *leerArchivo(char *);
char **conteo(char*);
char **ordenamiento(char**);
void crearArreglo(struct Nodo*, char **);

int limite,n_caracteres_dif;
int *numOrdenados; 

void main(int argc, char **argv[])
{
	//Leemos el archivo que el usuario quiera desde la linea de comando al ejecutar el programa
	char *archivon = (char *)malloc(sizeof(char)*20);
	//Ejemplo: ./a.out texto.txt
	archivon = (char *) argv[1];


	//Convertimos lo que haya dentro del archivo en una cadena, así podremos contar la frecuencia de cada caracter
	char *cadena = leerArchivo(archivon);
	
	//En clase vimos una tabla, de 2 x 'Cantidad de caracteres diferente' es por eso que utilizo un puntero doble
	char **matriz;
	
	//Le asigno el valor de retorno de la función conteo, que como su nombre lo dice, cuenta la cantidad de caracteres
	// y los ordena, al final, solo se utiliza una de las columnas de la matriz, la otra solo fue auxiliar, hazta aquí todo bien 
	matriz = conteo(cadena);

	//Imprimimos los caracteres ordenados de menor a mayor con su respectiva cantidad de concurrencias
	//Ejemplo: VALOR DE ENTRADA: "Hola Hola mundo de los algoritmos"
	/*  SALIDA: 	1 1 1 1 1 1 1 2 2 2 2 3 4 5 6
					n g e u t r i s H m d a l   o	*/
	for (int i = 0; i < n_caracteres_dif; ++i) printf("%d ",*(numOrdenados + i)); printf("\n");
	for (int i = 0; i < n_caracteres_dif; ++i) printf("%c ",*(*(matriz)+i)); printf("\n\n");

	//Creamos el arreglo de estructuras, sus apuntadores a hijos estan vacios, por que es el primer arreglo
	struct Nodo *arreglo;
	crearArreglo(arreglo, matriz);

	//A PARTIR DE AQUI NO SE COMO PASAR A CÓDIGO EL ALGORITMO
	//Estoy utilizando apuntadores simples, pero creo que tendria que utilizar dobles, ya que es un arreglo de apuntadores a nodos
	//No estoy muy seguro y esa es mi principal pregunta: *¿CÓMO HAGO EL ARREGLO DE ARBOLES?*

	
}

void crearArreglo(struct Nodo *arreglo, char **matriz){
	arreglo = (struct Nodo*) malloc(sizeof(struct Nodo)*n_caracteres_dif);

	for (int i = 0; i < n_caracteres_dif; ++i)
	{
		arreglo[i].caracter = *(*(matriz)+i);
		arreglo[i].frecuencia = *(numOrdenados + i);
		arreglo[i].izq = NULL; arreglo[i].der = NULL;
	}
	for (int i = 0; i < n_caracteres_dif; ++i) printf("%c: %d  ",arreglo[i].caracter,arreglo[i].frecuencia); printf("\n");		
}

char *leerArchivo(char *archivon){	
	int fd,i = 0;
	char c;

	fd = open(archivon,O_RDONLY);

	if(fd!=-1)
	{
		for(;read(fd,&c,sizeof(c)!=0);i++);					
		printf("Cantidad de caracteres: %d\n",i);
		close(fd);

		char *cadena = (char *)malloc(sizeof(char)*i);

		fd = open(archivon,O_RDONLY);
		i = 0;
		for(;read(fd,&c,sizeof(c)!=0);i++)			
			*(cadena + i) = c;
		close(fd);
		limite = i;
		i = 0;
		return cadena;
		
	} else	printf("El archivo no existe\n");
}

char **conteo(char *cadena){
	char **matriz = (char **)malloc(sizeof(char*)*2);
	matriz[0] = (char *)malloc(sizeof(char)*limite); 
	matriz[1] = (char *)malloc(sizeof(char)*limite);

	for(int i = 0; i < limite; ++i){ *(*(matriz)+i) = '\0'; *(*(matriz+1)+i) = '\0';}

	int cat = 0;
	int contador = 0;
	for (int i = 0; i < limite; ++i)
	{
		contador = 0;
		if(*(cadena + i) != '\0'){
			contador++;
			*(*(matriz)+cat) = *(cadena + i);
			*(cadena + i) = '\0';
			for (int j = i; j < limite; ++j)
				if(*(cadena + j) == *(*(matriz)+cat)){
					contador++;
					*(cadena + j) = '\0';
				}
			*(*(matriz+1)+cat) = contador + '0';
			cat++;								
		}			
	}
	n_caracteres_dif = cat;

	char **matriz2 = ordenamiento(matriz);

	return matriz;

}

char **ordenamiento(char **matriz){
	numOrdenados = (int *) malloc(sizeof(int)*n_caracteres_dif);
	for (int j = 0; j < n_caracteres_dif; ++j)
			*(numOrdenados + j) = *(*(matriz+1)+j) - 48;
	
	//Ordenar numOrdenados
	int n = n_caracteres_dif;
	int b,i,temp;
	char tempc;
	int k = trunc(n/2);

	while(k>=1)
	{
		b=1;
		while(b!=0)
		{
			b=0;	
			for (i=k;i<=n-1;i++)
			{		
				if(numOrdenados[i-k] > numOrdenados[i])
				{					
					temp = numOrdenados[i];
					tempc = *(*(matriz)+i);
					numOrdenados[i] = numOrdenados[i-k];
					*(*(matriz)+i) = *(*(matriz)+(i-k));
					numOrdenados[i-k] = temp;
					*(*(matriz)+(i-k)) = tempc;
					b++;
				}
			}
		}
		k=trunc(k/2);
	}	

	return matriz;
}