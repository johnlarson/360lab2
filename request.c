struct request {

	// first line
	char* method;
	char* path;
	char* version;

	// headers
	char* headers;

	// body
	char* body;

}

buildRequest(int hSocket) {
	struct request result;
	result.method = "GET";
	result.path = "/hello.html";
	result.version = "HTTP/1.1";
	result.headers = "Header stuff";
	result.body = "";
	return result;
}
