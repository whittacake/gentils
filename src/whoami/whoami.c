#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int skip_over_char(char c, FILE *fp)
{
    while(1) {
        char fc = fgetc(fp);
        if (fc == EOF) return 1;
        if (fc == c)   return 0;
    }
}

int main(int argc, char *argv[])
{
    uid_t euid = geteuid();
    FILE *passwd = fopen("/etc/passwd", "r");

    int start, end, len;
    char *name;
    int   tempid;

    while (1)
    {
        /*record position of name*/
        start = ftell(passwd);

        /*move over ':', check for eof*/
        if (skip_over_char(':', passwd)) {
            fprintf(stderr, "something fucked up!\n");
            return 1;
        }

        /*record current position - one char after the ':' character*/
        end = ftell(passwd) - 1;

        /*move back to string*/
        fseek(passwd, start, SEEK_SET);

        /*calculate the length*/
        len = end - start;

        if (len > 0)
        {
            /*allocate space for string, including NULL byte*/
            name = malloc(len+1);

            /*read string, if it fucks up return 1 I guess*/
            if (fread(name, 1, len, passwd) != len) {
                fprintf(stderr, "something fucked up\n");
                return 1;
            }
            name[len] = 0;

            /*move back over two colons*/
            skip_over_char(':', passwd); 
            skip_over_char(':', passwd);

            /*read the uid*/
            fscanf(passwd, "%d", &tempid);

            /*check the uid*/
            if (tempid == euid) {
                printf("%s\n", name);
                return 0;
            }

            /*free up memory*/
            free(name);
        }

        /*skip to next line, return 1 if EOF*/
        if (skip_over_char('\n', passwd)) {
            return 1;
        }
    }

    /*this should never occur*/
    return 9001;
}
