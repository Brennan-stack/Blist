#include "BListProgram.h"
#include "LineReconstructor.h"
#include <stdio.h>
#include <stdlib.h>
#include "Lexer.h"
int executeBList(int numInputFiles, char** inputFiles)
{
	//allocate char array
	char** fileContents = calloc(numInputFiles, sizeof(char*));

	//first, we reconstruct the lines (eliminates whitespace and other non-essential characters)
	for (int i = 0; i < numInputFiles - 1; i++)
	{
		//loop through input files, load file information into memory
		fileContents[i] = reconstructFileInput(inputFiles[i]);
		printf("fileContents for '%s' :: '%s'\n", inputFiles[i], fileContents[i]);
	}

	setUpLexer();






}