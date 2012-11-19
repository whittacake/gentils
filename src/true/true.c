#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i = 1;
	for(i = 1; i < argc; i++){
	if(!strncmp(argv[1], "--", 2) && !strcasecmp(argv[1], "--version")) {
		 puts("Gentils true v0.1"); 
	}
}
	return 0;
}
