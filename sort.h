typedef struct
{
    char* begin;
    int length;
    char currentSymbol;
    char* nextSymbol;

} Line;

bool istrue(unsigned char c);

char ReturnSymbol(int length, int index, unsigned char** current, int x);
/**
    return Symbol
*/

int sortStrings(int lineCount, unsigned char** strings, int* lineLengths, int maxLineLength, int x);
/**
    Splits lines into poems, returns the number of lines
*/

void swap(Line** first, Line** second);
/**
    swap
*/

int SplittingText(unsigned char* text, unsigned char*** strings, int** lineLengths, int* maxLineLength);
/**
    Reads text from a file
*/

char* readText(const char* filename);

void writeStrings(const char* filename, unsigned char** strings, int lineCount);

void writeText(const char* filename, const unsigned char* text);
