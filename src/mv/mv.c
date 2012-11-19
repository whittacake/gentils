#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc < 2) {
		puts("mv: missing file operand");
		return(1);
	}
	if(argc < 3) {
		printf("mv: missing file operand after '%s'", argv[1]);
		return(1);
	}
	rename(argv[1], argv[2]);
	return(0);
}
