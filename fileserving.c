#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "response.h"
#include "request.h"
#include "fileserving.h"
#include "utils.h"

#define ERROR -1

struct Response buildResponseRec(char* path, struct stat filestat);
char* getContentType(char* path);
char* joinPath(outer, inner);
char* get404();
char* getBody(char* path, struct stat filestat);
char* showDirectory(char* path, struct stat filestat);

struct Response buildResponse(struct Request request, char* root) {
	char* path = joinPath(root, request.path);
	struct stat filestat;
	struct Response response = buildResponseRec(path, filestat);
	response.version = request.version;
	response.contentLengthInt = strlen(response.body);
	sprintf(response.contentLength, "%i", response.contentLengthInt);
	//free(path);
	return response;
}

struct Response buildResponseRec(char* path, struct stat filestat) {
	struct Response response;
	if(stat(path, &filestat) == ERROR) {
		response.status = "404";
		response.statusMessage = "Not Found";
		response.contentType = "text/html";
		response.body = get404();
	} else if(S_ISREG(filestat.st_mode)) {
		response.status = "200";
		response.statusMessage = "OK";
		response.contentType = getContentType(path);
		response.body = getBody(path, filestat);
	} else if(S_ISDIR(filestat.st_mode)) {
		char* indexPath = joinPath(path, "index.html");
		response.status = "200";
		response.statusMessage = "OK";
		response.contentType = "text/html";
		struct stat indexStat;
		if(stat(indexPath, &indexStat) == ERROR) {
			response.body = showDirectory(path, filestat);
		} else {
			response.body = getBody(indexPath, indexStat);
		}
		//free(indexPath);
	}
	return response;
}

char* getContentType(char* path) {
	int dotIndex = strchr(path, '.') - path;
	int firstIndex = dotIndex + 1;
	int substrLength = strlen(path) - firstIndex;
	char* substr = substring(firstIndex, substrLength, path);
	char* returnable;
	if(!strcmp(substr, "html")) {
		returnable = "text/html";
	} else if(!strcmp(substr, "txt")) {
		returnable =  "text/plain";
	} else if(!strcmp(substr, "jpg")) {
		returnable = "image/jpg";
	} else if(!strcmp(substr, "gif")) {
		returnable = "image/gif";
	}
	//free(substr);
	return returnable;
}


char* joinPath(char* parent, char* child) {
	int parentLastIndex = strlen(parent) - 1;
	if(parent[parentLastIndex] == '/') {
		parent = substring(0, parentLastIndex, parent);
	}
	if(child[0] == '/') {
		child = substring(1, strlen(child) - 1, child);
	}
	int newLength = strlen(parent) + strlen("/") + strlen(child);
	char* returnable = (char*)malloc(newLength);
	strcpy(returnable, parent);
	strcat(returnable, "/");
	strcat(returnable, child);
	//free(parent);
	//free(child);
	return returnable;
}

char* get404() {
	return "<!DOCTYPE html><html><head></head><body>404 Message Here</body></html>";
}

char* getBody(char* path, struct stat filestat) {
	return "<!DOCTYPE html><html><head></head><body>File Here</body></html>";
}

char* showDirectory(char* path, struct stat filestat) {
	return "<!DOCTYPE html><html><head></head><body>Directory Here</body></html>";
} 
