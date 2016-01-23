struct response {
	
	// first line
	char* version;
	int status;
	char* statusMessage;

	// headers
	char* contentType;
	int contentLength;

	char* body;
}

char* getResponseString(struct response myResponse) {
	return "the response";
}
