/* 
>Copyright
>2012
Shiggerino

Insert license information here at some point 
*/

/* 
Usage: echo [-n] [string ...] 
*/

#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{

	if (argc < 2)
		return 0;

	int i;
	char c;

	c = getopt(argc, argv, "n");

	if (c != 'n') {
		for (i = 1; i < argc; i++) 
			printf("%s ", argv[i]);
		printf("\n");
	} else {
		for (i = 2; i < argc; i++) 
			printf("%s ", argv[i]);
	}

	return 0;
}
