#include "Token.h"
#include <string.h>
#include <stdio.h>


Token* makeTokenFull(char* textIn, char* fileIn, int textInSize, int fileInSize, int linePosIn, int charPosIn, Type type, Operator op)
{
	Token* ret = calloc(1, sizeof(Token));
	ret->tokenType = type;
	ret->textIn = calloc(textInSize + 1, sizeof(char));
	strcpy(ret->textIn, textIn);
	ret->fileIn = calloc(fileInSize + 1, sizeof(char));
	strcpy(ret->fileIn, fileIn);
	ret->linePosIn = linePosIn;
	ret->charPosIn = charPosIn;
	ret->op = op;
	return ret;
}

Token* makeTokenPartial(char* textIn, char* fileIn, int textInSize, int fileInSize, int linePosIn, int charPosIn, Type type)
{

	Token* ret = calloc(1, sizeof(Token));
	if (ret == NULL)
	{
		printf("failed to allocate from stack");
	}
	ret->tokenType = type;
	ret->textIn = calloc(textInSize + 1, sizeof(char));
	strcpy(ret->textIn, textIn);	
	ret->linePosIn = linePosIn;
	ret->charPosIn = charPosIn;
	ret->fileIn = calloc(fileInSize + 1, sizeof(char));
	strcpy(ret->fileIn, fileIn);
	return ret;
}

int identifyToken(char* textIn, char* fileIn, long charPos){
	//loop through the array
	Operator* op = NULL;
	
	
	return 0;
}