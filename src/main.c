#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "BListProgram.h"

int main(int argc, char** argv)
{
	Flags* flags = getFlags(argc, argv);
	for (int i = 0; i < flags->numInputFiles - 1; i++)
	{
		printf("%s\n", flags->inputFiles[i]);
		
	}

	if (flags->help)
	{
		printf("\nBList version %s", "0.0.1 Alpha.\n");
		printf("usage: blist [options] [source file] [options]\n");
		printf("options:\n");
		printf("-v\t displays the version of BList currently running\n");
		printf("-d\t displays debug information before running\n");
		printf("-h\t displays help information about the program\n\n");
	}

	if (flags->version)
	{
		
		printf("BList version %s", "0.0.1 Alpha.\n");
	}

	if (flags->runInterpreted)
	{
		printf("Running BList as interpreter.\n");
		executeBList(flags->numInputFiles, flags->inputFiles);
	}

	return 0;
}

/*
Returns all the flags which are present in the
command line call. 
*/
Flags* getFlags(int argc, char** argv)
{
	int fileCount = 1;
	Flags* flags = calloc(1, sizeof(Flags));
	flags->help = false;
	flags->version = false;
	flags->runInterpreted = false;
	flags->flagError = false;
	flags->inputFiles = calloc(10, sizeof(char*));
	//loop through argument count
	for (int i = 1; i < argc; i++)
	{
		char* arg = argv[i];
		if (strlen(arg) > 1 && *arg == '-')
		{
			char* flag = (arg + 1);
			if (*flag == 'v')
			{
				flags->version = true;
			}
			else if (*flag == 'h')
			{
				flags->help = true;
			}
			else if (*flag == 'i')
			{
				flags->runInterpreted = true;
			}
			else
			{
				//flag error, set error to true
				flags->flagError = true;
			}
		}
		else
		{
			flags->inputFiles = realloc(flags->inputFiles, fileCount * sizeof(char*));
			flags->inputFiles[fileCount-1] = arg;
			fileCount++;
		}
	}

	flags->numInputFiles = fileCount;

	return flags;
}


/**
Cleans up the program after done executing. 
**/
int cleanUp()
{

}