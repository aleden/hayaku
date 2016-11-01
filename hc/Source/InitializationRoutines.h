#pragma once
#include "Common.h"
#include <stdio.h>

char* IsSourceFilePathInArguments(int argc, char** argv);
char* IsExecutableFilePathInArguments(int argc, char** argv);
void ParseFile(FILE* file);
void PrintHelp();

#if 1
	#define DetermineSourceFilePath()\
		if (!(sourceFilePath = IsSourceFilePathInArguments(argc, argv)))\
			sourceFilePath = "../Input/source.txt"; /* "/home/edena/Dev/aeden/LarkCompiler/LarkCompiler/source.txt";*/
#else
	#define DetermineSourceFilePath()\
		if (!(sourceFilePath = IsSourceFilePathInArguments(argc, argv)))\
		{\
			PrintHelp();\
			return 0;\
		}
#endif

#if 1
	#define DetermineExecutableFilePath()\
		if (!(executableFilePath = IsExecutableFilePathInArguments(argc, argv)))\
			executableFilePath = "../Generated/out.exe";
#else
	#define DetermineExecutableFilePath()\
		if (!(executableFilePath = IsExecutableFilePathInArguments(argc, argv)))\
		{\
			PrintHelp();\
			return 0;\
		}
#endif
