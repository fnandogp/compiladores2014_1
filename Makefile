all:
	gcc main.c -o trab2 hash.c automato.c analisadorLexico.c

clean:
	rm trab2