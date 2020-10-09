#include "ResolveKeywords.h"

Keyword* kwHash = NULL;
void addToKeywordMap(Keyword* kw)
{
	HASH_ADD_STR(kwHash, text, kw);
}

Keyword* getKeywordFromMap(char* sequence)
{
	Keyword* temp;
	HASH_FIND_STR(kwHash, sequence, temp);

	return temp;
}

void populateKeywords()
{
	for (int i = 0; i < NUMKEYWORDS; i++)
	{
		addToKeywordMap(&Keywords[i]);
	}
}