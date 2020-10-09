#include "Lexer.h"
#include <stdio.h>
#include <string.h>
#include "uthash.h"
#include <ctype.h>
bool setup = false;
void setUpLexer()
{

	for(char c = 'a'; c <= 'z'; c++)
	{
		addToMap(c, LETTER);
	}

	for (char c = '0'; c < '9'; c++)
	{
		addToMap(c, NUM);
	}

	for(char c = 'A'; c <= 'Z'; c++)
	{
		addToMap(c, LETTER);
	}

	for (int i = 0; i < NUMOPERATORS; i++)
	{
		for (int j = 0; j < strlen(Operators[i].text); j++)
		{
			addToMap(Operators[i].text[j], OPERATOR);
		}
	}
	
	addToMap('\n', NEW_LINE);
	addToMap(';', LINE_BREAK);
	addToMap(' ', WHITESPACE);
	addToMap('\t', WHITESPACE);
	addToMap('\r', WHITESPACE);
	addToMap('_', LETTER);
	addToMap('"', STRING_QUOTE);
	addToMap('{', DELIM);
	addToMap('}', DELIM);
	addToMap('\0', WHITESPACE);

	
	setup = true;

}


Token** lex(char* fileInput)
{
	if (!setup)
	{
		setUpLexer();
		populateOperators();
		populateKeywords();
	}
	char* delims = " ";


	FILE* filePath;
	filePath = fopen(fileInput, "r");

	if (filePath == NULL)
	{
		printf("Error while opening file %s\nAborting compilation", fileInput);
		exit(1);
	}

	//get the length of the file so we can store it in a char array
	fseek(filePath, 0, SEEK_END);
	long fileSize = ftell(filePath);
	fseek(filePath, 0, SEEK_SET);
	char* data = calloc(fileSize, sizeof(char));
	fileSize = fread(data, 1, fileSize, filePath);
	fclose(filePath);
	data = realloc(data, fileSize * sizeof(char));


	Token** ret = calloc(1, sizeof(Token*));
	int lineNum = 1;
	int charNum = 1;
	char* tokenLine = calloc(1, sizeof(char));
	int count = 1;

	Type type = WHITESPACE;

	for (int i = 0; i < fileSize; i++)
	{
		//ret[i] = getCharType(data, i);
		Type charType = getCharType(data, i);
		Type tokenType = getTokenType(type, charType);
		//printf("%d: '%c' '%s' -- %s\n", i, data[i], getCharTypeToString(charType), getCharTypeToString(tokenType));

		if (tokenType != type)
		{

			if (strlen(tokenLine) > 0)
			{


				if (type == COMMENT || type == BLOCK_COMMENT)
				{
					//we ignore comments
				} else if (type == OPERATOR)
				{

					Operator* op = getOperatorFromMap(tokenLine);
					if (op != NULL)
					{
						Token* full = makeTokenFull(tokenLine, fileInput, lineNum, charNum, OPERATOR, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;
					}
					else{
						int currentCount = count;
						if (strlen(tokenLine) > 1)
						{
							for (int j = 0; j < strlen(tokenLine); j++)
							{
								char* l = calloc(1, sizeof(char));
								l[0] = tokenLine[j];
								Operator* singleOp = getOperatorFromMap(l);
								if (singleOp != NULL)
								{
									Token* f = makeTokenFull(l, fileInput, lineNum, charNum + j, OPERATOR, *singleOp);
									ret = realloc(ret, count * sizeof(Token*));
									ret[count-1] = f;
									count++;
									
								}
								else
								{
									printf("ERROR: INVALID TOKEN, ABORTING CODE");
									exit(1);
								}
							}
						}
						
					}
					
				}
				else 
				{
					Operator* op = getOperatorFromMap(tokenLine);
					Keyword* kw;
					if (op != NULL)
					{
						Token* full = makeTokenFull(tokenLine, fileInput, lineNum, charNum, OPERATOR, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;
					}
					else if ((kw = getKeywordFromMap(tokenLine)) != NULL)
					{
						/*
						Token* full = makeTokenFull(tokenLine, fileInput, lineNum, charNum, OPERATOR, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;*/

						Token* part = makeTokenPartial(tokenLine, KEYWORD);
						ret = realloc(ret, count * sizeof(Token*));
						//printf("TOKEN COUNT: %s\n", tokenLine);
						ret[count - 1] = part;
						count++;
					}
					else
					{
					//printf("partial %s\n", tokenLine);
					Token* part = makeTokenPartial(tokenLine, IDENTIFIER);
					ret = realloc(ret, count * sizeof(Token*));
					//printf("TOKEN COUNT: %s\n", tokenLine);
					ret[count - 1] = part;
					count++;
					}
				}
			}
			free(tokenLine);
			tokenLine = calloc(1, sizeof(char));
			//tokenLine = realloc(tokenLine, sizeof(char));
		}

		if (tokenType != WHITESPACE && tokenType != LINE_END)
		{
			if (tokenType == STRING_LITERAL && data[i]=='\\')
			{
				i++;
				char a;
				if (data[i] =='n')
				{
					a = '\n';
					int len = strlen(tokenLine);
					tokenLine = realloc(tokenLine, (len + 2) * sizeof(char));
					tokenLine[len + 1] = '\0';
					tokenLine[len] = a;
				}
				else if (data[i] == '\\')
				{
					a = '\\';
					int len = strlen(tokenLine);
					tokenLine = realloc(tokenLine, (len + 2) * sizeof(char));
					tokenLine[len + 1] = '\0';
					tokenLine[len] = a;
				}
				else if (data[i] == 't')
				{
					a = '\t';
					int len = strlen(tokenLine);
					tokenLine = realloc(tokenLine, (len + 2) * sizeof(char));
					tokenLine[len + 1] = '\0';
					tokenLine[len] = a;
				}
				else if( data[i] == '"')
				{
					a = '"';
					int len = strlen(tokenLine);
					tokenLine = realloc(tokenLine, (len + 2) * sizeof(char));
					tokenLine[len + 1] = '\0';
					tokenLine[len] = a;
				}
				else
				{
					printf("invalid escape error");
				}
			}
			else
			{
				char app = data[i];
				int len = strlen(tokenLine);
				tokenLine = realloc(tokenLine, (len + 2) * sizeof(char));
				tokenLine[len + 1] = '\0';
				tokenLine[len] = app;

				//strncat(tokenLine, &app, 5);
				//printf("LEN%d\n", strlen(tokenLine));
			}
		}



		if (data[i] == '\n')
		{
			lineNum++;
			charNum = 1;
		}
		else
		{
			charNum++;
		}

		type = tokenType;

	}


	printf("\n\n\n\n\t\tLEXICAL ANALYSIS BREAKDOWN\n =======================================================\n");
	for (int i = 0; i < count - 1; i ++)
	{
		printf("\tname: %-15s\t type: %-15s\n",ret[i]->textIn, getCharTypeToString(ret[i]->tokenType));
	}
	
	//printf("COUNT: %d\n", count);
	return ret;

}

CharType* chm = NULL;

void addToMap(char charac, Type type)
{
	int temp = charac;
	CharType* c = calloc(1, sizeof(CharType));
	c->character = charac;
	c->index = temp;
	c->type = type;
	HASH_ADD_INT(chm, index, c);
}

char* getCharTypeToString(Type st)
{
	switch(st)
	{
		case IDENTIFIER:
			return "identifier";
		break;
		case WHITESPACE:
			return "whitespace";
		break;
		case LETTER:
			return "letter";
		break;
		case LINE_END:
			return "line end";
		break;
		case NEW_LINE:
			return "new line";
		break;
		case STRING_LITERAL:
			return "string literal";
		break;
		case LITERAL:
			return "literal";
		break;
		case OPERATOR:
			return "operator";
		break;
		case NUM:
			return "number";
		break;
		case DELIM:
			return "delimiter";
		break;
		case KEYWORD:
			return "keyword";
		break;
		case BLOCK_COMMENT_START:
			return "block comment start";
		break;
		case BLOCK_COMMENT_END:
			return "block comment end";
		break;
		case SINGLE_COMMENT_START:
			return "single comment start";
		break;
		case BLOCK_COMMENT:
			return "block comment";
		break;
		case COMMENT:
			return "comment";
		break;
		case STRING_QUOTE:
			return "string quote";
		break;
		case LINE_BREAK:
			return "line break";
		default:
			return "unknown";
		break;
	}
}

Type getCharType(char* file, int index)
{

	CharType* hm = calloc(1, sizeof(CharType));
	int c = file[index];
	switch(file[index])
	{
		case '/':
			if (index< (strlen(file) - 1) && file[index + 1] == '/')
			{
				return SINGLE_COMMENT_START;
				
			}
			else if (index < (strlen(file) - 1) && file[index + 1] == '*')
			{
				return BLOCK_COMMENT_START;
			
			}
			else if (index > 0 && file[index - 1] == '*')
			{
				return BLOCK_COMMENT_END;
				
			}
			break;

		case '.':
			if (index < (strlen(file) - 1))
			{
				int c2 = file[index + 1];
				HASH_FIND_INT(chm, &c2, hm);
				if (hm != NULL)
				{
					if (hm->type == NUM)
					{
						return NUM;
					}
				}
				else
				{
					printf("NULL");
				}
			}

	}

	//look in hash table for it, if not found return null
	HASH_FIND_INT(chm, &c, hm);
	if (hm == NULL)
	{

		return UNKNOWN;
	}
	return hm->type;

}

Type getTokenType(Type prevType, Type nextType)
{
	if (prevType == COMMENT)
	{
		if (nextType == NEW_LINE)
		{
			return WHITESPACE;
		}
		return COMMENT;
	}

	if (prevType == BLOCK_COMMENT)
	{
		if (nextType == BLOCK_COMMENT_END)
		{
			return WHITESPACE;
		}
		return BLOCK_COMMENT;
	}

	if (prevType == STRING_LITERAL)
	{
		if (nextType == STRING_QUOTE)
		{
			return WHITESPACE;
		}
		return STRING_LITERAL;
	}

	switch (nextType)
	{
		case SINGLE_COMMENT_START:
			return COMMENT;

		case BLOCK_COMMENT_START:
			return BLOCK_COMMENT;

		case BLOCK_COMMENT_END:
			printf("comment eneded without start");
			return UNKNOWN;

		case WHITESPACE:
			return WHITESPACE;

		case LINE_BREAK:
		case NEW_LINE:
			return LINE_END;

		case OPERATOR:
			return OPERATOR;

		case LETTER:
		case NUM:
			if (prevType == IDENTIFIER || prevType == LITERAL)
				return prevType;
			else if (nextType == NUM)
				return LITERAL;
			return IDENTIFIER;

		case STRING_QUOTE:
			return STRING_LITERAL;

		default:
			return UNKNOWN;
	}
}

