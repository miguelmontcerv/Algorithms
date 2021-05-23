 # Las instrucciones que comienzan con 'w' están hechas
# para la funcionalidad en plataformas Windows
#run: ejecutable
#	./run.sh
#wrun: ejecutable 
#	./run.bat
ejecutable: main.c frecuencias.o bits.o colacodificacion.o codificacion.o
	gcc main.c -w frecuencias.o bits.o codificacion.o colacodificacion.o
frecuencias.o:
	gcc -c frecuencias.c -w
codificacion.o: 
	gcc -c codificacion.c -w
colacodificacion.o:
	gcc -c colacodificacion.c -w
bits.o:
	gcc -c bits.c -w
clean:
	rm frecuencias.o
	rm colacodificacion.o
	rm codificacion.o
	rm bits.o
	#rm a.out	
#wclean:
#	rm frecuencias.o
#	rm colacodificacion.o
#	rm codificacion.o
#	rm bits.o
#	rm a.exe	

