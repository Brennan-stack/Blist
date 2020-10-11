#ifndef RESOLVEKEYWORDS_H
#define RESLOVEKEYWORDS_H
#define NUMKEYWORDS 16
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
	{"long",		"long",			3,		false},
	{"character",	"char",			4,		false},
	{"double",		"double",		5,		false},
	{"string",		"String",		6,		false},
	{"void",		"void",			7,		false},
	//static types
	{"include",		"include",		8,		false},
	{"setState",	"setState",		9,		false},
	{"endState",	"endState",		10,		false},
	{"select",		"select",		11,		false},
	//modifiers
	{"static",		"static",		12,		false},
	{"global",		"global",		13,		false},
	{"mutable",		"mutable",		14,		false},
	{"immutable",	"immutable",	15,		false},

};

void addToKeywordMap(Keyword* kw);

Keyword* getKeywordFromMap(char* sequence);

void populateKeywords();

#endif