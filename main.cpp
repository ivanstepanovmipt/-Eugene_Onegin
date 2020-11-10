#include "sort.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    //declare
    char* read_data = ReadText("Eugene_Onegin.txt");
    char** strings;
    int maxLineLength = 0;
    int* lineLengths;
    int lineCount = splitText(read_data, &strings, &lineLengths, &maxLineLength);
    char** originalLines = (unsigned char**)calloc(lineCount, sizeof(*originalLines));


    memcpy(originalLines, strings, lineCount * sizeof(*strings));
    sortStrings(lineCount, strings, lineLengths, maxLineLength, DIRECTION_FROMBEGIN);
    writeStrings("Begin.txt",strings, lineCount);
    memcpy(strings, originalLines, lineCount * sizeof(*originalLines));
    sortStrings(lineCount, strings, lineLengths, maxLineLength, DIRECTION_FROMEND);
    writeStrings("End.txt", strings, lineCount);
    writeText("Original_Eugene_Onegin.txt", read_data);

    //delete data

    free(read_data);
    free(strings);
    free(lineLengths);
    free(originalLines);
    return 0;
}
