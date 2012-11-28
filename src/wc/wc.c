/*
   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   Version 2, December 2004

   Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

   Everyone is permitted to copy and distribute verbatim or modified
   copies of this license document, and changing it is allowed as long
   as the name is changed.

   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

   0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define BUF_SIZE 1024

void
print_usage(void)
{
        printf("Usage: wc <flag> filename(s)\n");
}

void
print_help(void)
{
        printf(
                "Print newline, word, and/or byte counts for each FILE, and a total line if more than\n"
                "one FILE is specified. The options below may be used to select which counts are printed:\n"
                "-c, --bytes            print the byte counts\n"
                "-l, --lines            print the newline counts\n"
                "-L, --max-line-length  print the length of the longest line\n"
                "-w, --words            print the word counts\n"
                "-h, display this help and exit\n"
                "-v, output version information and exit\n"
                );
}

void
print_version(void)
{
        printf(
                "wc 0.1 is part of gentils "
                "(https://github.com/Oxidopamine/gentils)\n"
                "Written by Anonymous\n"
                );
}

int
sum(int *nums, int size) {
        int total = 0;
        for (int i = 0; i < size; ++i) total += nums[i];
        return total;
}

int
maximum(int a, int b) {
    return (a > b) ? a : b;
}

int
byte_count_file(FILE *src)
{
        char ch;
        int chars = 0;

        while ((ch=getc(src)) != EOF) ++chars;

        rewind(src);
        return chars;
}

int
byte_count_str(char *str)
{
    int p = 0;
    while (str[p] != '\0') p++;
    return p;
}

int
word_count_file(FILE *src)
{
        char ch;
        int sp = 1;
        int words = 0;

        while ((ch=getc(src)) != EOF) {
                if (isspace(ch)) sp = 1;
                else if (sp) {
                        ++words;
                        sp = 0;
                }
        }

        rewind(src);
        return words;
}

int
word_count_str(char *str)
{
    int sp = 1;
    int words = 0;
    
    int i;
    for (i = 0; str[i] != '\0'; ++i) {
        if (isspace(str[i])) sp = 1;
        else if (sp) {
            ++words;
            sp = 0;
        }
    }
    
    return words;
}

int
line_count_file(FILE *src)
{
        char ch;
        int lines = 0;

        while ((ch=getc(src)) != EOF) {
                if (ch == '\n') ++lines;
        }

        rewind(src);
        return lines;
}

int
line_count_str(char *str)
{
    int lines = 0;
    
    int i;
    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\n') ++lines;
    }
    
    return lines; 
}

int
max_line_length_file(FILE *src)
{
        char ch;
        int max = 0;
        int len = 0;

        while ((ch=getc(src)) != EOF) {
                if (ch != '\n') ++len;
                else {
                        if (len > max) max = len;
                        len = 0;
                }
        }

        rewind(src);
        return max;
}

int
max_line_length_str(char *str)
{
    int max = 0;
    int len = 0;

    int i;
    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] != '\n') ++len;
        else {
            if (len > max) max = len;
            len = 0;
        }
    }
    return max;
}

char*
read_stdin()
{
    if (ferror(stdin)) return NULL;

    char block[BUF_SIZE];
    char *result;
    char *old_result;
    size_t block_size = 1;

    result = malloc(sizeof(char) * BUF_SIZE);

    if (result == NULL) {
        perror("Failed to allocate memory for result.");
        exit(EXIT_FAILURE);
    }

    result[0] = '\0';

    while (fgets(block, BUF_SIZE, stdin)) {
        old_result = result;
        block_size += strlen(block);
        result = realloc(result, block_size);

        if (result == NULL) {
            perror("Failed to reallocate memory for result.");
            free(old_result);
            exit(EXIT_FAILURE);
        }

        strcat(result, block);
    }

    return result;
}


int
argcmp(char *arg, char *sht, char *lng)
{
    return (strcmp(arg,sht) == 0 || strcmp(arg,lng) == 0);
}

/* wc counts the number of bytes, words, and/or lines in a file or group of files. */
int
main(int argc, char *argv[])
{
        int byte_flag   = 0;
        int word_flag   = 0;
        int line_flag   = 0;
        int length_flag = 0;
        int file_index  = 0;

        /* process flags */
        for (int i = 1; i < argc && !file_index; ++i) {
            if      (argcmp(argv[i],"-c","--chars")) byte_flag = 1;
            else if (argcmp(argv[i],"-w","--words")) word_flag = 1;
            else if (argcmp(argv[i],"-l","--lines")) line_flag = 1;
            else if (argcmp(argv[i],"-L","--max-line-length")) length_flag = 1;
            else if (argcmp(argv[i],"-h","--help")) {
                print_help();
                exit(EXIT_SUCCESS);
            } else if (argcmp(argv[i],"-v","--version")) {
                print_version();
                exit(EXIT_SUCCESS);
            } else file_index = i;
        }
        
        int file_count = argc - file_index;

        if (!byte_flag && !word_flag && !line_flag && !length_flag) {
            byte_flag = word_flag = line_flag = 1;
        }

        /* TODO: handle piped input */
        int piped = 0;
        char *piped_input;
        if(!isatty(fileno(stdin))) {
                piped_input = read_stdin();
                piped = 1;
                file_count = 1;
        }

        /* user error: no piped input and no files given */
        if (argc == 1 && !piped) {
                print_usage();
                exit(EXIT_SUCCESS);
        }

        FILE *src;
        int bytes[file_count];
        int words[file_count];
        int lines[file_count];
        int lengths[file_count];

        if (!piped) { // process files

            int file_failure = 0;
            for (int i = 0; i < file_count; ++i) {
                
                if (!(src=fopen(argv[i+file_index], "r"))) {
                    printf(
                        "wc: %s: file cound not be opened"
                        "(or does not exist)\n", argv[i+file_index]);
                    file_failure = 1;
                    continue;
                }
               
                if (byte_flag) bytes[i] = byte_count_file(src);
                if (word_flag) words[i] = word_count_file(src);
                if (line_flag) lines[i] = line_count_file(src);
                if (length_flag) lengths[i] = max_line_length_file(src);
            
                fclose(src);
            }
            if (file_failure) exit(EXIT_FAILURE);
            
        } else { // process STDIN
            if (byte_flag) bytes[0] = byte_count_str(piped_input);
            if (word_flag) words[0] = word_count_str(piped_input);
            if (line_flag) lines[0] = line_count_str(piped_input);
            if (length_flag) lengths[0] = max_line_length_str(piped_input);
        }

        int bytes_total;
        int words_total;
        int lines_total;
        int length_total;
        
        int bytes_digits;
        int words_digits;
        int lines_digits;
        int length_digits;

        for (int i=0;i<file_count;++i) {
                if (byte_flag) {
                        bytes_total = sum(bytes, file_count);
                        bytes_digits = log10(bytes_total) + 2;
                }

                if (word_flag) {
                        words_total = sum(words, file_count);
                        words_digits = log10(words_total) + 2;
                }

                if (line_flag) {
                        lines_total = sum(lines, file_count);
                        lines_digits = log10(lines_total) + 2;
                }

                if (length_flag) {
                        length_total = maximum(lengths[i], length_total);
                        length_digits = log10(length_total) + 2;
                }
        }

        /* print requested counts */
        for (int i=0;i<file_count;++i) {
                if (line_flag) printf("%*d ", lines_digits, lines[i]);
                if (word_flag) printf("%*d ", words_digits, words[i]);
                if (byte_flag) printf("%*d ", bytes_digits, bytes[i]);
                if (length_flag) printf("%*d ", length_digits, lengths[i]);
                if (!piped) printf(" %s\n", argv[i+file_index]);
                    else printf("\n");
        }

        /* print 'total' line if multiple files were passed to wc */
        if (file_count > 1) {
                if (line_flag) printf("%*d ", lines_digits, lines_total);
                if (word_flag) printf("%*d ", words_digits, words_total);
                if (byte_flag) printf("%*d ", bytes_digits, bytes_total);
                if (length_flag) printf("%*d ", length_digits, length_total);
                printf(" total\n");
        }

        return 0;
}
