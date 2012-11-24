/*
a really simple echo implementation, done by yours truly, nebukadnezzar.

Copyright of previous author applies, I suppose.
If no license defined, read on:

I, the copyright holder of this work, hereby release it into the public domain.
This applies worldwide. If this is not legally possible:
I grant any entity the right to use this work for any purpose, without any conditions,
unless such conditions are required by law. If law requires a definition of a software
license, the terms of the MIT/X11 license shall apply.
*/

/*
Usage: echo [-n] [string ...]
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main (int argc, char *argv[])
{
    int i;
    int omit_nl = false;

    for(i=1; i<argc; i++)
    {
        /* not using getopt(), because it's shite anyway
           there's likely a better way to do it, but it works just fine */
        if((strlen(argv[i]) > 1) && argv[i][0] == '-' && argv[i][1] == 'n')
        {
            omit_nl = true;
            continue;
        }
        printf("%s%s", argv[i], (i+1==argc ? "" : " "));
    }
    if(!omit_nl)
    {
        printf("\n");
    }
    return 0;
}
