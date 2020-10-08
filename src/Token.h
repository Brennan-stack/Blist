#ifndef TOKEN_H
#define TOKEN_H
#include "OperatorDef.h"
enum _TokenType {IDENTIFIER, CAST, LETTER, DIGIT, OPERATOR, LINE_END, STRING_LITERAL, SCOPE};
typedef enum _TokenType TokenType;

struct _Token {
	TokenType type;
	char* text;
	char* fileIn;
	long charPos;
	Operator op;
};

typedef struct _Token Token;

Token* makeTokenFull(char* textIn, char* fileIn, long charPos, TokenType type, Operator op);

Token* makeTokenPartial(char* textIn);

int identifyToken(char* textIn, char* fileIn, long charPos);
#endif