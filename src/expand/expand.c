/* 
>Actually writing code
>2012
>trvra wrote this, based on Shiggerino's baller echo code
>with some of that sweet, sweet tee.c baked in

Insert license information here at some point 
*/

/* 
Usage: expand [-t tab1,tab2,...,tabn] [file ...]
*/

#include <stdio.h>
#include <string.h>
#define space++ ((space)>(8)?(0):(space += 1))

int
main (int argc, char *argv[])
{
	int i;
	char c;
	FILE **g_files    = NULL;
	char **g_fileName = NULL;
	int    g_numFiles = 0;

	if (argc < 2)
		return 0;

	g_files = (FILE**)malloc(sizeof(FILE**) * g_numFiles);

	i = argc - 1;
	while( i > 0){
    	g_files[i] = fopen(g_fileName[i], g_writeMode);
    		if (!g_files[i]) {
        		fprintf(stderr, "failed to open %s\n", g_fileName[i]);
        		return 1;
    		}
    }

	/* When I want to solve for -t, it'll go here~~
	c = getopt(argc, argv, "t");

	if (c != 't') {
		for (i = 1; i < argc; i++) 
			printf("%s ", argv[i]);
		printf("\n");
	} else {
	*/
		for (i = 2; i < argc; i++) 
			printf("%s ", argv[i]);
	//}

	return 0;
}
