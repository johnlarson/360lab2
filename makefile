all:
	gcc main.c utils.c server.c request.c response.c -o server

debug:
	gcc -g main.c utils.c server.c request.c response.c -o debug

clean:
	rm debug server *.o
