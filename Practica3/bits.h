

#ifndef __BITS_H__
#define	__BITS_H__

#define PESOBIT(bpos) 1<<bpos
#define COGEBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)
#define BYTE 8

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
	

#endif	/* __BITS_H__ */
