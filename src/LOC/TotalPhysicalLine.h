#include <stdio.h>
#include <string.h>

void countPhysicalLines()
{
    char filename[] = "SourceCode.java"; // specify the file name here
    char line[10000];
    int physicalLines = 0;

    FILE* file = fopen(filename, "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            physicalLines++;
        }
        fclose(file);
    } else {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    printf("Physical lines: %d\n", physicalLines);
}
