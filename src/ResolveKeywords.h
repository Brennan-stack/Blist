#ifndef RESOLVEKEYWORDS_H
#define RESLOVEKEYWORDS_H
#define NUMKEYWORDS 15
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
	//variables/return types
	{"var",			"var",			0,		true},
	{"integer",		"int",			1,		false},
	{"float",		"float",		2,		false},
	{"character",	"char",			3,		false},
	{"double",		"double",		4,		false},
	{"string",		"String",		5,		false},
	{"void",		"void",			6,		false},
	//static types
	{"include",		"include",		7,		false},
	{"setState",	"setState",		8,		false},
	{"endState",	"endState",		9,		false},
	{"select",		"select",		10,		false},
	//modifiers
	{"static",		"static",		11,		false},
	{"global",		"global",		12,		false},
	{"mutable",		"mutable",		13,		false},
	{"immutable",	"immutable",	14,		false},

};

void addToKeywordMap(Keyword* kw);

Keyword* getKeywordFromMap(char* sequence);

void populateKeywords();

#endif