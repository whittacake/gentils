#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
  
  int status;

  char *input;
  char *output;

  if(argc < 2) 
    {
      puts("mv: missing file operand");
      return(1);
    }

  if(argc < 3)
    {
      printf("mv: missing file operand after '%s'", argv[1]);
      return(1);
    }

  input = argv[1];
  output = argv[2];

  status = rename(input, output);

  if(status == -1)
    {
      printf("ERROR: %s\n", strerror(errno));
      return 1;
    }
  return(0);
}
