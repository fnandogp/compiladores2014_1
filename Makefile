all:
	gcc main.c -o trab4 hash.c automato.c analisadorLexico.c tabelaSintatico.c tadLista.c tadPilha.c analisadorSintatico.c

clean:
	rm trab4
