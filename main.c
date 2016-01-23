#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

#define ERROR -1

int main(int argc, char** argv) {
	if(argc < 3) {
		expressFrustration("You need to type in something in this format: server port-number directory");
	}
	int port;
	//try {
		port = atoi(argv[1]);
	//} catch(const invalid_argument &ia) {
		//expressFrustration("The port needs to be number");
	//}
	char* directory = argv[2];
	struct stat filestat;
	if(stat(directory, &filestat) == ERROR) {
		expressFrustration("That's not a directory");
	}
	if(S_ISREG(filestat.st_mode)) {
		expressFrustration("I need a directory, but you gave me a regular file");
	}
	runserver(port, directory);
}
