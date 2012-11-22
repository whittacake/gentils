#include <stdio.h>
#include <string.h>
#define VERSION "Gentils Yes v0.0.1\n"

int main(int argc, char *argv[]){
  if(argv[1] != NULL)
    {
      if(!strcmp(argv[1], "--version"))
	{
	  printf(VERSION);
	  return 0;
	}

      while(1)
	{
	  printf("%s\n", argv[1]);
	}
    }

  else
    {
	while(1)
	  {
	    printf("y\n");
	  }

	return 0;
    }
}
