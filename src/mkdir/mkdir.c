/* 		Copyright (C) 2012 Jan Brennen

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
extern int errno;
int help(char *argv[]);
int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("%s: Missing operand.\n", argv[0]);
		help(argv);
		return 1;
	}

	// Makeshift getopt until I learn how to actually use getopt.
	int p = 0, i = 1, v = 0;
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				case 'p':
					p = 1;
					break;
				case 'h':
					help(argv);
					return 0;
				case 'v':
					v = 1;
					break;
				case 'V':
					printf("( ͡° ͜ʖ ͡°) mkdir v0.0.1 by Jan Brennen for the Gentils project\n");
					break;
				default:
					printf("%s: invalid option `%s'.\n", argv[0], argv[i]);
					return 1;
			}
		}
	}


			// Attempt to make the directory
	for(i = 1; i < argc; i++) {
		if(argv[i][0] != '-') {
			if(mkdir(argv[i], 0755) != 0){
				printf("%s: could not create directory `%s': %s\n", argv[0], argv[i], strerror(errno));
				return 1;
			}
			else if(v) {
				printf("%s: created the directory `%s'\n", argv[0], argv[i]);
			}
		}
	}
	
	// To get gcc to shut up:
	return 0;
}

int help(char *argv[]) {
	printf("%s - Creates directories\n", argv[0]);
	printf(" -p foo/dirname\n   Creates directory \"dirname\" while also creating its parent directory \"foo\" (not yet implemented)\n");
	printf(" -v dirname\n   Creates directory \"dirname\" and is verbose about it\n");
	return 0;
}
