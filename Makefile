all:
	gcc main.c -o trab2 hash.c automato.c analisadorLexico.c tabelaSintatico.c tadPilha.c analisadorSintatico.c

clean:
	rm trab2