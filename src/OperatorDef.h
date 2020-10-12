#ifndef OPERATORDEF_H
#define OPERATORDEF_H
#include "Operator.h"
#include <stdlib.h>
#include <stdbool.h>
#define NUMOPERATORS 50
#define NUMMULTIOPERATORS 18
#include "uthash.h"
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
struct _Operator {
	char* name;
	char* text;
	int precedence;
	InputTaken input; 
	Type tokenType;
	bool overload;
	UT_hash_handle hh;
};

typedef struct _Operator Operator;

static Operator Operators[NUMOPERATORS] = {

	{"colon",			":",			8,			BOTH,		OPERATOR,			false},	//for function declarations
	{"comma",			",",			30,			BOTH,		OPERATOR,			false}, //for declaration of multiple variables
	{"equal",			"=",			15,			BOTH,		OPERATOR,			true},
	{"greater",			">",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"less",			"<",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"plus",			"+",			55,			BOTH,		OPERATOR,			true}, //for addition
	{"minus",			"-",			55,			BOTH,		OPERATOR,			true}, //for subtraction
	{"multiply",		"*",			60,			BOTH,		OPERATOR,			true}, //for multiplication
	{"divide",			"/",			60,			BOTH,		OPERATOR,			true}, //for division
	{"mod",				"%",			59,			BOTH,		OPERATOR,			true}, //for mod
	{"notOp",			"!",			70,			RIGHT,		OPERATOR,			true}, //for not boolean inversion
	{"dot",				".",			80,			BOTH,		OPERATOR,			false}, //for subselection
	{"hashTag",			"#",			90,			RIGHT,		OPERATOR,			false}, //for include/exclude/select/setstate
	{"openPeren",		"(",			100,		BOTH,		OPERATOR,			false}, //for function declarations/mathematics
	{"closePeren",		")",			99,			BOTH,		OPERATOR,			false}, //for function declarations/mathematics
	{"openSqBrkt",		"[",			100,		BOTH,		OPERATOR,			false}, //for array declarations
	{"closeSqBrkt",		"]",			99,			BOTH,		OPERATOR,			false}, //for array declarations
	{"forloop",			"for",			5,			RIGHT,		OPERATOR,			false}, //for for loop
	{"whileloop",		"while",		5,			RIGHT,		OPERATOR,			false}, //for for loop
	{"switch",			"switch",		6,			RIGHT,		OPERATOR,			false}, //for for loop
	{"ifOp",			"if",			6,			RIGHT,		OPERATOR,			false}, //for if statements
	{"orOp",			"||",			35,			BOTH,		OPERATOR,			false}, //for boolean or
	{"andOp",			"&&",			36,			BOTH,		OPERATOR,			false}, //for boolean and
	{"equal",			"==",			40,			BOTH,		OPERATOR,			true}, //for comp
	{"notEqual",		"!=",			40,			BOTH,		OPERATOR,			false}, //for comp
	{"greaterEq",		">=",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"lessEq",			"<=",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"greaterEq",		">=",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"lessEq",			"<=",			50,			BOTH,		OPERATOR,			true}, //for comp
	{"plusPlus",		"++",			75,			LEFT,		OPERATOR,			false}, //for adding
	{"minusMinus",		"--",			75,			LEFT,		OPERATOR,			false}, //for subtracting
	{"rightArrow",		"->",			80,			BOTH,		OPERATOR,			false}, //for pointer selection
	{"shiftLeft",		"<<",			85,			BOTH,		OPERATOR,			false}, //for bit shifting left
	{"shiftRight",		">>",			85,			BOTH,		OPERATOR,			false}, //for bit shifting right

	//data types
	{"var",				"var",			0,			BOTH,		KEYWORD,			false},
	{"integer",			"int",			0,			BOTH,		KEYWORD,			false},
	{"float",			"float",		0,			BOTH,		KEYWORD,			false},
	{"long",			"long",			0,			BOTH,		KEYWORD,			false},
	{"character",		"char",			0,			BOTH,		KEYWORD,			false},
	{"double",			"double",		0,			BOTH,		KEYWORD,			false},
	{"string",			"String",		0,			BOTH,		KEYWORD,			false},
	{"void",			"void",			0,			BOTH,		KEYWORD,			false},
	//static types
	{"include",			"include",		0,			BOTH,		KEYWORD,			false},
	{"setState",		"setState",		0,			BOTH,		KEYWORD,			false},
	{"endState",		"endState",		0,			BOTH,		KEYWORD,			false},
	{"select",			"select",		0,			BOTH,		KEYWORD,			false},
	//modifiers
	{"static",			"static",		0,			BOTH,		KEYWORD,			false},
	{"global",			"global",		0,			BOTH,		KEYWORD,			false},
	{"mutable",			"mutable",		0,			BOTH,		KEYWORD,			false},
	{"immutable",		"immutable",	0,			BOTH,		KEYWORD,			false},




};
/*
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
	{"immutable",	"immutable",	15,		false},*/


static Operator MultiOperators[NUMMULTIOPERATORS] = {


};

void addToOperatorMap(Operator* op);

Operator* getOperatorFromMap(char* sequence);

void populateOperators();

//void createOperator(char* name, char* text, int precedence, InputTaken input, bool overload);



#endif