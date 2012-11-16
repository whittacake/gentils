/*
  cp - just as the "normal" cp, many features to be added
*/

//Credit goes to an anonymous 4chan user.

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

void printUsage()
{
  printf("USAGE: cp sourcefile targetfile\n");
}

int main ( int argc, char *argv[])
{

  if(argc < 3)
    {
      printUsage();
      return 1;
    }

  /* OPEN SRC FILE */

  FILE *src;

  if((src = fopen(argv[1], "rb")) == NULL) 
    {
      printf("Cannot open source file.\n");
      return 1;
    }
  
  /* OPEN DESTINATION FILE */

  FILE *dst;
  
  if((dst = fopen(argv[2], "w")) == NULL) 
    {
      printf("Cannot open destination file.\n");
      fclose(src);
      return 1;
    }
  
  /* COPY FILE CONTENT */
  
  // allocate buffer first, read src file

  fseek(src, 0, SEEK_END);
  unsigned long flen=ftell(src);
  fseek(src, 0, SEEK_SET);

#ifdef DEBUG
  printf("allocating buffer..\n");
#endif

  char *buf=(char *)malloc(flen+1);
  if (!buf)
    {
      fprintf(stderr, "Memory error!");
      fclose(src);
      fclose(dst);
      return 1;
    }

#ifdef DEBUG
  printf("now reading file contents..\n");
#endif

  fread(buf, flen, 1, src);

  // write file content

#ifdef DEBUG
  printf("now writing file contents..\n");
#endif

  fwrite(buf, flen, 1, dst);

  /* CLOSE FILES */

  if( fclose( src )) 
      printf("File close error.\n");

  if( fclose( dst )) 
      printf("File close error.\n");

  /* CLEANUP */
  free(buf);

  return 0;
}
