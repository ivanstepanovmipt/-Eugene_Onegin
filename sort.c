#include "sort.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>

bool istrue(unsigned char c){
    return ('a' <= c && c <= 'ÿ') || ('À' <= c && c <= 'ß');
}

char ReturnSymbol(int length, int index, unsigned char** current, int x){
    if (index >= length)
        return '\0';
    while (!istrue(**current)){
        *current += x;
    }
    unsigned char symbol = **current;
    *current += x;
    if ('À' <= symbol && symbol <= 'ß'){
        return (symbol - 'À' + 'a');
    }
    return symbol;
}

void swap(Line** first, Line** second){
    Line* tmp = *first;
    *first = *second;
    *second = tmp;
}

int sortStrings(int lineCount, unsigned char** strings, int* lineLengths, int maxLineLength, int x){
    int symbolCounts[256 + 1];
    Line* ls = (Line*)calloc(lineCount, sizeof(*ls));
    for (int i = 0; i < lineCount; ++i){
        ls[i].begin = strings[i];
        ls[i].length = lineLengths[i];
        if (x == DIRECTION_FROMBEGIN)
            ls[i].nextSymbol = strings[i + 1] - 1;
        else
            ls[i].nextSymbol = strings[i];
    }
    Line* lc = (Line*)calloc(lineCount, sizeof(*lc));
    for (int iter = maxLineLength - 1; iter >= 0; --iter){
        memset(symbolCounts, 0, sizeof(symbolCounts));
        for (int line = 0; line < lineCount; ++line){
            ls[line].currentSymbol = getSymbol(ls[line].length, iter, &ls[line].nextSymbol, x);
            ++symbolCounts[ls[line].currentSymbol + 1];
        }
        for (int i = 1; i < sizeof(symbolCounts) / sizeof(*symbolCounts); ++i){
            symbolCounts[i] += symbolCounts[i - 1];
        }
        for (int line = 0; line < lineCount; ++line){
            int newPosition = symbolCounts[ls[line].currentSymbol]++;
            lc[newPosition] = ls[line];
        }
        swap(&ls, &lc);
    }
    if (maxLineLength % 2 == 0){
        for (int i = 0; i < lineCount; ++i){
            strings[i] = ls[i].begin;
        }
    }
    else{
        for (int i = 0; i < lineCount; ++i){
            strings[i] = lc[i].begin;
        }
    }
    free(ls);
    free(lc);
    return 0;
}

char* readText(const char* filename){
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
char* buffer = (char*)calloc(size, sizeof(*buffer));
    fclose(file);
    return buffer;
}

void writeStrings(const char* filename, unsigned char** strings, int lineCount){
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < lineCount; ++i){
        size_t length;
        for (length = 0; strings[i][length] != '\n'; ++length);
    }
    fclose(file);
}

void writeText(const char* filename, const unsigned char* text){
    FILE* file = fopen(filename, "w");
    fclose(file);
}

int SplittingText(unsigned char* text, unsigned char*** strings, int** lineLengths, int* maxLineLength){

    int lineCount = 0;
    for (int i = 0; text[i] != '\0'; ++i)
        if (text[i] == '\n')
            ++lineCount;

    if (lineCount == 0)
    {
        lines = NULL;
        lineLengths = NULL;
        maxLineLength = 0;
        errno = EINVAL;
        return -1;
    }

    *strings = (unsigned char**)calloc(lineCount + 1, sizeof(**strings));
    *lineLengths = (int*)calloc(lineCount, sizeof(**lineLengths));
    *maxLineLength = 0;
    int lineLength = 0;
    (*strings)[0] = text;
    int ind = 1;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] == '\n')
        {
            if (lineLength == 0)
            {
                (*strings)[ind - 1] = text + i + 1;
                --lineCount;
            }
            else
            {
                (*lines)[ind] = text + i + 1;
                (*lineLengths)[ind - 1] = lineLength;
                ++ind;
            }
            if (lineLength > *maxLineLength)
                *maxLineLength = lineLength;
            lineLength = 0;
        }
        else if (istrue(text[i]))
            ++lineLength;
    }
    return lineCount;
}
