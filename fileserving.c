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

struct Response buildResponseRec(char* path, char* reqPath, struct stat filestat);
char* getContentType(char* path);
char* joinPath(outer, inner);
char* get404();
char* getBody(char* path, struct stat filestat);
char* showDirectory(char* path, char* reqPath);

struct Response buildResponse(struct Request request, char* root) {
	char* path = joinPath(root, request.path);
	struct stat filestat;
	struct Response response = buildResponseRec(path, request.path, filestat);
	response.version = request.version;
	response.contentLength = (char*)malloc(30);
	sprintf(response.contentLength, "%i", response.contentLengthInt);
	//free(path);
	return response;
}

struct Response buildResponseRec(char* path, char* reqPath, struct stat filestat) {
	struct Response response;
	if(stat(path, &filestat) == ERROR) {
		response.status = "404";
		response.statusMessage = "Not Found";
		response.contentType = "text/html";
		response.body = get404();
		response.contentLengthInt = strlen(response.body);
	} else if(S_ISREG(filestat.st_mode)) {
		response.status = "200";
		response.statusMessage = "OK";
		response.contentType = getContentType(path);
		response.body = getBody(path, filestat);
		response.contentLengthInt = filestat.st_size;
	} else if(S_ISDIR(filestat.st_mode)) {
		char* indexPath = joinPath(path, "index.html");
		response.status = "200";
		response.statusMessage = "OK";
		response.contentType = "text/html";
		struct stat indexStat;
		if(stat(indexPath, &indexStat) == ERROR) {
			response.body = showDirectory(path, reqPath);
			response.contentLengthInt = strlen(response.body);
		} else {
			response.body = getBody(indexPath, indexStat);
			response.contentLengthInt = indexStat.st_size;
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
		//char* newParent = substring(0, parentLastIndex, parent);
		//strcpy(parent, newParent);
		parent = substring(0, parentLastIndex, parent);
		//free(newParent);
	}
	if(child[0] == '/') {
		//char* newChild = substring(1, strlen(child) - 1, child);
		//strcpy(child, newChild);
		child = substring(1, strlen(child) - 1, child);
		//free(newChild);
	}
	int newLength = strlen(parent) + strlen("/") + strlen(child);
	char* returnable = (char*)malloc(newLength);
	strcpy(returnable, parent);
	strcat(returnable, "/");
	strcat(returnable, child);
	return returnable;
}

char* get404() {
	return "<!DOCTYPE html><html><head></head><body>404 Message Here</body></html>";
}

char* getBody(char* path, struct stat filestat) {
	FILE* fp = fopen(path, "r");
 	char* buffer = (char*)malloc(filestat.st_size + 4);
	fread(buffer, filestat.st_size, 1, fp);
	fclose(fp);
	return buffer;
}

char* showDirectory(char* path, char* reqPath) {
	int len;
	DIR *dirp;
	struct dirent *dp;
	char* start = "<!DOCTYPE html><html><head></head><body>";
	char* chunkStart = "<a href='";
	char* chunkMiddle = "'>";
	char* chunkEnd = "</a><br>";
	char* end = "</body></html>";
	int length = strlen(start) + strlen(end) + 1;
	dirp = opendir(path);
	while((dp = readdir(dirp)) != NULL) {
		char* itemReqPath = joinPath(reqPath, dp->d_name);
		length += strlen(chunkStart);
		length += strlen(itemReqPath);
		length += strlen(chunkMiddle);
		length += strlen(dp->d_name);
		length += strlen(chunkEnd);
	}
	(void)closedir(dirp);
	char* result = (char*)malloc(length);
	dirp = opendir(path);
	strcpy(result, start);
	while((dp = readdir(dirp)) != NULL) {
		char* itemReqPath = joinPath(reqPath, dp->d_name);
		strcat(result, chunkStart);
		strcat(result, itemReqPath);
		strcat(result, chunkMiddle);
		strcat(result, dp->d_name);
		strcat(result, chunkEnd);
	}
	(void)closedir(dirp);
	strcat(result, end);
	return result;
} 
