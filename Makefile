all:
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/automato.c" -o obj/Debug/automato.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/automatoLex.c" -o obj/Debug/automatoLex.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/estruturas.c" -o obj/Debug/estruturas.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/lexico.c" -o obj/Debug/lexico.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/main.c" -o obj/Debug/main.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/sintatico.c" -o obj/Debug/sintatico.o
	gcc -Wall -w -g  -c "/home/daniel/Área de Trabalho/compilador-master/xml_parse_lib/xml_parse_lib.c" -o obj/Debug/xml_parse_lib/xml_parse_lib.o
	g++  -o bin/Debug/compilador1 obj/Debug/automato.o obj/Debug/automatoLex.o obj/Debug/estruturas.o obj/Debug/lexico.o obj/Debug/main.o obj/Debug/sintatico.o obj/Debug/xml_parse_lib/xml_parse_lib.o   
