
 
#ifndef __COLACODIFICACION_H__
#define	__COLACODIFICACION_H__

typedef struct nodoCola {
	char valor;
	struct nodoNodoCola * siguiente;
}NodoCola;

typedef struct colaCodificacion {
	NodoCola * inicio;
	NodoCola * final;
}ColaCodificacion;

void iniciaCola(ColaCodificacion * cola);

void formaCodificacion(ColaCodificacion * cola, char valor);}

char atiendeCola(ColaCodificacion * cola);

void atiendeTodos(ColaCodificacion * cola);

#endif	/* __COLACODIFICACION_H__ */