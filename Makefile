#compila o programa e executa ao mesmo tempo
all:
	gcc -Wall *.c -o main
	./main
	
#remove o arquivo executável
clean:
	rm -f main