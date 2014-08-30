gcc -g -c Filme.c Usuarios.c Main.c Sugestoes.c Arquivo.c Lista.c Nodo.c -std=c99 -Wall -pg -O0

gcc -g -o Programa.exe Lista.o Nodo.o Filme.o Usuarios.o Main.o Sugestoes.o Arquivo.o -std=c99 -Wall -pg -O0
