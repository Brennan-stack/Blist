#ifndef OPERATORDEF_H
#define OPERATORDEF_H
#include "Operator.h"
#include <stdlib.h>
#include <stdbool.h>
#define NUMOPERATORS 34
#define NUMMULTIOPERATORS 18
#include "uthash.h"

struct _Operator {
	char* name;
	char* text;
	int precedence;
	InputTaken input; 
	bool overload;
	UT_hash_handle hh;
};

typedef struct _Operator Operator;

static Operator Operators[NUMOPERATORS] = {

	{"colon",			":",			8,			BOTH,			false},	//for function declarations
	{"comma",			",",			30,			BOTH,			false}, //for declaration of multiple variables
	{"equal",			"=",			15,			BOTH,			true},
	{"greater",			">",			50,			BOTH,			true}, //for comp
	{"less",			"<",			50,			BOTH,			true}, //for comp
	{"plus",			"+",			55,			BOTH,			true}, //for addition
	{"minus",			"-",			55,			BOTH,			true}, //for subtraction
	{"multiply",		"*",			60,			BOTH,			true}, //for multiplication
	{"divide",			"/",			60,			BOTH,			true}, //for division
	{"mod",				"%",			59,			BOTH,			true}, //for mod
	{"notOp",			"!",			70,			RIGHT,			true}, //for not boolean inversion
	{"dot",				".",			80,			BOTH,			false}, //for subselection
	{"hashTag",			"#",			90,			RIGHT,			false}, //for include/exclude/select/setstate
	{"openPeren",		"(",			100,		BOTH,			false}, //for function declarations/mathematics
	{"closePeren",		")",			99,			BOTH,			false}, //for function declarations/mathematics
	{"openSqBrkt",		"[",			100,		BOTH,			false}, //for array declarations
	{"closeSqBrkt",		"]",			99,			BOTH,			false}, //for array declarations
	{"forloop",			"for",			5,			RIGHT,			false}, //for for loop
	{"whileloop",		"while",		5,			RIGHT,			false}, //for for loop
	{"switch",			"switch",		6,			RIGHT,			false}, //for for loop
	{"ifOp",			"if",			6,			RIGHT,			false}, //for if statements
	{"orOp",			"||",			35,			BOTH,			false}, //for boolean or
	{"andOp",			"&&",			36,			BOTH,			false}, //for boolean and
	{"equal",			"==",			40,			BOTH,			true}, //for comp
	{"notEqual",		"!=",			40,			BOTH,			false}, //for comp
	{"greaterEq",		">=",			50,			BOTH,			true}, //for comp
	{"lessEq",			"<=",			50,			BOTH,			true}, //for comp
	{"greaterEq",		">=",			50,			BOTH,			true}, //for comp
	{"lessEq",			"<=",			50,			BOTH,			true}, //for comp
	{"plusPlus",		"++",			75,			LEFT,			false}, //for adding
	{"minusMinus",		"--",			75,			LEFT,			false}, //for subtracting
	{"rightArrow",		"->",			80,			BOTH,			false}, //for pointer selection
	{"shiftLeft",		"<<",			85,			BOTH,			false}, //for bit shifting left
	{"shiftRight",		">>",			85,			BOTH,			false}, //for bit shifting right

};

static Operator MultiOperators[NUMMULTIOPERATORS] = {


};

void addToOperatorMap(Operator* op);

Operator* getOperatorFromMap(char* sequence);

void populateOperators();

//void createOperator(char* name, char* text, int precedence, InputTaken input, bool overload);



#endif