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
		printf("Error while opening file %s\nAborting compilation", fileName);
		exit(1);
	}

	//get the length of the file so we can store it in a char array
	fseek(filePath, 0, SEEK_END);
	long fileSize = ftell(filePath);
	fseek(filePath, 0, SEEK_SET);
	char* data = calloc(fileSize + 1, sizeof(char));
	fread(data, 1, fileSize, filePath);
	fclose(filePath);

	//char* reconstructedData = eliminateSpecialChars(data);
	//free data array
	//free(data);
	//return the reconstructed Data
	return data;
}

/**
Eliminates special characters such as whitespaces, comments, etc.
rom the input stream prior to processing. 
**/
char* eliminateSpecialChars(char* data)
{
	if(strlen(data) < 1) return data;
	//allocate new memory location for our string
	char* ret = calloc(2 * strlen(data), sizeof(char));
	ret[0] = data[0];
	long count = 0;
	bool singleQuote = false;
	bool multiQuote = false;
	//loop through each character in the input stream, if special remove. 
	for (int i = 0; i < strlen(data) - 1; i++)
	{
		char next = data[i+1];
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
					if (next != ' ')
					{
						ret = realloc(ret, (count + 1) * sizeof(char));
						ret[count] = current;
						count++;
					}
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
					if (next == '/')
					{
						singleQuote = true;
					}
					//test for multiline comment
					if (next == '*')
					{
						multiQuote = true;
					}
				break;

				case '(':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case ')':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;
				
				case '[':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;
				
				case ']':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case '{':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case '}':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case ';':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case ':':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case '=':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				case '#':
					ret = realloc(ret, (count + 3) * sizeof(char));
					ret[count] = ' ';
					count++;
					ret[count] = current;
					count++;
					ret[count] = ' ';
					count++;
				break;

				default:
					//default, set character to current.
					ret = realloc(ret, (count + 1) * sizeof(char));
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
		if (multiQuote && (current == '*' && next == '/'))
		{
			multiQuote = false;
		}

	}
	ret = realloc(ret, count * sizeof(char) + 1);
	ret[count] = '\0';

	return ret;

	
}

