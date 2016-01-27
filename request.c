#include "request.h"
#include "cs360Utils.h"

struct Request buildRequest(int hSocket) {
	struct Request result;
	char* firstLine = GetLine(hSocket);
	result.method = strtok(firstLine, " ");
	result.path = strtok(NULL, " ");
	char* version = strtok(NULL, " ");
	if(strlen(version) == 0) {
		result.version = "HTTP/1.0";
	} else {
		result.version = version;
	}
	result.headers = "Header stuff";
	result.body = "";
	return result;
}
