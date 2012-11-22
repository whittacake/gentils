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
                "wc (alpha 0.01) is part of gentils "
                "(https://github.com/Oxidopamine/gentils)\n"
                "Written by Anonymous\n"
                );
}

int
byte_count(FILE *src)
{
        char ch;
        int chars = 0;

        while ((ch=getc(src)) != EOF) ++chars;

        rewind(src);
        return chars;
}

int
word_count(FILE *src)
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
line_count(FILE *src)
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
max_line_length(FILE *src)
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
max(int a, int b)
{
        int c = (a > b) ? a : b;
        return c;
}

int
sum(int *nums, int size) {
        int i;
        int total = 0;
        for (i = 0; i < size; ++i) total += nums[i];
        return total;
}

/* wc counts the number of bytes, words, and/or lines in a file(s). */
int
main(int argc, char *argv[])
{
        int byte_flag = 0;
        int word_flag = 0;
        int line_flag = 0;
        int length_flag = 0;

        // TODO: handle piped input
        if(!isatty(STDIN_FILENO)) {
                print_usage();
                return 1;
        }

        if (argc == 1) {
                print_usage();
                return 1;
        }

        opterr = 0;

        int ch;
        while((ch = getopt(argc,argv,"cwlLhv::")) != -1)
                switch (ch) {
                        case 'c':
                                byte_flag = 1;
                                break;
                        case 'w':
                                word_flag = 1;
                                break;
                        case 'l':
                                line_flag = 1;
                                break;
                        case 'L':
                                length_flag = 1;
                                break;
                        case 'h':
                                print_help();
                                return 0;
                        case 'v':
                                print_version();
                                return 0;
                        case '?':
                                if (isprint (optopt))
                                        fprintf (stderr,
                                            "Unknown option `-%c'.\n", optopt);
                                else
                                        fprintf (stderr,
                                            "Unknown option character `\\x%x'.\n", optopt);
                                return 1;
                        default:
                                abort();
                }

        int file_count = argc - optind;
        if (!file_count) {
                print_usage();
                return 1;
        }

        /* no flags passed, use default behavior */
        if (byte_flag == 0 && word_flag == 0 && line_flag == 0 && length_flag == 0) {
                byte_flag = 1;
                word_flag = 1;
                line_flag = 1;
        }

        FILE *src;
        int bytes[file_count];
        int words[file_count];
        int lines[file_count];
        int lengths[file_count];

        int i;
        int failed = 0;
        for (i = optind; i < argc; ++i) {

                if (!(src=fopen(argv[i], "r"))) {
                        printf("wc: %s: file cound not be opened (or does not exist)\n", argv[i]);
                        failed = 1;
                        continue;
                }

                if (byte_flag) bytes[i-optind] = byte_count(src);
                if (word_flag) words[i-optind] = word_count(src);
                if (line_flag) lines[i-optind] = line_count(src);
                if (length_flag) lengths[i-optind] = max_line_length(src);

                fclose(src);
        }

        if (failed) return 1;

        int bytes_total;
        int words_total;
        int lines_total;
        int length_total;
        int digits = 0;

        /*
         *  Calculate the 'total' values and find the maximum number of
         *  digit spaces needed for printing.
         */
        for (i=0;i<file_count;++i) {

                if (byte_flag) {
                        bytes_total = sum(bytes, file_count);
                        digits = max(digits, log10(bytes_total) +  1);
                }

                if (word_flag) {
                        words_total = sum(words, file_count);
                        digits = max(digits, log10(words_total) +  1);
                }

                if (line_flag) {
                        lines_total = sum(lines, file_count);
                        digits = max(digits, log10(lines_total) +  1);
                }

                if (length_flag) {
                        length_total = max(lengths[i], length_total);
                        digits = max(digits, log10(length_total) +  1);
                }
        }

        ++digits;

        for (i=0;i<file_count;++i) {
                if (line_flag) printf("%*d ", digits, lines[i]);
                if (word_flag) printf("%*d ", digits, words[i]);
                if (byte_flag) printf("%*d ", digits, bytes[i]);
                if (length_flag) printf("%*d ", digits, lengths[i]);
                printf("%s\n", argv[optind + i]);
        }

        if (file_count > 1) {
                if (line_flag) printf("%*d ", digits, lines_total);
                if (word_flag) printf("%*d ", digits, words_total);
                if (byte_flag) printf("%*d ", digits, bytes_total);
                if (length_flag) printf("%*d ", digits, length_total);
                printf("total\n");
        }

        return 0;
}
