
#include <stdio.h>
#include <stdlib.h>
#include "frecuencias.h"
#include "codificacion.h"
#include "bits.h"
#include "tiempo.h"

void imprimeTablaFrecuencias(Frecuencia * frecuencias, int length, int padding, int byteOrginal,const char ruta[]);

// Definimos el tamaño del buffer
#define BUFFER 1024 
// Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];
// Nuestras variables para los archivos
FILE * entrada;
FILE * tablaFrecuenciasArchivo;
FILE * out;

// Variables para controlar la medición de tiempos
double 	usrtime11, systime11, walltime11,
		usrtime21, systime21, walltime21,
		real, user, sys, cpuwall;

/*
 * 
 */
int main(int argc, char** argv) {
	// Salida
	char * salida;
	char * codificado;
    int leidos;
	long leidosTotal = 0;
	long bytesTotal = 0;
	int bitsEscritosReal = 0;
	Frecuencia * v;
	

	if(argv[1][0] == '-' && argv[1][1] == 'd') // Decompresión
	{
		// Iniciamos la medición de tiempos
		uswtime(&usrtime11, &systime11, &walltime11);
		
		// Apertura de los flujos
		tablaFrecuenciasArchivo = fopen(argv[2],"r"); // Abrimos la tabla de frecuencias
		entrada = fopen(argv[3],"rb"); // Abrimos el archivo comprimido
		out = fopen(argv[4],"wb"); // Abrimos un flujo de salida para guardar el nuevo archivo
		
		if(out == NULL) printf("Error\n");
		if(tablaFrecuenciasArchivo == NULL) printf("Error\n");
		if(entrada == NULL) printf("Error\n");
		
		// Variables auxiliares para la descompresión
		long size;
		char caracter;
		int apariciones;
		int padding;
		int tamanoOriginal;
		int numeroCaracteres;
		char basura;
		
		// Obtenemos el tamaño de nuestro archivo codificado
		fseek (entrada,0,SEEK_END);
		size = ftell(entrada);
		rewind(entrada);
		
		// Leemos información importante sobre el archivo de salida
		fscanf(tablaFrecuenciasArchivo,"N:%d",&numeroCaracteres); // El número de caracteres distintos en el archivo
		fscanf(tablaFrecuenciasArchivo,"%c",&basura); // Salto de línea
		fscanf(tablaFrecuenciasArchivo,"P:%d",&padding); // El número de bits "basura"
		fscanf(tablaFrecuenciasArchivo,"%c",&basura); // Salto de línea
		fscanf(tablaFrecuenciasArchivo,"T:%d",&tamanoOriginal); // El tamaño original del archivo comprimido
		
		salida = (char *)malloc(sizeof(char)*tamanoOriginal);
		codificado = (char *)malloc(sizeof(char)*size);
		
		// Reservamos el espacio para el arreglo de frecuencias
		v = (Frecuencia *)malloc(sizeof(Frecuencia) * numeroCaracteres);
		
		// Lectura del archivo de la tabla de frecuencias para generar un arreglo
		for(leidos = 0; leidos < numeroCaracteres; leidos++){
			fscanf(tablaFrecuenciasArchivo,"%c",&basura); // Salto de línea
			// Obtenemos los caracteres y su número de apariciones, para que a partir de ellos
			// se cree el árbol de decodificación
			fscanf(tablaFrecuenciasArchivo,"%c|%d",&caracter,&apariciones);
			Frecuencia f;
			f.caracter = caracter;
			f.apariciones = apariciones;
			v[leidos] = f;
		}
		
		// Cerramos el flujo de la tabla de frecuencias
		fclose(tablaFrecuenciasArchivo);
		
		// Ordenamos el arreglo por las apariciones
		ordenaFrecuenciasPorAparicion(v, numeroCaracteres);
		// Creamos el árbol de codificación
		creaArbolCodificacion(v,numeroCaracteres);
		
		// Leemos el archivo codificado
		fread(codificado,sizeof(char),size,entrada);
		fclose(entrada); // Cerramos el flujo de salida
		decodificaBits(codificado, (size*8)  - padding, salida);
		
		fwrite(salida,sizeof(char),tamanoOriginal,out); // Escribimos el archivo final
		fclose(out); // Cerramos el flujo
		
		// Concluimos la medición de tiempos
		uswtime(&usrtime21, &systime21, &walltime21);
		
		calculaTiempos(&usrtime11, &systime11, &walltime11,
							&usrtime21, &systime21, &walltime21,
							&real, &user, &sys, &cpuwall);
		
		// Imprimimos información 
		printf("descompresion|%s|exito|%ld|%ld|%s\n",argv[2],leidosTotal,bytesTotal, argv[3]);
		
	}

	else {
		// Iniciamos la medición de tiempos		
		ListaFrecuencia f;
		f.inicio = NULL;
			
		entrada = fopen(argv[1], "rb");		
		uswtime(&usrtime11, &systime11, &walltime11);
		
		if (entrada == NULL) {
			perror("No se puede abrir el fichero de entrada");
			return -1;
		}
				
		// Este primer ciclo se encarga de la lectura para generar el árbol
		do {
			// Leemos el archivo hasta que ya no haya que leer
			// fread nos devuelve la cantidad de datos leídos
			leidos = fread(buffer, sizeof(char), BUFFER, entrada);
			leidosTotal += leidos;
			// Insertamos las frecuencias en nuestra tabla
			generaFrecuencias(&f,buffer,leidos);			
			// Cuando no se hayan ocupado todos los espacios en la lectura
			// sabemos que ya se terminó de leer el archivo
		}while(leidos == BUFFER);
				
		// Reservamos memoria suficiente para almacenar el archivo codificado
		salida = (char *)malloc(sizeof(char) * leidosTotal);		
		// Obtenemos el arreglo de frecuencias
		v = vectorFrecuencias(&f);		
		// Generamos la codificación mediante la llamada a este método
		creaArbolCodificacion(v,f.length);				
		// Regresamos al inicio del archivo
		leidos = 0;
		rewind(entrada);

		int resultadoEscritura = 0;
		// El segundo ciclo lee el archivo para generar la codificación
		do {
			int iaux = 0;
			// Leemos el archivo hasta que ya no haya que leer
			// fread nos devuelve la cantidad de datos leídos
			leidos = fread(buffer, sizeof(char), BUFFER, entrada);
			// Por cada caracter leído vamos a modificar los bits dentro de este ciclo
			for(iaux = 0; iaux < leidos; iaux++){
				resultadoEscritura = escribeBits(salida,leidosTotal*8,bitsEscritosReal, buffer[iaux], v, f.length);
				if(resultadoEscritura < 0) break;
				bitsEscritosReal += resultadoEscritura;
			}
			// Cuando no se hayan ocupado todos los espacios en la lectura
			// sabemos que ya se terminó de leer el archivo
			// Cuando no se puedan segir escribiendo bits en el arreglo de salida, rompemos el ciclo
		}while(leidos == BUFFER && resultadoEscritura >= 0);
		
		fclose(entrada); // Cerramos la entrada
		
		bytesTotal = (bitsEscritosReal / 8); // Determinamos cuantos bytes ocupará el nuevo archivo
		int padding = bytesTotal % 8;
		if(padding > 0)
			bytesTotal++;
		
		
		out = fopen(argv[2],"w"); // Abrimos un flujo de salida para guardar el nuevo archivo
		fwrite(salida,sizeof(char),bytesTotal,out); // Escribimos el arreglo de chars, el cual fue modificado para contener la información
		fclose(out); // Cerramos el flujo
		
		// Imprimimos la tabla de frecuencias a un archivo para conservarla
		imprimeTablaFrecuencias(v,f.length, padding, leidosTotal ,argv[3]);
		
		// Concluimos la medición de tiempos
		uswtime(&usrtime21, &systime21, &walltime21);
		
		calculaTiempos(&usrtime11, &systime11, &walltime11,
							&usrtime21, &systime21, &walltime21,
							&real, &user, &sys, &cpuwall);
		
		// Impresión de información relevante de la compresión [Académico]
		if(resultadoEscritura >= 0)
			printf("compresion|%s|exito|%ld|%ld|%s\n",argv[1],leidosTotal,bytesTotal, argv[2]);
		else
			printf("compresion|%s|fallo|%ld|%ld|%s\n",argv[1],leidosTotal,bytesTotal, argv[2]);
	}
	
	
    return (EXIT_SUCCESS);
}

/**
 * Función para imprimir la tabla de frecuencias a un archivo especificado
 * @param frecuencias La tabla de frecuencias en el archivo
 * @param ruta La ruta en la que se debe guardar
 */
void imprimeTablaFrecuencias(Frecuencia * frecuencias, int length, int padding, int byteOrginal,const char ruta[]) {
    tablaFrecuenciasArchivo = fopen(ruta,"w");
    if (tablaFrecuenciasArchivo == NULL) {
        perror("No se puede abrir archivo");
    }
	fprintf(tablaFrecuenciasArchivo,"N:%d\n", length);
	fprintf(tablaFrecuenciasArchivo,"P:%d\n", padding);
	fprintf(tablaFrecuenciasArchivo,"T:%d\n", byteOrginal);
	// Impresión de las frecuencias al archivo especificado
	int i;
    for (i = 0; i < length; i++) {
        fprintf(tablaFrecuenciasArchivo,"%c|%d\n"
                , (int) frecuencias[i].caracter
                , frecuencias[i].apariciones
				/*, frecuencias[i].codigo*/);
    }
    fclose(tablaFrecuenciasArchivo);
}

