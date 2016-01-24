#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "request.h"
#include "response.h"
#include "cs360Utils.h"
#include "fileserving.h"

#define QUEUE_SIZE 5
#define ERROR -1

void startSocket(int port, int* hSocket, struct sockaddr_in* address);
void acceptLoop(int hServerSocket, struct sockaddr_in address, char* dir);
void respondRequest(int hSocket, char* dir);
void closeSocket(int hSocket);

void runserver(int port, char* dir) {
	int hServerSocket;
	struct sockaddr_in address;
	startSocket(port, &hServerSocket, &address);
	acceptLoop(hServerSocket, address, dir);	
	closeSocket(hServerSocket);
}

void startSocket(int port, int* hSocket, struct sockaddr_in* address) {
	*hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(*hSocket == ERROR) {
		expressFrustration("I couldn't make a socket, and it's probably your fault");
	}
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(port);
	address->sin_family = AF_INET;
	if(bind(*hSocket, (struct sockaddr*)address, sizeof(*address)) == ERROR) {
		expressFrustration("I can't bind the address to the socket");
	}
	int addressSize = sizeof(struct sockaddr_in);
	getsockname(*hSocket, (struct sockaddr*)address, (socklen_t*)&addressSize);
	if(listen(*hSocket, QUEUE_SIZE) == ERROR) {
		expressFrustration("I wasn't able to listen on the port you gave me");
	} 
}

void acceptLoop(int hServerSocket, struct sockaddr_in address, char* dir) {
	while(1) {
		int addressSize = sizeof(struct sockaddr_in);
		int hSocket = accept(hServerSocket, (struct sockaddr*)&address, (socklen_t*)&addressSize);
		respondRequest(hSocket, dir);
		closeSocket(hSocket);
	}
}

void respondRequest(int hSocket, char* dir) {
	struct Request request = buildRequest(hSocket);
	printf("%s\n", request.method);
	printf("%s\n", request.path);
	printf("%s\n", request.version);
	struct Response response = buildResponse(request, dir);
	char* msg = getResponseString(response); 
	write(hSocket, msg, strlen(msg) + 1);
}

void closeSocket(int hSocket) {
	if(close(hSocket) == ERROR) {
		expressFrustration("The whole thing exploded when I tried to close a socket");
	}
}
