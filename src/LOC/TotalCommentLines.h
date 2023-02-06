#include <stdio.h>
#include <string.h>
#include<stdlib.h>
/*
In Java, there are three types of comments:
    1.Single-line comments
    2.Multi-line comments
    3.Documentation comments
*/

void countCommentLines()
{
    char filename[] = "SourceCode.java"; // specify the file name here
    char line[10000];
    int comment_count = 0;
    int single_line_comment = 0;
    int multi_line_comment = 0;
    int doc_comment = 0;
    char previous_char, current_char, next_char;

    FILE* file = fopen(filename, "r");

    if (file == NULL){
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    previous_char=fgetc(file);

    while ((current_char=fgetc(file)) != EOF){
        if (previous_char == '/' && current_char == '/') {
            single_line_comment++;
            comment_count++;
        }

        if (previous_char == '/' && current_char == '*') {
            next_char=fgetc(file);

            if (next_char == '*') {
                doc_comment++;
            } else {
                multi_line_comment++;
            }

            comment_count++;

            while (!(previous_char == '*' && current_char == '/')) {
                previous_char = current_char;
                current_char = getc(file);
            }
        }

        previous_char = current_char;
    }
    fclose(file);

    printf("Total number of comment lines: %d, which includes: \n", comment_count);
    printf("  1.Number of single line comments: %d\n", single_line_comment);
    printf("  2.Number of multi-line comments: %d\n", multi_line_comment);
    printf("  3.Number of documentation comments: %d\n", doc_comment);
}
