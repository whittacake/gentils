#include <stdio.h>

int
main (int argc, char *argv[])
{
	int i, j, space;
	char c;
	FILE* gFile;
	
	for (i = 1; i < argc; i++){
		gFile = fopen(argv[i], "r");

		if(gFile)
		{
			space = 0;
			c = fgetc (gFile);
			do{
    			if(c == '\t'){ 
    				for(j = 8 - space; j > 0; j--)
    					printf(" ");
    				space = 0;
    			}
    			else if(c == '\n'){
    				space = 0;
    				printf("\n");
    			}
    			else{
    				if(space == 7)
    					space = 0;
    				else
    					space++;
    				printf("%c", c);
    			}

    			c = fgetc (gFile);
   			} while(c != EOF);
		}
	}

	return 0;
}
