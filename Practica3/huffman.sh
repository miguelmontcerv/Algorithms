#!/bin/bash
gcc 'practica3.c' -o 'practica3' -w

./practica3 0 texto.txt texto_comp.txt caracteres1.txt >registro.txt
./practica3 0 cancion.mp3 cancion_comp.txt caracteres2.txt >>registro.txt
./practica3 0 imagen1.bmp imagen1_comp.txt caracteres3.txt >>registro.txt
./practica3 0 imagen2.jpg imagen2_comp.txt caracteres4.txt >>registro.txt
./practica3 0 pdf.pdf pdf_comp.txt caracteres5.txt >>registro.txt
./practica3 0 word.docx word_comp.txt caracteres6.txt >>registro.txt
./practica3 0 imagen3.png imagen3_comp.txt caracteres7.txt >>registro.txt

./practica3 1 caracteres1.txt texto_comp.txt texto_desc.txt >>registro.txt
./practica3 1 caracteres2.txt cancion_comp.txt cancion_desc.mp3 >>registro.txt
./practica3 1 caracteres3.txt imagen1_comp.txt imagen1_desc.bmp >>registro.txt
./practica3 1 caracteres4.txt imagen2_comp.txt imagen2_desc.jpg >>registro.txt
./practica3 1 caracteres5.txt pdf_comp.txt pdf_desc.pdf >>registro.txt
./practica3 1 caracteres6.txt word_comp.txt word_desc.docx >>registro.txt
./practica3 1 caracteres7.txt imagen3_comp.txt imagen3_desc.png >>registro.txt