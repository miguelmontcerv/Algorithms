#!/bin/bash
gcc 'practica3.c' -o 'practica3' -w

./practica3 0 texto.txt texto_comp.txt caracteres1.txt >registro.txt
./practica3 0 cancion.mp3 cancion_comp.txt caracteres2.txt >>registro.txt
./practica3 0 imagen1.bmp imagen1_comp.txt caracteres3.txt >>registro.txt
./practica3 0 imagen2.jpg imagen2_comp.txt caracteres4.txt >>registro.txt
./practica3 0 pdf2.pdf pdf_comp.txt caracteres5.txt >>registro.txt
./practica3 0 word.docx word_comp.txt caracteres6.txt >>registro.txt
./practica3 0 imagen3.png imagen3_comp.txt caracteres7.txt >>registro.txt
