#include <stdlib.h>
#include "response.h"

#define HEADERS_LENGTH

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
	char* forward = rt;
	int forwardLength = 0;
	while(*(forward++) != '\0') {
		forwardLength++;
	}
	memcpy(rt, response.body, response.contentLengthInt);
	//strcat(rt, response.body);
	return rt;
}

int getLength(struct Response response) {
	int space = strlen(" ");
	int newline = strlen("\r\n");
	int version = strlen(response.version) + space;
	int status = strlen(response.status) + space;
	int statusMessage = strlen(response.statusMessage);
	int firstLine = version + status + statusMessage + newline;
	int contentType = strlen("Content-Type: ") + strlen(response.contentType) + newline;
	int contentLength = strlen("Content-Length: ") + strlen(response.contentLength) + newline;
	int emptyLine = newline;
	int body = response.contentLengthInt;
	return firstLine + contentType + contentLength + emptyLine + body;
}
