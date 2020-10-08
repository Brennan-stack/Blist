#include "Lexer.h"
#include <stdio.h>
#include "uthash.h"

void setUpLexer()
{
	printf("Setting up lexer");
	addToCharMap('a', LETTER);
	printf("added to char");
	CharHashMap* hm = getCharType('a');
	printf("found");
	printf("\n%c\n", hm->character);
}

CharHashMap* chm = NULL;

void addToCharMap(char charac, CharType type)
{
	printf("\n%d\n", charac);
	CharHashMap* c = calloc(1, sizeof(CharHashMap*));
	c->character = charac;
	c->hashId = charac;
	c->type = type;
	HASH_ADD_INT(chm, hashId, c);
}

CharHashMap* getCharType(int c)
{
	printf("%d\n", &c);
	CharHashMap* hm;
	HASH_FIND_INT(chm, &c, hm);
	return hm;
}