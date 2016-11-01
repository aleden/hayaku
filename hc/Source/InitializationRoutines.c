#include "InitializationRoutines.h"
#include "X86ICode.h"
#include "ParseNode.h"
#include "Parser.h"
#include "ICode.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef WIN32
	int __stdcall GetFileAttributesA(char* filepath);
	#define INVALID_FILE_ATTRIBUTES -1

    #define DOES_FILE_EXIST(FILEPATH)\
        (GetFileAttributesA(FILEPATH) != INVALID_FILE_ATTRIBUTES)
#else
	BOOL DoesFileExistForLinux(const char* filePath)
	{
		struct stat fileInfo;

		return (stat(filePath, &fileInfo) == 0);
	}
    #define DOES_FILE_EXIST(FILEPATH)\
        (DoesFileExistForLinux(FILEPATH))
#endif

char* IsSourceFilePathInArguments(int argc, char** argv)
{
	if (argc != 1)
	{
		int i;
		for (i = 1; i + 1 <= argc; ++i)
		{
			if (argv[i][0] == '-' && argv[i][1] == 's')
			{
				if (DOES_FILE_EXIST(argv[i + 1]))
				{
					return argv[i + 1];
					break;
				}
				else
				{
				    printf("ERROR: \"%s\" does not exist\n", argv[i + 1]);
				    break;
				}
			}
		}
	}

	return NULL;
}

char* IsExecutableFilePathInArguments(int argc, char** argv)
{
	if (argc != 1)
	{
		int i;
		for (i = 1; i + 1 <= argc; ++i)
		{
			if (argv[i][0] == '-' && argv[i][1] == 'o')
			{
                return argv[i + 1];
                break;
			}
		}
	}

	return NULL;
}

extern FILE *yyin;
extern int yydebug;
int yyparse();

void ParseFile(FILE* file)
{
#ifdef DEBUG
	yydebug = 1;
#endif

	yyin = file;
	yyparse();
	free(GetParserFunctionTable()->functions[GetParserFunctionTable()->numFunctions]);
	GetParserFunctionTable()->functions[GetParserFunctionTable()->numFunctions] = 0;
	--GetParserFunctionTable()->numFunctions;
}

void PrintHelp()
{
	printf("AddCompiler -s \"[SOURCE_FILE_PATH]\" -o \"[EXECUTABLE_FILE_PATH]\"\n");
}
