#include "OperatorDef.h"
//instantiate ophash
Operator* opHash = NULL;

void addToOperatorMap(Operator* op)
{
	HASH_ADD_STR(opHash, text, op);
	//printf("added op");
}

Operator* getOperatorFromMap(char* sequence)
{
	Operator* temp;
	HASH_FIND_STR(opHash, sequence, temp);

	return temp;
}

void populateOperators()
{
	for (int i = 0; i < NUMOPERATORS; i++)
	{
		addToOperatorMap(&Operators[i]);
	}
}

/*
void createOperator(char* name, char* text, int precedence, InputTaken input, bool overload)
{
	Operator* op = calloc(1, sizeof(Operator));
	op->name = name;
	op->text = text;
	op->precedence = precedence;
	op->input = input;
	op->overload = overload;

	addToOperatorMap(op);
}*/