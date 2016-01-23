#ifndef RESPONSE_H
#define RESPONSE_H

struct response {
	
	// first line
	char* version;
	int status;
	char* statusMessage;

	// headers
	char* contentType;
	int contentLength;

	char* body;
};

struct response;
char* getResponseStr(struct response myResponse);

#endif
