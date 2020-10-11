#include "BListProgram.h"
#include <stdio.h>
#include <stdlib.h>
#include "Lexer.h"
int executeBList(Flags* flags)
{
	//allocate char array
	char** fileContents = calloc(flags->numInputFiles, sizeof(char*));
	//setUpLexer();

	//first, we reconstruct the lines (eliminates whitespace and other non-essential characters)
	for (int i = 0; i < flags->numInputFiles - 1; i++)
	{
		//loop through input files, load file information into memory
		//ileContents[i] = reconstructFileInput(inputFiles[i]);
		//printf("fileContents for '%s' :: '%s'\n", inputFiles[i], fileContents[i]);
		lex(flags->inputFiles[i], flags->lexerDebug);
	}







}