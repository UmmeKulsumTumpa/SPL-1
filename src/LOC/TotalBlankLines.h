#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void countBlankLines()
{
    char filename[] = "SourceCode.java"; // specify the file name here
    char current_char, prev_char;
    int blank_line_count=0;

    FILE* file = fopen(filename, "r");

    if (!file){
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    prev_char = '\0';

    while ((current_char = getc(file)) != EOF) {
        if (current_char == '\n') {
            if (prev_char == '\n' || prev_char == '\r' || prev_char == ' ' || prev_char == '\t') {
                blank_line_count++;
            }
        }

        prev_char = current_char;
    }
    fclose(file);

    printf("Total number of blank lines: %d\n", blank_line_count);
}