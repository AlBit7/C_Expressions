@echo off

:: definisco le variabili
@REM set PATH=%0\..\
@REM cd %PATH%
set CC=gcc
set out=output

:: creo gli object files (".o", uno e zero)
%CC% -c stack.c
%CC% -c solvePostfix.c
%CC% -c infixToPostfix.c
%CC% -c main.c

:: linko tutti i file oggetto con le librerie necessarie
%CC% main.o infixToPostfix.o solvePostfix.o stack.o -o %out%

:: rimuovi tutti i file oggetto
del stack.o
del solvePostfix.o
del infixToPostfix.o
del main.o

:: esegue il programma
.\%out%.exe

