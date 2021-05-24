#!/bin/bash
gcc 'practica3.c' -o 'practica3'

./practica3 texto.txt comprimido.txt salida.txt >registro.txt
./practica3 imagen.bmp comprimido2.txt salida2.txt >>registro.txt
./practica3 imagen2.bmp comprimido3.txt salida3.txt >>registro.txt

./practica3 -d salida.txt comprimido.txt descomprimido.txt >>registro.txt
./practica3 -d salida2.txt comprimido2.txt imagen_desc.bmp >>registro.txt
./practica3 -d salida3.txt comprimido3.txt imagen2_desc.bmp >>registro.txt