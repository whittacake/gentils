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

void print_usage(void) {
    printf("Usage: wc <flag> filename(s)\n");
}

void print_help(void) {
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

void print_version(void) {
    printf(
        "wc (alpha 0.01) is part of gentils "
        "(https://github.com/Oxidopamine/gentils)\n"
        "Written by Anonymous\n"
    );
}

int line_count(FILE *src) {
    char ch;
    int lines = 0;

    while ((ch=getc(src)) != EOF) {
        if (ch == '\n') ++lines;
    }

    return lines;
}

int byte_count(FILE *src) {
    char ch;
    int chars = 0;

    while ((ch=getc(src)) != EOF) ++chars;

    return chars;
}

int word_count(FILE *src) {
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

    return words;
}

int max_line_length(FILE *src) {
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

    return max;
}

int main ( int argc, char *argv[]) {

    if(!isatty(STDIN_FILENO)) {
        print_usage();
        return 1;
    }

    if (argc == 1 || argv[1][0] != '-') {
        print_usage();
        return 1;
    }

    int (*counter)(FILE *);

    switch (argv[1][1]) {
        case 'l':
            counter = &line_count;
            break;
        case 'c':
            counter = &byte_count;
            break;
        case 'L':
            counter = &max_line_length;
            break;
        case 'w':
            counter = &word_count;
            break;
        case 'h':
            print_usage();
            print_help();
            return 0;
        case 'v':
            print_version();
            return 0;
        default:
            print_usage();
            print_help();
            return 1;
    }

    FILE *src;
    int total = 0;
    int count;

    for (int i = 2; i < argc; ++i) {
        if (!(src=fopen(argv[i], "r"))) {
            printf("One or more FILES could not be read\n");
            return 1;
        }
        count = counter(src);
        total += count;
        printf("%i\t" "%s\n", count, argv[i]);
        fclose(src);
    }

    printf("%i\t" "total\n", total);

    return 0;
}
