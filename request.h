#ifndef REQUEST_H
#define REQUEST_H

struct Request {

	// first line
	char* method;
	char* path;
	char* version;

	// headers
	char* headers;

	// body
	char* body;

};

struct Request buildRequest(int hSocket);

#endif
