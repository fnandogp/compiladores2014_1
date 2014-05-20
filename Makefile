all:
	gcc main.c -o trab3 hash.c automato.c analisadorLexico.c tabelaSintatico.c tadLista.c tadPilha.c analisadorSintatico.c

clean:
	rm trab3
