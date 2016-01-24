#ifndef RESPONSE_H
#define RESPONSE_H

struct Response {
	
	// first line
	char* version;
	char* status;
	char* statusMessage;

	// headers
	char* contentType;
	char* contentLength;
	int contentLengthInt;

	char* body;
};

char* getResponseString(struct Response response);

#endif
