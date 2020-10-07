#include "LineReconstructor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char* reconstructFileInput(char* fileName)
{
	FILE* filePath;
	filePath = fopen(fileName, "r");

	if (filePath == NULL)
	{
		printf("Error while opening file %s\n Aborting compilation", fileName);
		exit(1);
	}

	//get the length of the file so we can store it in a char array
	fseek(filePath, 0, SEEK_END);
	long fileSize = ftell(filePath);
	fseek(filePath, 0, SEEK_SET);

	char* data = calloc(fileSize + 1, sizeof(char));
	fread(data, 1, fileSize, filePath);
	char* reconstructedData = eliminateSpecialChars(data);
	//free data array
	free(data);

	for (int i = 0; i < strlen(reconstructedData); i++)
	{
		printf("inputchar: %c %d\n", reconstructedData[i], i);
	}

	return reconstructedData;

}



/**
Eliminates special characters such as whitespaces, comments, etc.
rom the input stream prior to processing. 
**/
char* eliminateSpecialChars(char* data)
{
	if(strlen(data) < 1) return data;
	//allocate new memory location for our string
	char* ret = calloc(strlen(data), sizeof(char));
	ret[0] = data[0];
	long count = 1;
	bool singleQuote = false;
	bool multiQuote = false;
	//loop through each character in the input stream, if special remove. 
	for (int i = 1; i < strlen(data); i++)
	{
		char prev = data[i-1];
		char current = data[i];
		
		/**
		Special characters: 
		" ", "\n", "\t", "//", "/*", "* /",
		**/
		if (!singleQuote && !multiQuote)
		{
			switch(current)
			{
				case ' ':
					//do nothing, character not counted
				break;

				case '\n':
					//do nothing, character not counted
				break;

				case '\t':
					//do nothing, character not counted
				break;

				case '/':
					//test for single line comment
					if (prev == '/')
					{
						singleQuote = true;
					}
				break;

				case '*':
					//test for multiline comment
					if (prev == '/')
					{
						multiQuote = true;
					}
				break;

				default:
					//default, set character to current.
					ret[count] = current;
					count++;
				break;
			}
		}
		//check to see if single line comment ended
		if (singleQuote && current == '\n')
		{
			singleQuote = false;
		}
		//check to see if multi-line comment ended
		if (multiQuote && (current == '/' && prev == '*'))
		{
			multiQuote = false;
		}

	}

	ret = realloc(ret, count * sizeof(char));
	ret[count] = '\0';

	return ret;

	
}