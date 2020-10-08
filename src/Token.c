#include "Token.h"
#include <string.h>


Token* makeTokenFull(char* textIn, char* fileIn, long charPos, TokenType type, Operator op)
{
	Token* ret = calloc(1, sizeof(Token));
	ret->type = type;
	ret->text = textIn;
	ret->fileIn = fileIn;
	ret->charPos = charPos;
	ret->op = op;
	return ret;
}

Token* makeTokenPartial(char* textIn)
{
	Token* ret = calloc(1, sizeof(Token));
	ret->type = IDENTIFIER;
	ret->text = textIn;
	ret->fileIn = NULL;
	ret->charPos = 0;
	return ret;
}

int identifyToken(char* textIn, char* fileIn, long charPos){
	//loop through the array
	Operator* op = NULL;
	
	
	return 0;
}