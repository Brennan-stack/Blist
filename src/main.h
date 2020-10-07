#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//structure for input flags
struct _Flags {
	char* path;
	char** inputFiles;
	int numInputFiles;
	bool flagError;
	bool version;
	bool help;
	bool runInterpreted; 
};
typedef struct _Flags Flags;

Flags* getFlags(int argc, char** argv);
int cleanUp();
#endif