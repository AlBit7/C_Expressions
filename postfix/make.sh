#!/usr/bin/env bash

# definisco il compilatore da usare
CC="gcc"
out="output"

# creo gli object files (".o" uno e zero)
$CC -c main.c
$CC -c infixToPostfix.c
$CC -c solvePostfix.c
$CC -c stack.c

# linko tutti i file oggetto con le librerie necessarie
$CC main.o infixToPostfix.o solvePostfix.o stack.o -lm -o %out

# elimino tutti i file oggetto
rm stack.o
rm solvePostfix.o
rm infixToPostfix.o
rm main.o

# esegue il programma
./$out
