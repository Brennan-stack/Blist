#ifndef LEXER_H
#define LEXER_H
#include "uthash.h"
#include "OperatorDef.h"
#include "Token.h"
#include "ResolveKeywords.h"
/*
enum _CharType {TYPE, DIGIT, OPERATOR, UNKNOWN, IDENTIFIER, KEYWORD, LITERAL, STRING_LITERAL, END_OF_LINE};
typedef enum _CharType CharType;*/

struct _CharType {
	int index;
	char character;
	Type type;
	UT_hash_handle hh;
};
typedef struct _CharType CharType;

void addToMap(char charac, Type type);

Type getCharType(char* file, int index);

void setUpLexer();

Token** lex(char* fileInput);

char* getCharTypeToString(Type st);

Type getTokenType(Type prevType, Type nextType);

#endif