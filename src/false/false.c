#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i = 1;
	for(i = 1; i < argc; i++) {
		if(!strncmp(argv[i], "--", 2) && !strcasecmp(argv[i], "--version")) {
			puts("Gentils false v0.1");
			return 1; 
		}
	}
	return 1;
}
