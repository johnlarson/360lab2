#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int startSocket(int port, int* hSocket, struct sockaddr_in* address);
void acceptLoop(int hSocket, struct sockaddr_in address);
void acceptConnection(int hSocket, struct sockaddr_in address);
void respondRequest(int hSocket);
void closeSocket(int hSocket);

void runserver(int port, char* dir) {
	int hSocket;
	struct sockaddr_in address;
	startSocket(port, &hSocket, &address);
	acceptLoop(hSocket, address);	
	closeSocket(hSocket);
}

int startSocket(int port, int* hSocket, struct sockaddr_in* address) {
	return 1;
}

void acceptLoop(int hSocket, struct sockaddr_in address) {
	while(1) {
		acceptConnection(hSocket, address);
		respondRequest(hSocket);
	}
}

void acceptConnection(int hSocket, struct sockaddr_in address) {
	
}

void respondRequest(int hSocket) {
	
}

void closeSocket(int hSocket) {
	
}
