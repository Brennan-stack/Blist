#ifndef TOKEN_H
#define TOKEN_H
#include "OperatorDef.h"


struct _Token {
	Type tokenType;
	char* textIn;
	char* fileIn;
	int charPosIn;
	int linePosIn;
	Operator op;

};

typedef struct _Token Token;

Token* makeTokenFull(char* textIn, char* fileIn, int textInSize, int fileInSize, int linePosIn, int charPosIn, Type type, Operator op);

Token* makeTokenPartial(char* textIn, char* fileIn, int textInSize, int fileInSize, int linePosIn, int charPosIn, Type type);

int identifyToken(char* textIn, char* fileIn, long charPos);
#endif