all:
	gcc main.c utils.c server.c -o server

debug:
	g++ -g main.c utils.c server.c -o debug

clean:
	rm debug server *.o
