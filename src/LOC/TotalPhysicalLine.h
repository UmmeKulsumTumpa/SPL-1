#include <stdio.h>
#include <string.h>

const int MAX=1e4;

/*
The physical SLOC is a count of lines in the text of the program's
source code including comment lines and, sometimes, blank lines.
*/

void countPhysicalLines()
{
    char filename[] = "SourceCode.java"; // specify the file name here
    char line[MAX];
    int physicalLines = 0;

    FILE* file = fopen(filename, "r");

    if (file){
        while (fgets(line, sizeof(line), file)) {
            physicalLines++;
        }
        fclose(file);
    }else{
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    printf("Total physical lines of code : %d\n", physicalLines);
}
