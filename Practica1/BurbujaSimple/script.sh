#!/bin/bash
gcc 'burbujaSimple.c' -o 'burbujaSimple'

./burbujaSimple 100 <numeros10millones.txt >burbujaSimple.txt
./burbujaSimple 1000 <numeros10millones.txt >>burbujaSimple.txt
./burbujaSimple 5000 <numeros10millones.txt >>burbujaSimple.txt
./burbujaSimple 10000 <numeros10millones.txt >>burbujaSimple.txt
#./burbujaSimple 50000 <numeros10millones.txt >>burbujaSimple.txt
#./burbujaSimple 100000 <numeros10millones.txt >>burbujaSimple.txt