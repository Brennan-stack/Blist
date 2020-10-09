#ifndef RESOLVEKEYWORDS_H
#define RESLOVEKEYWORDS_H
#define NUMKEYWORDS 14
#include "uthash.h"
#include <stdlib.h>
#include <stdbool.h>
struct _Keyword {
	char* name;
	char* text;
	int	id;
	bool mutable;
	UT_hash_handle hh;
};
typedef struct _Keyword Keyword;

static Keyword Keywords[NUMKEYWORDS] = {
	//variables
	{"var",			"var",			0,		true},
	{"integer",		"int",			1,		false},
	{"float",		"float",		2,		false},
	{"character",	"char",			3,		false},
	{"double",		"double",		4,		false},
	{"string",		"String",		5,		false},
	//static types
	{"include",		"include",		6,		false},
	{"setState",	"setState",		7,		false},
	{"endState",	"endState",		8,		false},
	{"select",		"select",		9,		false},
	//modifiers
	{"static",		"static",		10,		false},
	{"global",		"global",		11,		false},
	{"mutable",		"mutable",		12,		false},
	{"immutable",	"immutable",	13,		false},

};

void addToKeywordMap(Keyword* kw);

Keyword* getKeywordFromMap(char* sequence);

void populateKeywords();

#endif