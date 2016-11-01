#include "InitializationRoutines.h"
#include "Parser.h"
#include "Symbol.h"
#include "ParseNode.h"
#include "GenerateICode.h"
#include "GenerateX86Code.h"
#include "GenerateX86ICode.h"
#include "WritePEFile.h"
#include "GenerateDOTFile.h"
#include "Link.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
	#include <conio.h>
#endif

struct SymbolTable* gst;
struct FunctionTable* ft;

int main(int argc, char** argv)
{
	struct SymbolTable globalSymbolTable;
	struct FunctionTable functionTable;

	const char* sourceFilePath;
	const char* executableFilePath;
	const char* dotFilePath;
	const char* entryPoint = "Main";

	FILE* sourceFile;
	FILE* exefile;

	gst = &globalSymbolTable;
	ft = &functionTable;

	InitializeSymbolTable(&globalSymbolTable);
	InitializeFunctionTable(&functionTable);

	DetermineSourceFilePath();
	DetermineExecutableFilePath();
	dotFilePath = "../Generated/ParseTree.dot";

	sourceFile = fopen(sourceFilePath, "rb");
	exefile = fopen(executableFilePath, "wb+");

	if (!sourceFile)
	{
		printf("ERROR: Unable to open \"%s\"\n", sourceFilePath);
		goto Exit;
	}

	if (!exefile)
	{
		printf("ERROR: Unable to open \"%s\"\n", executableFilePath);
		goto Exit;
	}

	printf("Lexical Analysis/Parsing...\n\n");
	SetParserFunctionTable(&functionTable);
	SetParserGlobalSymbolTable(&globalSymbolTable);
	SetParserCurrentFunction(*functionTable.functions);
	ParseFile(sourceFile);

#if 0
	printf("Generating DOT...\n\n");
	GenerateDOTFile(&functionTable, &globalSymbolTable, dotFilePath);
#endif

	printf("\nGenerating Intermediate Code...\n\n");
	GenerateICode(&functionTable, &globalSymbolTable);

	printf("\nGenerating x86 Intermediate Code...\n\n");
	GenerateX86ICode(&functionTable, &globalSymbolTable);

	printf("\nGenerating x86 Code...\n\n");
	GenerateX86Code(&functionTable, &globalSymbolTable);

	printf("\nLinking...\n\n");
	Link(exefile, &functionTable, entryPoint);

	printf("\nDone!\n");

Exit:
	if (exefile)
		fclose(exefile);
	if (sourceFile)
		fclose(sourceFile);

	{
		#if 1 //def DEBUG
			char buff[0x100];
			#ifdef WIN32
				if (dotFilePath)
				{
					sprintf(buff, "\"C:/Program Files/Graphviz2.26.3/bin/dotty.exe\" %s", dotFilePath);

					if (_getch() == 'y')
						system(buff);
				}
				if (_getch() == 'y')
					system("C:/Software/OllyDbg/ollydbg.EXE C:/Dev/Hayaku/hc/Generated/out.exe");

				system("pause");
			#elif defined (LINUX)
				if (dotFilePath)
				{
					sprintf(buff, "dotty \"%s\"", dotFilePath);

					if (getc(stdin) == 'y')
						system(buff);
				}
			#endif
		#endif
	}
	return 0;
}
