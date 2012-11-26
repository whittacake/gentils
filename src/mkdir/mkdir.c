/* 		Copyright (C) 2012 Jan Brennen and Tootoot222		*/

/*
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
									 */

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void help(char *progname);

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("%s: Missing operand.\n", argv[0]);
		help(argv[0]);
		return(1);
	}

	// Makeshift getopt 
	int p = 0, i = 1, v = 0, dc = -1;
	int diris[argc];
	mode_t mode = 0755;

	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				case 'p':
					p = 1;
					break;
				case 'h':
					help(argv[0]);
					return(0);
				case 'v':
					v = 1;
					break;
				case 'm':
					umask(0000);
					if(argv[i + 1]) {
						int v = -1;
						while(argv[i + 1][++v]) {
							if((argv[i + 1][v] < '0') || (argv[i + 1][v] > '7') || (v > 3)) {
								goto ivm;
							}
						}
						if((v = sscanf(argv[i + 1], "%o", &mode)) && (v != EOF)) {
							i++;
							continue;
						}else {
ivm:;
							printf("%s: invalid mode '%s'\n", argv[0], argv[i + 1]);
							return(1);
						}

					}else {
						printf("%s: option requires an argument -- '%c'\n", argv[0], argv[i][1]);
						return(1);
					}
					break;
				case 'V':
					printf("( ͡° ͜ʖ ͡°) mkdir v0.0.2 by Jan Brennen and Tootoot222 for the Gentils project\n");
					return(0);
				default:
					printf("%s: invalid option `%s'.\n", argv[0], argv[i]);
					return(1);
			}
		}else {
			diris[++dc] = i;
		}
	}

	if(dc == -1) {
		printf("%s: missing operand\n\
Try 'mkdir -h' for more information.\n", argv[0]);
	}

	//Attempt to make the directory; diris contains the indexes of non-switches (I.E. directories to create), and dc is the highest index
	int ret = 0;
	for(i = 0; i < (dc + 1); i++) {
		if(p) {
			size_t ii = -1;
			char cc = 0;
			while((cc = argv[diris[i]][++ii])) {
				if(cc == '/') {
					argv[diris[i]][ii] = 0;
					if(mkdir(argv[diris[i]], mode)) {
						if(errno == EEXIST) {
							struct stat buf;
							if(!stat(argv[diris[i]], &buf)) {
								if(S_ISDIR(buf.st_mode)) {
									argv[diris[i]][ii] = '/';
									goto dcloop;
								}else {
									errno = ENOTDIR;
								}
							}
						}
						printf("%s: cannot create directory `%s': %s\n", argv[0], argv[diris[i]], strerror(errno));
						ret = 1;
						goto pploop;
					}
					if(v) {
						printf("%s: created the directory `%s'\n", argv[0], argv[diris[i]]);
					}
					argv[diris[i]][ii] = '/';
				}
			}
dcloop:;
		}
		if(mkdir(argv[diris[i]], mode)) {
			if((p) && (errno == EEXIST)) {
				struct stat buf;
				if((!stat(argv[diris[i]], &buf)) && (S_ISDIR(buf.st_mode))) {
					continue;
				}
			}
			printf("%s: cannot create directory `%s': %s\n", argv[0], argv[diris[i]], strerror(errno));
			return(1);
		}else if(v) {
			printf("%s: created the directory `%s'\n", argv[0], argv[diris[i]]);
		}
pploop:;
	}
	return(ret);
}

void help(char *progname) {
	//heredoc style, YYEEAAHHHHH
	printf("\
%s [OPTION]... [DIRECTORY]...\n\
Create the DIRECTORY(ies), if they do not already exist.\n\
\n\
Mandatory arguments to long options are mandatory for short options too. (long options not implemented yet)\n\
  -m, --mode=MODE     set file mode (as in chmod), not a=rwx - umask\n\
  -p, --parents       no error if existing, make parent directories as needed\n\
  -v, --verbose       print a message for each created directory\n\
  -Z, --context=CTX   set the SELinux security context of each created\n\
                        directory to CTX (not implemented yet)\n\
  -h, --help          display this help and exit\n\
  -V, --version       output version information and exit\n\
", progname);
}

