#ifndef TOKEN_H
#define TOKEN_H
#include "OperatorDef.h"
enum _Type {IDENTIFIER, 
			UNKNOWN, 
			COMMENT,
			SINGLE_COMMENT_START,
			BLOCK_COMMENT_START, 
			BLOCK_COMMENT_END,
			BLOCK_COMMENT,
			NEW_LINE,
			KEYWORD, 
			DELIM, 
			NUM, 
			OPERATOR, 
			LITERAL, 
			STRING_LITERAL, 
			LINE_END,
			LETTER, 
			WHITESPACE,
			LINE_BREAK,
			STRING_QUOTE};
typedef enum _Type Type;

struct _Token {
	Type tokenType;
	char* textIn;
	char* fileIn;
	int charPosIn;
	int linePosIn;
	Operator op;
};

typedef struct _Token Token;

Token* makeTokenFull(char* textIn, char* fileIn, int linePosIn, int charPosIn, Type type, Operator op);

Token* makeTokenPartial(char* textIn, Type type);

int identifyToken(char* textIn, char* fileIn, long charPos);
#endif