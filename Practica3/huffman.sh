#!/bin/bash
gcc 'practica3.c' -o 'practica3'

./practica3 texto.txt comprimido.txt salida.txt >registro.txt
./practica3 cancion.mp3 comprimido2.txt salida2.txt >>registro.txt
./practica3 imagen.bmp comprimido3.txt salida3.txt >>registro.txt
./practica3 imagen2.jpg comprimido4.txt salida4.txt >>registro.txt
./practica3 pdf.pdf comprimido5.txt salida5.txt >>registro.txt

./practica3 -1 salida.txt comprimido.txt texto_desc.txt >>registro.txt
./practica3 -1 salida2.txt comprimido2.txt cancion_desc.mp3 >>registro.txt
./practica3 -1 salida3.txt comprimido3.txt imagen_desc.bmp >>registro.txt
./practica3 -1 salida4.txt comprimido4.txt imagen2_desc.jpg >>registro.txt
./practica3 -1 salida5.txt comprimido5.txt pdf_desc.pdf >>registro.txt