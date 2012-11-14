#include <stdio.h>
#include <string.h>
#define VERSION "Gentils Yes v0.0.1\n"

int main(int argc, char *argv[]){
  if(argv[1] != NULL)
    while(1)
      printf("%s\n", argv[1]);
  else
    while(1)
      printf("yes\n");

	return 0;
}
