#include <stdio.h>
#include <string.h>

const int MAX_LENGTH=1e4;

/*
The logical line count is the number of 
semicolons (;) in each line, as each semicolon typically 
represents the end of a single logical line in Java code.
*/

int countSemicolonPerLine(const char *copiedLine){
    int semicolon=0;
    const char *line=copiedLine;

    while(*line){
        if(*line == ';'){
            semicolon++;
        }

        line++;
    }

    return semicolon;
}

void countLogicalLines()
{
    char filename[] = "SourceCode.java"; // specify the file name here
    char line[MAX_LENGTH];
    int logicalLines = 0;

    FILE* file = fopen(filename, "r");

    if (!file){
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    while (fgets(line, sizeof(line), file)){
        // if (strncmp(line, "//", 2) == 0 || strncmp(line, "/*", 2) == 0){
        //     // do nothing, as this is a comment
        // }else{
        //     logicalLines += countSemicolonPerLine(line);
        // }

        // Check if the line is a multi-line comment
        if (strlen(line) >= 2 && line[0] == '/' && line[1] == '*') {
            while (fgets(line, sizeof(line), file)) {
                if (strlen(line) && line[strlen(line) - 2] == '*' && line[strlen(line) - 1] == '/') {
                    break;
                }
            }
        } else if (strlen(line) >= 2 && line[0] == '/' && line[1] == '/') {
            // do nothing, as this is a single line comment
        } else {
            logicalLines += countSemicolonPerLine(line);
        }
    }
    fclose(file);

    printf("Total logical lines of code : %d\n", logicalLines);
}
