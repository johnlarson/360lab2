#ifndef REQUEST_H
#define REQUEST_H

struct request {

	// first line
	char* method;
	char* path;
	char* version;

	// headers
	char* headers;

	// body
	char* body;

};

struct request buildRequest(int hSocket);

#endif
