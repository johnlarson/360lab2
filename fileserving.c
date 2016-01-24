#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "response.h"
#include "request.h"
#include "fileserving.h"

#define ERROR -1

char* getContentType(char* path);
char* joinPath(outer, inner);
char* get404();

struct Response buildResponse(struct Request request, char* root) {
	struct Response response;
	response.version = request.version;
	response.contentType = getContentType(request.path);
	char* path = joinPath(root, request.path);
	struct stat filestat;
	printf("\nPATH: %s\n", path);
	if(stat(path, &filestat) == ERROR) {
		printf("\nERROR\n");
		response.status = "404";
		response.statusMessage = "Not Found";
		response.contentType = "text/html";
		response.body = get404();
		response.contentLengthInt = strlen(response.body);
		sprintf(response.contentLength, "%i", response.contentLengthInt);
	}
	return response;
}

char* getContentType(char* path) {
	return "text/html";
}

char* joinPath(char* parent, char* child) {
	return "hello/doesntexist.html";
}

char* get404() {
	return "<!DOCTYPE html><html><head></head><body>404 Message Here</body></html>";
}
