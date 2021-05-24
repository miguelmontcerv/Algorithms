#ifndef __PRACTICA3_H__
#define	__PRACTICA3_H__

#include<stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

#define PESOBIT(bpos) 1<<bpos
#define COGEBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)
#define BYTE 8

typedef struct frecuencia{
    char caracter;
    int apariciones;
	char * codigo;
}Frecuencia;

typedef struct nodoFrecuencia{
    Frecuencia frecuencia;
    struct nodoFrecuencia * siguiente;
}NodoFrecuencia;

typedef struct listaFrecuencia{
    NodoFrecuencia * inicio;
    int length;
}ListaFrecuencia;

typedef struct nodoArbol {
	Frecuencia * frecuencia;
	int peso;
	struct nodoArbol  * nodo0;
	struct nodoArbol  * nodo1;
	unsigned visitado : 1;
}NodoArbol;

typedef struct nodoCola {
	char valor;
	struct nodoCola * siguiente;
}NodoCola;

typedef struct colaCodificacion {
	NodoCola * inicio;
	NodoCola * final;
	int count;
}ColaCodificacion;

/**
 * Rellena una lista de frecuencias con los caracteres deseados
 * @param frecuencias La lista en la que se debe almacenar
 * @param caracteres El arreglo de caracteres que se quiere almacenar
 * @param length La longitud del arreglo
 */
void generaFrecuencias(ListaFrecuencia * frecuencias,char caracteres[], int length);

/**
 * Función interna para insertar o actualizar la frecuencia de un elemento
 * @param frecuencias
 * @param caracter
 */
void insertaFrecuencia(ListaFrecuencia * frecuencias, char caracter);

void imprimeTablaFrecuencias(Frecuencia * frecuencias, int length, int padding, int byteOrginal,const char ruta[]);

void reordenaArboles();
void generaUnicoArbol();
void ordenaVectorFrecuenciasPorCaracter(Frecuencia * frecuencias, int length);
void asignaCodificacion(Frecuencia * frecuencias, int length, ColaCodificacion * cola);
int buscaFrecuencia(Frecuencia * frecuencias, int inicio, int final, char c);
void obtieneCaminoR(NodoArbol * arbol, ColaCodificacion * cola);

/**
 * Función encargada de regresar un arreglo de frecuencias dada una lista de ellas
 * el arreglo resultante está ordenado de forma ascendete de acuerdo a sus apariciones
 * 
 */ 
Frecuencia * vectorFrecuencias(ListaFrecuencia * frecuencias);

void ordenaFrecuenciasPorAparicion(Frecuencia * vector, int length);

void creaArbolCodificacion(Frecuencia * frecuencias, int length);

int escribeBits(char * salida, int salidaLength, long pointer, char c, Frecuencia * frecuencias, int length);

void decodificaBits(char * codificado, long longitudCodificado, char * salida);

void iniciaCola(ColaCodificacion * cola);

void formaCodificacion(ColaCodificacion * cola, char valor);

void formaInicioCodificacion(ColaCodificacion * cola, char valor);

char atiendeCola(ColaCodificacion * cola);

void atiendeTodos(ColaCodificacion * cola);

/**
 * Función encargada de poner el bit elegido en 1
 * @param array El arreglo en el que queremos modificar
 * @param pos La posición del bit que queremos cambiar
 */ 
void pon1(char * array, int pos);

/**
 * Función encargada de poner el bit elegido en 0
 * @param array El arreglo en el que queremos modificar
 * @param pos La posición del bit que queremos cambiar
 */
void pon0(char * array, int pos);

/**
 * Función encargada de obtener el valor del bit en el arreglo
 * @param array El arreglo en el que queremos conocer
 * @param pos La posición del bit que queremos obtener
 */
int valorBit(char * array, int pos);

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
	printf("\n(%.3f s) ", wtime1 - wtime0);
}

// Definimos el tamaño del buffer
#define BUFFER 1024 

// Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];
// Nuestras variables para los archivos
FILE * entrada;
FILE * tablaFrecuenciasArchivo;
FILE * out;

// En este doble apuntador se almacenará la colección de frecuencias
NodoArbol ** bosqueHuffman;
int nodos;

// Variables para controlar la medición de tiempos
double 	usrtime11, systime11, walltime11,
		usrtime21, systime21, walltime21,
		real, user, sys, cpuwall;


#endif	/* __FRECUENCIAS_H__ */