/* a NetBSD user's wet dream


   ... but please don't actually use this code.
   If you must, it's public domain. Knock yourself silly with it.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main (int argc, char *argv[])
{
    int i = 1;
    int omit_nl = false;

    if((strlen(argv[i]) > 1) && argv[i][0] == '-' && argv[i][1] == 'n')
    {
        omit_nl = true;
        i++;
    }

    loop_next_string:
        if(i == argc)
        {
            goto end_loop;
        }
        goto print_next_string;


    print_next_string:
        printf("%s%s", argv[i], (i+1==argc ? "" : " "));
        i++;
        goto loop_next_string;

    end_loop:
        if(!omit_nl)
        {
            printf("\n");
        }
        return 0;
}
