#include <stdlib.h>
#include "response.h"

#define HEADERS_LENGTH

int getLength(struct Response response);

char* getResponseString(struct Response response) {
	//return "stuff\r\n\r\n";
	int responseLength = getLength(response);
	char* rt = (char*)malloc(responseLength);
	strcpy(rt, response.version);
	strcat(rt, " ");
	strcat(rt, response.status);
	strcat(rt, " ");
	strcat(rt, response.statusMessage);
	strcat(rt, "\r\n");
	strcat(rt, "Content-Type: ");
	strcat(rt, response.contentType);
	strcat(rt, "\r\n");
	strcat(rt, "Content-Length: ");
	strcat(rt, response.contentLength);
	strcat(rt, "\r\n");
	strcat(rt, "\r\n");
	strcat(rt, response.body);
	return rt;
}

int getLength(struct Response response) {
	printf("VERSION: %s\n", response.version);
	printf("STATUS: %i\n", response.status);
	printf("MESSAGE: %s\n", response.statusMessage);
	int space = strlen(" ");
	int newline = strlen("\r\n");
	int version = strlen(response.version) + space;
	int status = strlen(response.status) + space;
	int statusMessage = strlen(response.statusMessage);
	int firstLine = version + status + statusMessage + newline;
	int contentType = strlen(response.contentType) + newline;
	int contentLength = strlen(response.contentLength) +newline;
	int emptyLine = newline;
	int body = strlen(response.body);
	return firstLine + contentType + contentLength + emptyLine + body + 1;
}
