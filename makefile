all:
	gcc -w main.c utils.c server.c request.c response.c fileserving.c -o server

db:
	gcc -g main.c utils.c server.c request.c response.c fileserving.c -o debug

clean:
	rm debug server *.o
