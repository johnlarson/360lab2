#include <stdlib.h>
#include <sys/stat.h>
#include "utils.h"
#include "server.h"

#define ERROR -1

int main(int argc, char** argv) {
	if(argc < 3) {
		expressFrustration("You need to type in something in this format: server port-number directory");
	}
	int port;
	port = atoi(argv[1]);
	if(port == 0) {
		expressFrustration("The port has to be an integer greater than zero");
	}
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
