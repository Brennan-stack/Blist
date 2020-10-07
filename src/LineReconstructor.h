#include <string.h>
/**
Responsible for reconstructing the input from the file.
Opens the file, uses eliminateSpecialChars, and returns
a char array representing the string which is read 
into the file. 
**/
char* reconstructFileInput(char* fileName);

/**
Eliminates whitespaces, comments, etc. from 
the input stream.
**/
char* eliminateSpecialChars(char* data);