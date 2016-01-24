#include "request.h"
#include "cs360Utils.h"

struct Request buildRequest(int hSocket) {
	struct Request result;
	char* firstLine = GetLine(hSocket);
	result.method = strtok(firstLine, " ");
	result.path = strtok(NULL, " ");
	result.version = strtok(NULL, " ");
	result.headers = "Header stuff";
	result.body = "";
	return result;
}
