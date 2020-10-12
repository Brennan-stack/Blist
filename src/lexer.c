#include "Lexer.h"
#include <stdio.h>
#include <string.h>
#include "uthash.h"
#include <ctype.h>
#include <time.h>

bool setup = false;
clock_t start, end;
double cpu_time_used;
CharType* chm = NULL;

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
			CharType* hm;
			int a = Operators[i].text[j];
			HASH_FIND_INT(chm, &a, hm);
			if (hm == NULL)
			{
				printf("added %c to map\n", Operators[i].text[j]);
				addToMap(Operators[i].text[j], Operators[i].tokenType);
			}
		}
	}
	
	addToMap('\n', NEW_LINE);
	addToMap(';', LINE_BREAK);
	addToMap(' ', WHITESPACE);
	addToMap('\t', WHITESPACE);
	addToMap('\r', NEW_LINE);
	addToMap('_', LETTER);
	addToMap('"', STRING_QUOTE);
	addToMap('{', DELIM);
	addToMap('}', DELIM);
	addToMap('\0', WHITESPACE);

	
	setup = true;

}


Token** lex(char* fileInput, bool debug)
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
	int tokenLength = 0;
	int fileNameSize = strlen(fileInput);

	Type type = WHITESPACE;
	start = clock();
	for (int i = 0; i <= fileSize; i++)
	{
		//ret[i] = getCharType(data, i);
		Type charType = getCharType(data, i, fileSize);
		Type tokenType = getTokenType(type, charType);
		//printf("%d: '%c' '%s' -- %s\n", i, data[i], getCharTypeToString(charType), getCharTypeToString(tokenType));

		if (tokenType != type)
		{
			if (tokenLength > 0)
			{
				if (type == COMMENT || type == BLOCK_COMMENT)
				{
					//we ignore comments
				} 
				else if (type == OPERATOR)
				{


					

					Operator* op = getOperatorFromMap(tokenLine);
					if (op != NULL)
					{
						Token* full = makeTokenFull(tokenLine, fileInput, tokenLength, fileNameSize, lineNum, charNum, op->tokenType, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;
					}
					else{

						if (tokenLength > 1)
						{
							char prev = tokenLine[0];
							int charCount = 0;
							int prevOffset = 0;
							
							for (int k = 0; k <= tokenLength; k++)
							{
								if (prev == tokenLine[k] && k != tokenLength)
								{
									charCount++;
								}
								else
								{
									char* sub = calloc(charCount + 1, sizeof(char));
									strncpy(sub, tokenLine + prevOffset, charCount);
									prevOffset += charCount;

									Operator* singleOp = getOperatorFromMap(sub);
									if (singleOp != NULL)
									{
										Token* f = makeTokenFull(sub, fileInput, tokenLength, fileNameSize, lineNum, prevOffset, singleOp->tokenType, *singleOp);
										ret = realloc(ret, count * sizeof(Token*));
										ret[count-1] = f;
										count++;
										free(sub);
									}
									else
									{
										for (int j = 0; j < charCount; j++)
										{
											char* m = calloc(1, sizeof(char));
											m[0] = sub[j];
											Operator* singleOp = getOperatorFromMap(m);
											if (singleOp != NULL)
											{
												Token* f = makeTokenFull(m, fileInput, tokenLength, fileNameSize, lineNum,  charNum, singleOp->tokenType, *singleOp);
												ret = realloc(ret, count * sizeof(Token*));
												ret[count-1] = f;
												count++;
												free(m);
												
									
											}
											else
											{
												printf("ERROR: INVALID TOKEN, ABORTING CODE");
												free(m);
												exit(1);
											}	
											k++;
										}
										free(sub);
										//exit(1);
									}	//*/	

									/*char* m = calloc(1, sizeof(char));
									m[0] = tokenLine[k];
									Operator* singleOp = getOperatorFromMap(m);
									if (singleOp != NULL)
									{
										Token* f = makeTokenFull(m, fileInput, tokenLength, fileNameSize, lineNum, charNum + k, OPERATOR, *singleOp);
										ret = realloc(ret, count * sizeof(Token*));
										ret[count-1] = f;
										count++;
									
									}
									else
									{
										printf("ERROR: INVALID TOKEN, ABORTING CODE");
										exit(1);
									}	*/			
									
								}
								
										
							}
								//printf("ERROR: INVALID TOKEN, ABORTING CODE");
								//exit(1);
							
							charCount = 0;
								
															
							
						}
						
					}
					
				}
				else 
				{
					Operator* op = getOperatorFromMap(tokenLine);
					//Keyword* kw;
					if (op != NULL)
					{
						Token* full = makeTokenFull(tokenLine, fileInput, tokenLength, fileNameSize, lineNum, charNum, op->tokenType, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;
					}
					/*else if ((kw = getKeywordFromMap(tokenLine)) != NULL)
					{
						/*
						Token* full = makeTokenFull(tokenLine, fileInput, lineNum, charNum, OPERATOR, *op);
						ret = realloc(ret, count * sizeof(Token*));
						ret[count-1] = full;
						count++;*/

					/*	Token* part = makeTokenPartial(tokenLine, fileInput, tokenLength, fileNameSize, lineNum, charNum, KEYWORD);
						ret = realloc(ret, count * sizeof(Token*));
						//printf("TOKEN COUNT: %s\n", tokenLine);
						ret[count - 1] = part;
						count++;
					}*/
					else
					{
					//printf("partial %s\n", tokenLine);
						Token* part = makeTokenPartial(tokenLine, fileInput, tokenLength, fileNameSize, lineNum, charNum, type);
						ret = realloc(ret, count * sizeof(Token*));
						//printf("TOKEN COUNT: %s\n", tokenLine);
						ret[count - 1] = part;
						count++;
					}
				}
			}
			free(tokenLine);
			tokenLine = calloc(1, sizeof(char));
			tokenLength = 0;
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
					tokenLine = realloc(tokenLine, (tokenLength + 2) * sizeof(char));
					tokenLine[tokenLength + 1] = '\0';
					tokenLine[tokenLength] = a;
					tokenLength++;
				}
				else if (data[i] == '\\')
				{
					a = '\\';
					tokenLine = realloc(tokenLine, (tokenLength + 2) * sizeof(char));
					tokenLine[tokenLength + 1] = '\0';
					tokenLine[tokenLength] = a;
					tokenLength++;
				}
				else if (data[i] == 't')
				{
					a = '\t';
					tokenLine = realloc(tokenLine, (tokenLength + 2) * sizeof(char));
					tokenLine[tokenLength + 1] = '\0';
					tokenLine[tokenLength] = a;
					tokenLength++;
				}
				else if( data[i] == '"')
				{
					a = '"';
					tokenLine = realloc(tokenLine, (tokenLength + 2) * sizeof(char));
					tokenLine[tokenLength + 1] = '\0';
					tokenLine[tokenLength] = a;
					tokenLength++;
				}
				else
				{
					printf("invalid escape error");
				}
			}
			else
			{
				
				char app = data[i];
				tokenLine = realloc(tokenLine, (tokenLength + 2) * sizeof(char));
				tokenLine[tokenLength + 1] = '\0';
				tokenLine[tokenLength] = app;
				tokenLength++;
				
				//strncat(tokenLine, &app, 5);
				//printf("LEN%d\n", strlen(tokenLine));
			}

		}
				type = tokenType;

		if (data[i] == '\n' || data[i] == '\r')
		{
			lineNum++;
			charNum = 1;
		}
		else
		{
			charNum++;
		}
	}

	end = clock();
	if (debug)
	{
		printf("\n\n ================================================================\n\t     LEXICAL ANALYSIS BREAKDOWN FOR \"%s\"\n ================================================================\n\n", fileInput);
		
		for (int i = 0; i < count - 1; i ++)
		{
			printf("\tSequence: %-15s\tType: %-15s\tLine: %-15d\tChar: %-15d\t\n",ret[i]->textIn, getCharTypeToString(ret[i]->tokenType), ret[i]->linePosIn, ret[i]->charPosIn);
		}
	}
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n\n ================================================================\n\tSuccessfully Parsed %d tokens in %lf seconds\n ================================================================\n", count, cpu_time_used);
	return ret;

}
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

Type getCharType(char* file, int index, int size)
{

	CharType* hm = calloc(1, sizeof(CharType));
	int c = file[index];
	bool lt = index < size - 1;
	switch(file[index])
	{
		case '/':
			if (lt && file[index + 1] == '/')
			{
				return SINGLE_COMMENT_START;
				
			}
			else if (lt && file[index + 1] == '*')
			{
				return BLOCK_COMMENT_START;
			
			}
			else if (index > 0 && file[index - 1] == '*')
			{
				return BLOCK_COMMENT_END;
				
			}
			break;

		case '.':
			if (lt)
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
			return LINE_BREAK;
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

		case DELIM:
			return DELIM;

		default:
			return UNKNOWN;
	}
}

