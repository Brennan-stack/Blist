#ifndef LEXER_H
#define LEXER_H
#include "uthash.h"
#include "OperatorDef.h"

enum _CharType {LETTER, DIGIT, OPERATOR, UNKNOWN};
typedef enum _CharType CharType;

struct _CharHashMap {
	int hashId;
	char character;
	CharType type;
	UT_hash_handle hh;
};
typedef struct _CharHashMap CharHashMap;

void addToCharMap(char character, CharType type);
CharHashMap* getCharType(int c);
void setUpLexer();

#endif